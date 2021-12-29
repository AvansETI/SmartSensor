"""
@author	    Maurice Snoeren
@contact	macsnoeren@gmail.com
@copyright	2021 (c) Avans Hogeschool
@license	GNUv3
@date	    14-12-2021
@version	1.0
"""

import json
from datetime import datetime, timezone

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

class SmartNode:
    """Base class SmartNode. All base functionality that belongs to the SmartNode. """

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode. """

        # The object to the smart network itself
        self.smartnetwork = smartnetwork

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        self.smartnetwork.debug_print(message)

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
        """Process the info that the node has send. No security checks, just relay it further."""
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/info", json.dumps(data)) # relay it further!
        
    def welcome_node_to_network(self, data):
        """When the node is already added to the database, we wish the node a welcome back."""
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome back to the network!"})

    def __str__(self):
        """Default Python method to represent the class as a string"""
        return 'SmartNode (Base Class)'

    def __repr__(self):
        """Default Python method to represent the class as a string"""
        return 'SmartNode (Base Class)'
