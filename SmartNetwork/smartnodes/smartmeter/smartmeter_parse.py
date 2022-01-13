#!/usr/bin/python3

# Maurice Snoeren, version 1.0, 06-01-2022
# This softsensor reads the smartmeter MQTT raw messages and parses the
# P1 datagram itself rather than depending on the SmartMeter infrastructure.
# This parser also extract the gas meter value is available.
# Documentation:
# - https://www.netbeheernederland.nl/_upload/Files/Slimme_meter_15_32ffe3cc38.pdf
# - OBIS: https://www.promotic.eu/en/pmdoc/Subsystems/Comm/PmDrivers/IEC62056_OBIS.htm

import json
from json.encoder import JSONEncoder
import random
import time
from datetime import datetime, timezone
import re

import paho.mqtt.client as mqtt # pip install paho-mqtt

config = {}

# Read the config file!
try:
  config_json = open("smartmeter.json", "r").read()
  config = json.loads(config_json)
except Exception as e:
  print("Cannot parse the config.json file: " + str(e))
  quit()

clientSmartMeter   = mqtt.Client()
clientSmartNetwork = mqtt.Client()

sensor_id = "smartmeter-"

# dict storing the signatures that have been seen
signatures = []


# Send the init message to the smartnetwork
def send_init_message(signature):
    clientSmartNetwork.publish("node/init", json.dumps(
    { "type":  "smartmeter",
      "mode": 0,
      "id":   sensor_id + signature,
      "name": signature,
      "measurements": [{
        "name": "tariff",
        "description": "Actual tarrif of the smartmeter.",
        "unit": "-",
      },{
        "name": "power_received",
        "description": "Actual power received.",
        "unit": "kW",
      },{
        "name": "power_delivered",
        "description": "Actual power delivered.",
        "unit": "kW",
      },{
        "name": "energy_delivered_tarrif_1",
        "description": "Actual energy delivered to the customer for tarrif 1.",
        "unit": "kWh",
      },{
        "name": "energy_delivered_tarrif_2",
        "description": "Actual energy delivered to the customer for tarrif 2.",
        "unit": "kWh",
      },{
        "name": "energy_received_tarrif_1",
        "description": "Actual energy received from the customer for tarrif 1.",
        "unit": "kWh",
      },{
        "name": "energy_received_tarrif_2",
        "description": "Actual energy received from the customer for tarrif 2.",
        "unit": "kWh",
      },{
        "name": "energy_delivered",
        "description": "Actual energy delivered to the customer (tarrif 1+2).",
        "unit": "kWh",
      },{
        "name": "energy_received",
        "description": "Actual energy received from the customer (tarrif 1+2).",
        "unit": "kWh",
      },{
        "name": "gas_delivered",
        "description": "Actual gas that is delivered to the customer.",
        "unit": "m3",
      }],
    "actuators": [{
      }],
    }))

# Process the smart meter data
def process_smartmeter_data(data):
  if ( "datagram" in data ) and "signature" in data["datagram"] and "p1" in data["datagram"]:
    print("Processing: " + data["datagram"]["signature"])
    
    if ( data["datagram"]["signature"] not in signatures ):
        print("Sending init message for "+ data["datagram"]["signature"])
        send_init_message(data["datagram"]["signature"])
        signatures.append(data["datagram"]["signature"])
    
    try:
        record = process_smartmeter_data_raw(data)
        record["timestamp"] =  datetime.now(timezone.utc).isoformat()

        # Send the data!
        clientSmartNetwork.publish("node/data", json.dumps({ 
            "id": sensor_id + data["datagram"]["signature"],
            "measurements": [record]
        }))

    except Exception as e:
        print("EXCEPTION: Could not process the raw data.")
        print(data)
        print(e)

# Process the smart meter data
def process_smartmeter_data_raw(data):
  lines = str(data["datagram"]["p1"]).splitlines()
  version = lines[0]
  endline = lines[len(lines)-1]
  data = {}
  for i in range(2,len(lines)-1):
    matches = re.match("^(\d+)-(\d+):(\d+)\.(\d+)\.(\d+)\((.*)\)$", lines[i])
    if matches:
      m = matches.groups()
      r = process_p1_lines(int(m[0]), int(m[1]), int(m[2]), int(m[3]), int(m[4]), m[5])
      if r != None:
        data[r[0]] = r[1]
#    print(str(i) + ": " + lines[i])
#    print(r)
  if "energy_delivered_tarrif_1" in data and "energy_delivered_tarrif_2" in data and "energy_received_tarrif_1" in data and "energy_received_tarrif_2" in data:
    data["energy_delivered"] = data["energy_delivered_tarrif_1"] + data["energy_delivered_tarrif_2"]
    data["energy_received"] = data["energy_received_tarrif_1"] + data["energy_received_tarrif_2"]

  return data

def process_p1_lines(medium, channel, physical_value, algorithm, measurement_type, cosem):
  #print("medium: %s, channel: %s, physical_value: %s, algorithm: %s, measurement_type: %s, cosem: %s" % (medium, channel, physical_value, algorithm, measurement_type, cosem))
  
  # Meter Reading electricity delivered to client (Tariff 1) in 0,001 kWh
  if medium == 1 and channel == 0 and physical_value == 1 and algorithm == 8 and measurement_type == 1:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("energy_delivered_tarrif_1", float(matches.groups()[0]))
  
  # Meter Reading electricity delivered to client (Tariff 2) in 0,001 kWh
  if medium == 1 and channel == 0 and physical_value == 1 and algorithm == 8 and measurement_type == 2:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("energy_delivered_tarrif_2", float(matches.groups()[0]))
 
  # Meter Reading electricity delivered by client (Tariff 1) in 0,001 kWh
  if medium == 1 and channel == 0 and physical_value == 2 and algorithm == 8 and measurement_type == 1:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("energy_received_tarrif_1", float(matches.groups()[0]))
  
  # Meter Reading electricity delivered by client (Tariff 2) in 0,001 kWh
  if medium == 1 and channel == 0 and physical_value == 2 and algorithm == 8 and measurement_type == 2:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("energy_received_tarrif_2", float(matches.groups()[0]))

  # Tariff indicator electricity. 0-0:96.14.0
  if medium == 0 and channel == 0 and physical_value == 96 and algorithm == 14 and measurement_type == 0:
    matches = re.match("^0*(\d+)$", cosem)
    if matches:
      return ("tariff_indicator", int(matches.groups()[0]))

  # Actual electricity power delivered (+P) in 1 Watt resolution. 1-0:1.7.0
  if medium == 1 and channel == 0 and physical_value == 1 and algorithm == 7 and measurement_type == 0:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("actual_power_delivered", float(matches.groups()[0]))

  # Actual electricity power received (-P) in 1 Watt resolution. 1-0:2.7.0
  if medium == 1 and channel == 0 and physical_value == 2 and algorithm == 7 and measurement_type == 0:
    matches = re.match("^(.+)\*.+$", cosem)
    if matches:
      return ("actual_power_received", float(matches.groups()[0]))

  # Last hourly Meter reading and capture time (e.g. slave E meter). 0-n:24.2.1.255 
  if medium == 0 and channel > 0 and channel <=4 and physical_value == 24 and algorithm == 2 and measurement_type == 1:
    matches = re.match("^.+\((.+)\*m3$", cosem)
    if matches:
      return ("gas_delivered", float(matches.groups()[0]))

  return None

# The callback for when the client receives a CONNACK response from the server.
def on_connect_smartnetwork(client, userdata, flags, rc):
    print("Connected with SmartNetwork MQTT: " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.

# The callback for when the client receives a CONNACK response from the server.
def on_connect_smartmeter(client, userdata, flags, rc):
    print("Connected with SmartMeter MQTT: " + str(rc))
    clientSmartMeter.subscribe("smartmeter/raw", qos=0)

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT disconnection. Will auto-reconnect")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    if msg.retain == 1: # Do not process retained messages!
        return

    if ( msg.topic == "smartmeter/raw" ):
        try:
            data = json.loads(msg.payload)
        except:
            print("Error processing data:\n" + str(msg.payload) + "\n---------------------\n")
        
        try:
          process_smartmeter_data(data)
        except:
          print("Error processing SmartMeter data.\n")
    else:
        print("topic: " + msg.topic + ": " + msg.payload)

### SmartMeter MQTT    
clientSmartMeter.on_connect = on_connect_smartmeter
clientSmartMeter.on_disconnect = on_disconnect
clientSmartMeter.on_message = on_message

clientSmartMeter.username_pw_set(config["smartmeter_mqtt"]["username"], password=config["smartmeter_mqtt"]["password"])
clientSmartMeter.connect(config["smartmeter_mqtt"]["host"], config["smartmeter_mqtt"]["port"], 60)

### SmartNetwork MQTT
clientSmartNetwork.on_connect = on_connect_smartnetwork
clientSmartNetwork.on_disconnect = on_disconnect
clientSmartNetwork.on_message = on_message

clientSmartNetwork.username_pw_set(config["smartnetwork_mqtt"]["username"], password=config["smartnetwork_mqtt"]["password"])
clientSmartNetwork.connect(config["smartnetwork_mqtt"]["host"], config["smartnetwork_mqtt"]["port"], 60)

clientSmartMeter.loop_start()
clientSmartNetwork.loop_start()

time.sleep(5)

while ( 1 ):
    time.sleep(10)

clientSmartMeter.loop_stop()

