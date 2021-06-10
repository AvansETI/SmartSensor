import time
import threading

import re
import json
import random
from datetime import datetime, timezone
import dateutil
import paho.mqtt.client as mqtt # pip install paho-mqtt

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

from smartnetwork.smartnode0 import SmartNode0
from smartnetwork.smartnode1 import SmartNode1

"""
Author: Maurice Snoeren <mac.snoeren(at)avans.nl>
Version: 0.1 beta (use at your own risk)
Date: 7-4-2021
"""

class SmartNetwork(threading.Thread):

    def __init__(self, host, org, token):
        """Create instance of a SmartNetwork.SmartNetwork."""
        super(SmartNetwork, self).__init__()

        # When this flag is set, the node will stop and close
        self.terminate_flag = threading.Event()

        # Debugging on or off!
        self.debug = False

        # MQTT client
        self.mqtt = mqtt.Client()

        # InfluxDB client
        self.host = host
        self.org = org
        self.influx = InfluxDBClient(url=host, token=token)
        self.write  = self.influx.write_api(write_options=SYNCHRONOUS)
        self.query  = self.influx.query_api()
        self.delete = self.influx.delete_api()

        # Initialize the smart network
        self.init_server()

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def init_server(self):
        """Initialization of smart network."""
        self.mqtt.on_connect    = lambda client, userdata, flags, rc: self.mqtt_on_connect(client, userdata, flags, rc)
        self.mqtt.on_disconnect = lambda client, userdata, rc:        self.mqtt_on_disconnect(client, userdata, rc)
        self.mqtt.on_message    = lambda client, userdata, msg:       self.mqtt_on_message(client, userdata, msg)

        self.mqtt.username_pw_set("server", password="servernode")
        self.mqtt.connect("sendlab.nl", 11884, 60)

        self.mqtt.subscribe("node/init", qos=0)
        self.mqtt.subscribe("node/data", qos=0)
        self.mqtt.subscribe("node/info", qos=0)

        self.mqtt.loop_start() # Start the loop thread of MQTT

    def mqtt_on_connect(self, client, userdata, flags, rc):
        self.debug_print("Connected with MQTT broker with result code " + str(rc) + ".")

    def mqtt_on_disconnect(self, client, userdata, rc):
        self.debug_print("Disconnected with MQTT broker with result code " + str(rc) + ".")

    def mqtt_on_message(self, client, userdata, msg):
        print("got message: " + str(msg.topic) + ": " + str(msg.payload))
        try:
            plJson = json.loads(msg.payload)

            # Process the information from the SmartNodes!
            if   ( msg.topic == "node/init" ):
                self.process_node_init(plJson)
            elif ( msg.topic == "node/data" ):
                self.process_node_data(plJson)
            elif ( msg.topic == "node/info" ):
                self.process_node_info(plJson)
            else:
                print("Unknown topic: " + msg.topic)

        except Exception as e: # work on python 2.x
            print("Error processing node data: " + str(msg.payload))
            print(str(e))
            return
            
    def alert(level, type, id, message):
        point = Point("alerts").tag("id", id).tag("level", level).tag("type", type)
        point.field("message", message)
        point.time(datetime.now(), WritePrecision.NS)
        self.write.write("nodedata", self.org, point)

    def get_influx_record(self, records):
        results = {} #https://docs.influxdata.com/influxdb/cloud/tools/client-libraries/python/
        for table in records:
            for record in table.records:
                results[record.get_field()] = record.get_value()
            if ( len(table.records) > 0):
                for tag in table.records[0].values.keys():
                    if ( tag != "result" and tag != "table" and not re.match(r"^_", tag) ):
                        results[tag] = table.records[0].values.get(tag)
                results["time"] = table.records[0].get_time()
                results["id"] = id
        return results

    def get_node_from_id(self, id):
        if ( not re.match(r"^[a-zA-Z0-9_-]+$", id) ): # Check the ID to prevent injection!
            print("ID is not correct: " + id)
            return

        query = 'from(bucket: "nodeinfo")\
|> range(start: 2020-01-01T00:00:00Z)\
|> filter(fn: (r) => r["id"] == "' + id + '")'

        records = self.query.query(org=self.org, query=query)
        if ( len(records) > 0 ): # This sensor ID exists!
            return self.get_influx_record(records)

    def delete_all_node_info(self):
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="info"', bucket='nodeinfo', org=self.org)

    def delete_all_node_data(self):
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="data"', bucket='nodedata', org=self.org)

    def delete_all_node_alerts(self):
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="alerts"', bucket='nodedata', org=self.org)

    def get_smart_node(self, mode):
        if ( mode == 1 ):
            return SmartNode1(self)
        else:
            return SmartNode0(self)

    def process_node_init(self, data):
        if not "id" in data:
            return # Do nothing when id is not found in the data!

        if not "mode" in data:
            data["mode"] = 0 # Add the simplest mode to the sensor data!

        node = self.get_node_from_id(data["id"])
        smart_node = self.get_smart_node(data["mode"])
        if ( node == None ):
            smart_node.add_node_to_network(data)
        else:
            smart_node.welcome_node_to_network(data)

    def process_node_data(self, data):
        if not "id" in data:
            return # Do nothing when id is not found in the data!

        data["id"] = str(data["id"]) # Make sure the id is a string!
        node = self.get_node_from_id(data["id"])
        if ( node != None ):
            smart_node = self.get_smart_node(node["mode"])
            smart_node.process_node_data(data)
        else:
            print("process_node_data: no sensor found!")

    def process_node_info(self, data):
        if not "id" in data:
            return # Do nothing when id is not found in the data!

        node = self.get_node_from_id(data["id"])
        if ( node != None ):
            smart_node = self.get_smart_node(node["mode"])
            smart_node.process_node_info(data)
        else:
            print("process_node_info: no sensor found!")

    def stop(self):
        """Stop the smart network."""
        self.terminate_flag.set()

    def run(self):
        """The main loop of the thread."""
        while not self.terminate_flag.is_set():  # Check whether the thread needs to be closed
            try:
                pass # Do things here!
                
            except Exception as e:
                raise e

            time.sleep(1) # Need to be smaller when we do real stuff!!

        self.mqtt.loop_stop() # Stop the loop thread of MQTT
        print("Smart network stopped")

    def __str__(self):
        return 'SmartNetwork' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNetwork>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
