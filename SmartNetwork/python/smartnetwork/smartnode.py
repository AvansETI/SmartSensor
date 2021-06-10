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

class SmartNode:
    """Base class SmartNode. All base functionality that belongs to the SmartNode. """

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode. """

        # Debugging on or off!
        self.debug = False

        self.smartnetwork = smartnetwork

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def send_message_to_node(self, id, message):
        """Send a message to a node based on their ID"""
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/message", json.dumps(message))

    def send_event_to_node(self, id, event):
        """Send an event to a node based on their ID"""
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/event", json.dumps(event))

    def add_node_to_network(self, data):
        """Add a node to the network. This will be specific for each type of SmartNode."""
        self.debug_print("add_node_to_network: Base class SmartNode is used! Please make sure concrete classes are used.")
        self.send_message_to_node(data["id"], {"status": 0, "time": datetime.now(timezone.utc).isoformat(), "message": "Sorry the request could not be processed.!"})

    def process_node_data(self, data):
        """Process the data that the node has send. This is required to be processed by concrete classes."""
        self.debug_print("process_node_data: Base class SmartNode is used! Please make sure concrete classes are used.")
        self.send_message_to_node(data["id"], {"status": 0, "time": datetime.now(timezone.utc).isoformat(), "message": "Sorry the request could not be processed.!"})

    def process_node_info(self, data):
        self.debug_print("process_node_info: Base class SmartNode is used! Please make sure concrete classes are used.")
        self.send_message_to_node(data["id"], {"status": 0, "time": datetime.now(timezone.utc).isoformat(), "message": "Sorry the request could not be processed.!"})

    def __str__(self):
        return 'SmartNode' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNode>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
