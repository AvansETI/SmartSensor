import time
import re
import json
import random
from datetime import datetime, timezone
import dateutil

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

"""
Author: Maurice Snoeren <mac.snoeren(at)avans.nl>
Version: 0.1 beta (use at your own risk)
Date: 7-4-2021
"""

class SmartNode1:

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode1. A SmartNode that does implement some security asymm. """
        super(SmartNode1, self).__init__()

        # Debugging on or off!
        self.debug = False

        self.smartnetwork = smartnetwork

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def send_message_to_node(self, id, message):
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/message", json.dumps(message))

    def send_event_to_node(self, id, event):
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/event", json.dumps(event))

    def add_node_to_network(self, data):
        required_fields = ("id", "type", "name", "mode", "measurements", "actuators") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("add_node_to_network: required field '" + required_field + " missing.")
                return

        point = Point("info").tag("id", data["id"]).tag("type", data["type"]).tag("name", data["name"])
        point.tag("location", "none").tag("reference", "none").tag("mode", data["mode"]) # Values filled in later
        point.field("pecc", data["pecc"]).field("pdhk", data["pdhk"]).field("nonce", data["nonce"])
        point.field("hash", data["hash"]).field("sign", data["sign"])
        point.field("measurements", json.dumps(data["measurements"]))
        point.field("actuators", json.dumps(data["measurements"]))
        point.field("validated", 0)
        self.smartnetwork.write.write("nodeinfo", self.smartnetwork.org, point)
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome, you have been added to the network!", })

    def welcome_node_to_network(self, data):
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome back to the network!"})

    def process_node_data(self, data):
        required_fields = ("id", "measurements") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("process_node_data: required field '" + required_field + " missing.")
                return

        for measurement in data["measurements"]:
            point = Point("data").tag("id", data["id"])
            for item in measurement.keys():
                if ( item != "timestamp" ):
                    point.field(item, measurement[item])
                    point.time(dateutil.parser.parse(measurement["timestamp"]), WritePrecision.NS)
        self.smartnetwork.write.write("nodedata", self.smartnetwork.org, point)
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/data", json.dumps(data)) # relay it further!

    def process_node_info(self, data):
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/info", json.dumps(data)) # relay it further!

    def __str__(self):
        return 'SmartNode' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNode>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
