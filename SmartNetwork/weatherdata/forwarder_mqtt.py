#!/usr/bin/python3

# Todo: Implement message subscription, so the sensor known when a init message have been received
# Todo: Implement mode 1 for this sensor

import os
import sys
import json
from json.encoder import JSONEncoder
import random
import requests
import re
import time
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

# Go to the working directory of this python script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Read the config file!
try:
  config_json = open("config-forwarder.json", "r").read()
  config = json.loads(config_json)
except Exception as e:
  print("Cannot read the config.json file, which is required for execution.")
  print(config_json)
  print(e)
  quit()

mqtt_smart_network = mqtt.Client()
mqtt_azure         = mqtt.Client()

# The callback for when the client receives a CONNACK response from the server.
def on_connect_smart_network(client, userdata, flags, rc):
    print("Connected with smart network: result code "+str(rc))
    mqtt_smart_network.subscribe("#")

# The callback for when the client receives a CONNACK response from the server.
def on_connect_azure(client, userdata, flags, rc):
    print("Connected with azure result code "+str(rc))

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect_smart_network(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT smart network disconnection. Will auto-reconnect")

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect_azure(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT azure disconnection. Will auto-reconnect")
        print(rc)

# The callback for when a PUBLISH message is received from the server.
def on_message_smart_network(client, userdata, msg):
    print("smart network topic: " + msg.topic + ": " + str(msg.payload))
    mqtt_azure.publish(msg.topic, msg.payload)

# The callback for when a PUBLISH message is received from the server.
def on_message_azure(client, userdata, msg):
    print("azure topic: " + msg.topic + ": " + msg.payload)

### SmartNetwork MQTT
mqtt_smart_network.on_connect    = on_connect_smart_network
mqtt_smart_network.on_disconnect = on_disconnect_smart_network
mqtt_smart_network.on_message    = on_message_smart_network

### SmartNetwork MQTT
mqtt_azure.on_connect    = on_connect_azure
mqtt_azure.on_disconnect = on_disconnect_azure
mqtt_azure.on_message    = on_message_azure

mqtt_smart_network.username_pw_set(config["smart_network_user"], password=config["smart_network_password"])
mqtt_smart_network.connect("sendlab.nl", 11884, 60)

#mqtt_azure.username_pw_set(config["azure_user"], password=config["azure_password"])
#mqtt_azure.connect("avansiotdemo.westeurope.azurecontainer.io", 1883, 60)
mqtt_azure.connect("20.61.180.134", 1883, 60)

mqtt_smart_network.loop_start()
mqtt_azure.loop_start()

while ( 1 ):
    time.sleep(24*60*60) # Every 24 hours

mqtt_smart_network.loop_stop()
mqtt_azure.loop_stop()

