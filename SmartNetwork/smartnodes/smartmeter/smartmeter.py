#!/usr/bin/python3

# Maurice Snoeren, version 0.1, 01-12-2021
# This softsensor reads the smartmeter MQTT and creates a smartnode data
# source for each smartsensor.

import json
from json.encoder import JSONEncoder
import random
import time
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

clientSmartMeter   = mqtt.Client()
clientSmartNetwork = mqtt.Client()

sensor_id = "smartmeter-"

# dict storing the signatures that have been seen
signatures = []

# Send the init message to the smartnetwork
def send_init_message(signature, name):
    clientSmartNetwork.publish("node/init", json.dumps(
    { "type":  "smartmeter",
      "mode": 0,
      "id":   sensor_id + signature,
      "name": name,
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
        "description": "Actual energy delivered total for tarrif 1.",
        "unit": "kWh",
      },{
        "name": "energy_delivered_tarrif_2",
        "description": "Actual energy delivered total for tarrif 2.",
        "unit": "kWh",
      },{
        "name": "energy_received_tarrif_1",
        "description": "Actual energy received total for tarrif 1.",
        "unit": "kWh",
      },{
        "name": "energy_received_tarrif_2",
        "description": "Actual energy received total for tarrif 2.",
        "unit": "kWh",
      }],
    "actuators": [{
      }],
    }))

# Process the smart meter data
def process_smartmeter_data(data):
    print("Processing: " + data["signature"])

    if ( data["signature"] not in signatures ):
        print("Sending init message for this smartmeter!")
        send_init_message(data["signature"], data["p1_decoded"]["manufacturer"] + "-(" + data["p1_decoded"]["version"] + ")")
        signatures.append(data["signature"])
    
    try:
        # Send the data!
        if isinstance(data["p1_decoded"]["power"], list):
            power_received  = data["p1_decoded"]["power"][1]["received"]["value"]
            power_delivered = data["p1_decoded"]["power"][0]["delivered"]["value"]
        else:
            power_received  = data["p1_decoded"]["power"]["received"]["value"]
            power_delivered = data["p1_decoded"]["power"]["delivered"]["value"]

        if isinstance(data["p1_decoded"]["energy"], list):
            energy_delivered_1 = data["p1_decoded"]["energy"][0]["delivered"]["value"]
            energy_received_1 = data["p1_decoded"]["energy"][0]["received"]["value"]
            energy_delivered_2 = data["p1_decoded"]["energy"][1]["delivered"]["value"]
            energy_received_2 = data["p1_decoded"]["energy"][1]["received"]["value"]
        else:
            energy_delivered_1 = data["p1_decoded"]["energy"]["delivered"]["value"]
            energy_received_1 = data["p1_decoded"]["energy"]["received"]["value"]
            energy_delivered_2 = data["p1_decoded"]["energy"]["delivered"]["value"]
            energy_received_2 = data["p1_decoded"]["energy"]["received"]["value"]

        clientSmartNetwork.publish("node/data", json.dumps(
        { "id": sensor_id + data["signature"],
        "measurements": [{
            "timestamp": datetime.now(timezone.utc).isoformat(),
            "tariff": data["p1_decoded"]["tariff"],
            "power_received": power_received,
            "power_delivered": power_delivered,
            "energy_delivered_tarrif_1": energy_delivered_1,
            "energy_received_tarrif_1": energy_received_1,
            "energy_delivered_tarrif_2": energy_delivered_2,
            "energy_received_tarrif_2": energy_received_2,
        }]
        }))

    except Exception as e:
        print("EXCEPTION")
        print(data)
        print(e)

# The callback for when the client receives a CONNACK response from the server.
def on_connect_smartnetwork(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.

# The callback for when the client receives a CONNACK response from the server.
def on_connect_smartmeter(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    clientSmartMeter.subscribe("smartmeter/data", qos=0)

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT disconnection. Will auto-reconnect")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    if msg.retain == 1: # Do not process retained messages!
        return

    if ( msg.topic == "smartmeter/data" ):
        try:
            data = json.loads(msg.payload)
        except:
            print("Error processing data:\n" + str(msg.payload) + "\n---------------------\n")
        process_smartmeter_data(data)

    else:
        print("topic: " + msg.topic + ": " + msg.payload)

### SmartMeter MQTT    
clientSmartMeter.on_connect = on_connect_smartmeter
clientSmartMeter.on_disconnect = on_disconnect
clientSmartMeter.on_message = on_message

clientSmartMeter.username_pw_set("smartmeter_data", password="data")
#clientSmartMeter.connect("sendlab.nl", 11884, 60)
clientSmartMeter.connect("10.0.0.31", 1884, 60)

### SmartNetwork MQTT
clientSmartNetwork.on_connect = on_connect_smartnetwork
clientSmartNetwork.on_disconnect = on_disconnect
clientSmartNetwork.on_message = on_message

clientSmartNetwork.username_pw_set("node", password="smartmeternode")
clientSmartNetwork.connect("sendlab.nl", 11884, 60)

clientSmartMeter.loop_start()
clientSmartNetwork.loop_start()

time.sleep(5)

while ( 1 ):
    time.sleep(10)

clientSmartMeter.loop_stop()

# Example message from MQTT
""" {
  "signature": "2019-ETI-EMON-V01-695FA5-1640EF",
  "p1_decoded": {
    "manufacturer": "FLU5\\\\253769484",
    "version": "30",
    "equipment_id": "3153414733313030303639333837",
    "tariff": 2,
    "power": [
      {
        "delivered": {
          "value": 1.549,
          "unit": "kW"
        }
      },
      {
        "received": {
          "value": 0,
          "unit": "kW"
        }
      }
    ],
    "energy": [
      {
        "tariff": 1,
        "delivered": {
          "value": 34713.971,
          "unit": "kWh"
        },
        "received": {
          "value": 920.523,
          "unit": "kWh"
        }
      },
      {
        "tariff": 2,
        "delivered": {
          "value": 19120.549,
          "unit": "kWh"
        },
        "received": {
          "value": 1291.557,
          "unit": "kWh"
        }
      }
    ],
    "phases": {
      "failures": "NAN",
      "long failures": "NAN",
      "phases": [
        {
          "phase": "L1",
          "sags": "NAN",
          "swells": "NAN",
          "instantaneous voltage": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous current": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power +P": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power -P": {
            "value": "NAN",
            "unit": "NAN"
          }
        },
        {
          "phase": "L2",
          "sags": "NAN",
          "swells": "NAN",
          "instantaneous voltage": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous current": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power +P": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power -P": {
            "value": "NAN",
            "unit": "NAN"
          }
        },
        {
          "phase": "L3",
          "sags": "NAN",
          "swells": "NAN",
          "instantaneous voltage": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous current": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power +P": {
            "value": "NAN",
            "unit": "NAN"
          },
          "instantaneous power -P": {
            "value": "NAN",
            "unit": "NAN"
          }
        }
      ]
    }
  },
  "s0": {
    "unit": "W",
    "label": "e-car charger",
    "value": 0
  },
  "s1": {
    "unit": "W",
    "label": "solar panels",
    "value": 0
  },
  "createdAt": {
    "$date": 1637316824170
  }
} """
