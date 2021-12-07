#!/usr/bin/python3

# Todo: Implement message subscription, so the sensor known when a init message have been received
# Todo: Implement mode 1 for this sensor

import json
from json.encoder import JSONEncoder
import random
import requests
import re
import time
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

clientSmartNetwork = mqtt.Client()

sensor_id = "forecastsolar-"

# In order to send the init message once, this array is used
places = []

# config
config = {}

# Send the init message to the smartnetwork
def send_init_message(id, name):
    clientSmartNetwork.publish("node/init", json.dumps(
    { "type":  "internet",
      "mode": 0,
      "id":   sensor_id + id,
      "name": name,
      "measurements": [{
        "name": "W",
        "description": "Total estimates watt given the solar panel details.",
        "unit": "-",
      },{
        "name": "Wh",
        "description": "Total estimates watt hours given the solar panel details.",
        "unit": "-",
      }],
    "actuators": [{
      }],
    }))
    
def process_data(id, name, latitude, longitude, declination, azimuth, kwp):
  api_url = "https://api.forecast.solar/estimate/" + str(latitude) + "/" + str(longitude) + "/" + str(declination) + "/" + str(azimuth) + "/" + str(kwp)
  print("API CALL: " + api_url)
  response = requests.get(api_url)

  try:
    data = response.json()
    print(data)

    if id not in places:
      send_init_message(id, name)

    for timestamp in data["result"]["watts"]:
      clientSmartNetwork.publish("node/data", json.dumps(
        { "id": sensor_id + id,
        "measurements": [{
            "timestamp": datetime.strptime(timestamp, '%Y-%m-%d %H:%M:%S').isoformat(),
            "W": data["result"]["watts"][timestamp] * 1.0,
            "Wh": data["result"]["watt_hours"][timestamp] * 1.0
        }]
      }))

  except Exception as e:
      print("Could not process the data")
      print("place id: " + id)
      print(e)

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT disconnection. Will auto-reconnect")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print("topic: " + msg.topic + ": " + msg.payload)

### SmartNetwork MQTT
clientSmartNetwork.on_connect    = on_connect
clientSmartNetwork.on_disconnect = on_disconnect
clientSmartNetwork.on_message    = on_message

clientSmartNetwork.username_pw_set("node", password="smartmeternode")
clientSmartNetwork.connect("sendlab.nl", 11884, 60)

clientSmartNetwork.loop_start()

# Read the config file!
try:
  config_json = open("config-forecastsolar.json", "r").read()
  config = json.loads(config_json)
except Exception as e:
  print("Cannot read the config.json file, which is required for execution.")
  print(config_json)
  print(e)
  quit()

while ( 1 ):
    for place in config["places"]:
      print("process place: " + place["name"])
      print("- solar panel installation: " + str(place["installed_kwp"]))
      process_data(place["id"], place["name"], place["latitude"], place["longitude"], place["declination"], place["azimuth"], place["installed_kwp"])

    time.sleep(24*60*60) # Every 24 hours

clientSmartNetwork.loop_stop()

""" 
https://api.forecast.solar/estimate/51.58586805578371/4.793202206697863/0/0/1000
{
  "result": {
    "watts": {
      "2021-12-06 08:25:00": 0,
      "2021-12-06 08:43:00": 12000,
      "2021-12-06 09:00:00": 61151,
      "2021-12-06 10:00:00": 92900,
      "2021-12-06 11:00:00": 123163,
      "2021-12-06 12:00:00": 131180,
      "2021-12-06 13:00:00": 120669,
      "2021-12-06 14:00:00": 100118,
      "2021-12-06 15:00:00": 62252,
      "2021-12-06 16:00:00": 18455,
      "2021-12-06 16:20:00": 4000,
      "2021-12-06 16:40:00": 0,
      "2021-12-07 08:26:00": 0,
      "2021-12-07 08:43:00": 22000,
      "2021-12-07 09:00:00": 109762,
      "2021-12-07 10:00:00": 178663,
      "2021-12-07 11:00:00": 220607,
      "2021-12-07 12:00:00": 225307,
      "2021-12-07 13:00:00": 188688,
      "2021-12-07 14:00:00": 124494,
      "2021-12-07 15:00:00": 63795,
      "2021-12-07 16:00:00": 19094,
      "2021-12-07 16:20:00": 4000,
      "2021-12-07 16:40:00": 0
    },
    "watt_hours": {
      "2021-12-06 08:25:00": 0,
      "2021-12-06 08:43:00": 3600,
      "2021-12-06 09:00:00": 20926,
      "2021-12-06 10:00:00": 113826,
      "2021-12-06 11:00:00": 236989,
      "2021-12-06 12:00:00": 368169,
      "2021-12-06 13:00:00": 488838,
      "2021-12-06 14:00:00": 588956,
      "2021-12-06 15:00:00": 651208,
      "2021-12-06 16:00:00": 669663,
      "2021-12-06 16:20:00": 670996,
      "2021-12-06 16:40:00": 670996,
      "2021-12-07 08:26:00": 0,
      "2021-12-07 08:43:00": 6233,
      "2021-12-07 09:00:00": 37333,
      "2021-12-07 10:00:00": 215996,
      "2021-12-07 11:00:00": 436603,
      "2021-12-07 12:00:00": 661910,
      "2021-12-07 13:00:00": 850598,
      "2021-12-07 14:00:00": 975092,
      "2021-12-07 15:00:00": 1038887,
      "2021-12-07 16:00:00": 1057981,
      "2021-12-07 16:20:00": 1059314,
      "2021-12-07 16:40:00": 1059314
    },
    "watt_hours_day": {
      "2021-12-06": 670996,
      "2021-12-07": 1059314
    }
  },
  "message": {
    "code": 0,
    "type": "success",
    "text": "",
    "info": {
      "latitude": 51.5858,
      "longitude": 4.7928,
      "place": "4817 HC Breda, Noord-Brabant, NL",
      "timezone": "Europe/Amsterdam"
    },
    "ratelimit": {
      "period": 3600,
      "limit": 12,
      "remaining": 1
    }
  }
}
"""