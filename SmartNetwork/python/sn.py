#!/usr/bin/python3

import sys
import time

from smartnetwork.smartnetwork import SmartNetwork

server = SmartNetwork()

server.start()

print("Started")

server.stop()
