"""
@author	    Maurice Snoeren
@contact	macsnoeren@gmail.com
@copyright	2021 (c) Avans Hogeschool
@license	GNUv3
@date	    14-12-2021
@version	1.0
"""

import time
import threading

import re
import json
from datetime import datetime, timezone
import paho.mqtt.client as mqtt # pip install paho-mqtt

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

from smartnetwork.smartnode0 import SmartNode0
from smartnetwork.smartnode1 import SmartNode1

class SmartNetwork(threading.Thread):
    """The class SmartNetwork implements the SmartNetwork that is active on the MQTT network. 
       It is the main controller of the network that controls the smart nodes and the 
       controllers in the network using the MQTT protocol.
       TODO: Detect whether another SmartNetwork is active, while only one can be active!
    """

    def __init__(self, config_file="smartnetwork.json"):
        """Create instance of the SmartNetwork class."""
        super(SmartNetwork, self).__init__()

        # When this flag is set, the node will stop and close
        self.terminate_flag = threading.Event()

        # Debugging on or off!
        self.debug = False

        # When testing is True, it will not push any data to the InfluxDB and
        # all SmartNodes are recognized as existing
        self.test = False

        # Read the config file
        try:
            config_json = open(config_file, "r").read()
            self.config = json.loads(config_json)

        except Exception as e:
            print("Cannot read the config.json file, which is required for execution.")
            quit()

        # MQTT client
        self.mqtt = mqtt.Client()

        # InfluxDB client variables
        print("Connecting with influxdb...")
        self.host = self.config["influxdb"]["host"]
        self.org = self.config["influxdb"]["org"]
        self.influx = InfluxDBClient(url=self.host, token=self.config["influxdb"]["token"])
        self.write  = self.influx.write_api(write_options=SYNCHRONOUS)
        self.query  = self.influx.query_api()
        self.delete = self.influx.delete_api()

        # Initialize the smart network
        print("Connecting with MQTT...")
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

        self.mqtt.username_pw_set(self.config["mqtt"]["username"], password=self.config["mqtt"]["password"])
        self.mqtt.connect(self.config["mqtt"]["host"], self.config["mqtt"]["port"], 60)
        self.mqtt.loop_start() # Start the loop thread of MQTT

    def mqtt_on_connect(self, client, userdata, flags, rc):
        """When the MQTT client is connected to the server, this function is called to handle it."""
        self.debug_print("Connected with MQTT broker with result code " + str(rc) + ".")

        # Moved the subscribes to on_connect, so when reconnected we will subscribe again!
        self.mqtt.subscribe("node/init", qos=0)
        self.mqtt.subscribe("node/data", qos=0)
        self.mqtt.subscribe("node/info", qos=0)

    def mqtt_on_disconnect(self, client, userdata, rc):
        """When the MQTT client is disconnected from the server, this function is called to handle it."""
        self.debug_print("Disconnected with MQTT broker with result code " + str(rc) + ".")

    def mqtt_on_message(self, client, userdata, msg):
        """When a message is received from the MQTT server, this function is called to handle the message."""
        if msg.retain == 1: # Do not process retained messages!
            return

        self.debug_print("got message: " + str(msg.topic) + ": " + str(msg.payload))

        try:
            plJson = json.loads(msg.payload)

        except Exception as e: # work on python 2.x
            print("Error processing json: " + str(msg.payload))
            print(e)
            return

        # Process the information from the SmartNodes!
        # When debug is enabled, make sure we do not catch errors so we can debug!
        if self.debug:
            if   ( msg.topic == "node/init" ):
                self.process_node_init(plJson)
            elif ( msg.topic == "node/data" ):
                self.process_node_data(plJson)
            elif ( msg.topic == "node/info" ):
                self.process_node_info(plJson)
            else:
                print("Unknown topic: " + msg.topic)
        else:
            try:
                if   ( msg.topic == "node/init" ):
                    self.process_node_init(plJson)
                elif ( msg.topic == "node/data" ):
                    self.process_node_data(plJson)
                elif ( msg.topic == "node/info" ):
                    self.process_node_info(plJson)
                else:
                    print("Unknown topic: " + msg.topic)

            except Exception as e: # Here put it in Alert?
                print("Error processing node data: " + str(msg.payload))
                print(e)
                return

    def alert(self, level, type, id, message):
        """Put an alert message into the database!"""
        point = Point("alerts").tag("id", id).tag("level", level).tag("type", type)
        point.field("message", message)
        point.time(datetime.now(), WritePrecision.NS)
        if not self.smartnetwork.test:
            self.write.write("nodedata", self.org, point)

    def get_influx_record(self, records):
        """Convert the influxdb records to a usable result."""
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
        """Find the smart node in the database using the id."""
        if ( not re.match(r"^[a-zA-Z0-9_-]+$", id) ): # Check the ID to prevent injection!
            print("ID is not correct: " + id)
            return

        query = 'from(bucket: "nodeinfo")\
|> range(start: 2020-01-01T00:00:00Z)\
|> filter(fn: (r) => r["id"] == "' + id + '")'

        records = self.query.query(org=self.org, query=query)
        if ( len(records) > 0 ): # This sensor ID exists!
            return self.get_influx_record(records)

    def delete_smartnode(self, id):
        """Delete all the information of a smart node, given the id, from the data and info buckets."""
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="data" AND id="' + id + '"', bucket='nodedata', org=self.org)
        self.delete.delete(start, stop, '_measurement="info" AND id="' + id + '"', bucket='nodeinfo', org=self.org)

    def delete_all_node_info(self):
        """Delete all the information from the info bucket."""
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="info"', bucket='nodeinfo', org=self.org)

    def delete_all_node_data(self):
        """Delete all the information from the data bucket."""
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="data"', bucket='nodedata', org=self.org)

    def delete_all_node_alerts(self):
        """Delete all the information from the alert bucket."""
        start = "1970-01-01T00:00:00Z"
        stop = datetime.now(timezone.utc).isoformat()
        self.delete.delete(start, stop, '_measurement="alerts"', bucket='nodedata', org=self.org)

    def get_smart_node(self, mode):
        """Get the correct smart node object based on the given mode. The mode determines
           how the smart node has been implemented.
        """
        if ( int(mode) == 1 ):
            return SmartNode1(self)
        else:
            return SmartNode0(self)

    def process_node_init(self, data):
        """Process the node/init message that has been received by the MQTT server."""
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
        """Process the node/data message that has been received by the MQTT server."""
        if not "id" in data:
            return # Do nothing when id is not found in the data!

        data["id"] = str(data["id"]) # Make sure the id is a string!
        node = self.get_node_from_id(data["id"])
        if node != None:
            smart_node = self.get_smart_node(node["mode"])
            smart_node.process_node_data(data)
        else:
            print("process_node_data: no sensor found!")

        if self.test:
            if "mode" in data:
                smart_node = self.get_smart_node(data["mode"])
                smart_node.process_node_data(data)
            else:
                print("TEST: Simulating the sensor based on data, please provide mode for testing!")

    def process_node_info(self, data):
        """Process the node/info message that has been received by the MQTT server."""
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
        """Default Python method to convert the class to a string represntation"""
        return 'SmartNetwork'

    def __repr__(self):
        """Default Python method to convert the class to a string represntation"""
        return 'SmartNetwork'
