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

        # Initialize the smart network
        self.init_server()

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def init_server(self):
        """Initialization of smart network."""
        self.mqtt.on_connect = lambda client, userdata, flags, rc: self.mqtt_on_connect(client, userdata, flags, rc)
        self.mqtt.on_message = lambda client, userdata, msg: self.mqtt_on_message(client, userdata, msg)

        self.mqtt.username_pw_set("server", password="servernode")
        self.mqtt.connect("sendlab.nl", 11884, 60)

        self.mqtt.subscribe("node/init", qos=0)
        self.mqtt.subscribe("node/data", qos=0)
        self.mqtt.subscribe("node/info", qos=0)

    def mqtt_on_connect(self, client, userdata, flags, rc):
        self.debug_print("Connected with MQTT broker with result code " + str(rc) + ".")

    def mqtt_on_message(self, client, userdata, msg):
        print("got message: " + msg.topic)
        try:
            plJson = json.loads(msg.payload)
        except:
            print("Error processing node data: " + msg.payload)
            return

        # Process the information from the nodes!
        if   ( msg.topic == "node/init" ):
            self.process_node_init(plJson)
        elif ( msg.topic == "node/data" ):
            self.process_node_data(plJson)
        elif ( msg.topic == "node/info" ):
            self.process_node_info(plJson)
        else:
            print("Unknown topic: " + msg.topic)

    #SQL injection!!
    def get_node_from_id(self, id):
        if ( not re.match(r"^[a-zA-Z0-9]+$", id) ):
            print("ID is not correct: " + id)
            return

        query = 'from(bucket: "nodeinfo")\
|> range(start: 2020-01-01T00:00:00Z)\
|> filter(fn: (r) => r["id"] == "' + id + '")\
|> filter(fn: (r) => r["_field"] == "validated")'

        tables = self.query.query(org=self.org, query=query)
        for table in tables:
            print(len(table.records))
            for row in table.records:
                print (row.values)

        if ( len(tables) == 1 and len(tables[0].records) == 1 and tables[0].records[0].get_value() == 1 ): #exists
            pass
        print(tables[0])

    def process_node_init(self, data):
        print("init")
        print(data)

    def process_node_data(self, data):
        print("data")
        print(data)
        self.get_node_from_id(data["id"])

    def process_node_info(self, data):
        print("info")
        print(data)

    def stop(self):
        """Stop the smart network."""
        self.terminate_flag.set()

    def run(self):
        """The main loop of the thread."""
        while not self.terminate_flag.is_set():  # Check whether the thread needs to be closed
            try:
                self.mqtt.loop()
                
            except Exception as e:
                raise e

            time.sleep(0.01)

        print("Smart network stopped")

    def __str__(self):
        return 'SmartNetwork' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNetwork>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
