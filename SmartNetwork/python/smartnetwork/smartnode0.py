import time
import re
import json
import random
from datetime import datetime, timezone
import dateutil
import pytz

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS
from smartnetwork.smartnode import SmartNode

"""
Author: Maurice Snoeren <mac.snoeren(at)avans.nl>
Version: 0.1 beta (use at your own risk)
Date: 7-4-2021
"""

class SmartNode0 (SmartNode):

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode0. A SmartNode that does not implement any security. """
        super().__init__(smartnetwork)

    def add_node_to_network(self, data):
        """Add the node to the network."""
        required_fields = ("id", "type", "name", "mode", "measurements", "actuators") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("add_node_to_network: required field '" + required_field + " missing.")
                return

        point = Point("info").tag("id", data["id"]).tag("type", data["type"]).tag("name", data["name"])
        point.tag("location", "none").tag("reference", "none").tag("mode", data["mode"])
        point.field("measurements", json.dumps(data["measurements"]))
        point.field("actuators", json.dumps(data["actuators"]))
        point.field("validated", 0)
        self.smartnetwork.write.write("nodeinfo", self.smartnetwork.org, point)
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome, you have been added to the network!"})

    def welcome_node_to_network(self, data):
        """When the node is already added to the database, we wish the node a welcome back."""
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome back to the network!"})

    def process_node_data(self, data):
        """Process the node data that has been send."""
        required_fields = ("id", "measurements") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("process_node_data: required field '" + required_field + " missing.")
                return

        # When a device does not have the correct time, it can sent its timestamp
        disrupted_timestamp_diff = None
        if "timestamp" in data:
            timestamp_node = dateutil.parser.parse(data["timestamp"])
            if timestamp_node.tzinfo is None or timestamp_node.tzinfo.utcoffset(timestamp_node) is None:
                timestamp_node = pytz.utc.localize(timestamp_node) # Make timestamp aware of timezone when this is not given
                print("timestamp was naive!!")
            disrupted_timestamp_diff = datetime.now(timezone.utc) - timestamp_node;

        # Process the measurements!
        for measurement in data["measurements"]:
            if "timestamp" in measurement: # timestamp is required!
                point_timestamp = dateutil.parser.parse(measurement["timestamp"])

                if disrupted_timestamp_diff != None:
                    print("Fixed timestamp: " + str(point_timestamp) + " +> " + str(point_timestamp + disrupted_timestamp_diff))
                    point_timestamp = point_timestamp + disrupted_timestamp_diff

                point = Point("data").tag("id", data["id"])
                for item in measurement.keys():
                    if ( item != "timestamp" ):
                        point.field(item, measurement[item])
                        point.time(point_timestamp, WritePrecision.NS)
                self.smartnetwork.write.write("nodedata", self.smartnetwork.org, point)
                self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/data", json.dumps(data)) # relay it further!
           
            else:
                print("process_node_data: Measurement does not contain a timestamp!")

    def process_node_info(self, data):
        """Process the info that the node has send. No security checks, just relay it further."""
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/info", json.dumps(data)) # relay it further!

    def __str__(self):
        return 'SmartNode' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNode>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
