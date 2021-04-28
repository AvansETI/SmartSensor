import sys
import time
import threading

import json
import random
from datetime import datetime, timezone
import dateutil
import paho.mqtt.client as mqtt # pip install paho-mqtt

from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

"""
Author: Maurice Snoeren <macsnoeren(at)gmail.com>
Version: 0.1 beta (use at your own risk)
Date: 28-04-2021

Python package smartnetwork for implementing smart MQTT networking.

"""

class SmartNetwork(threading.Thread):
    """SmartNetwork implementation."""

    def __init__(self):
        """Create instance of a SmartNetwork."""

        super(SmartNetwork, self).__init__()

        # When this flag is set, the node will stop and close
        self.terminate_flag = threading.Event()

        # Server details, host (or ip) to bind to and the port
        self.mqtt_client = mqtt.Client()

        # Debugging on or off!
        self.debug = False

        # Init SmartNetwork
        self.init()
        
    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def init(self):
        """Initialization of the TCP/IP server to receive connections. It binds to the given host and port."""
        print("Initialisation of the SmartNetwork.")

    def stop(self):
        """Stop the SmartNetwork."""
        self.terminate_flag.set()
        
    def run(self):
        """The main loop of the thread."""
        while not self.terminate_flag.is_set():  # Check whether the thread needs to be closed
            try:
                self.debug_print("Node: Wait for incoming connection")

            except Exception as e:
                raise e

            time.sleep(0.01)

        print("SmartNetwork stopping...")
        print("SmartNetwork stopped")

    def __str__(self):
        return 'SmartNetwork: '

    def __repr__(self):
        return 'SmartNetwork: '
