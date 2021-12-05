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

sensor_id = "openweathermap-"

# In order to send the init message once, this array is used
cities = []

# config
config = {}

# Send the init message to the smartnetwork
def send_init_message(city):
    #clientSmartNetwork.publish("node/init", 
    print(json.dumps(
    { "type":  "internet",
      "mode": 0,
      "id":   sensor_id + re.sub(r'\W+', '', city.lower()),
      "name": city,
      "measurements": [{
        "name": "weather",
        "description": "Weather type.",
        "unit": "-",
      },{
        "name": "weather_description",
        "description": "Weather type description.",
        "unit": "-",
      },{
        "name": "weather_icon",
        "description": "",
        "unit": "-",
      },{
        "name": "temp",
        "description": "",
        "unit": "-",
      },{
        "name": "temp_min",
        "description": "",
        "unit": "-",
      },{
        "name": "temp_max",
        "description": "",
        "unit": "-",
      },{
        "name": "pressure",
        "description": "",
        "unit": "-",
      },{
        "name": "humidity",
        "description": "",
        "unit": "-",
      },{
        "name": "wind_speed",
        "description": "",
        "unit": "-",
      },{
        "name": "wind_degree",
        "description": "",
        "unit": "-",
      },{
        "name": "rain",
        "description": "",
        "unit": "-",
      },{
        "name": "clouds",
        "description": "",
        "unit": "-",
      },{
        "name": "sunrise",
        "description": "",
        "unit": "-",
      },{
        "name": "sunset",
        "description": "",
        "unit": "-",
      }],
    "actuators": [{
      }],
    }))

def process_data(city_id):
  print("Processing the data...")

  api_url = "https://api.openweathermap.org/data/2.5/weather?units=metric&id=" + str(city_id) + "&appid=" + config["token"]
  print("API CALL: " + api_url)
  response = requests.get(api_url)

  try:
    data = response.json()

    if data["name"] not in cities:
      send_init_message(data["name"])

    # When it is not raining, this is not in the data
    rain = 0.0
    if "rain" in data:
      rain = data["rain"]["1h"]

    #clientSmartNetwork.publish("node/data", 
    print(json.dumps(
      { "id": sensor_id + re.sub(r'\W+', '', data["name"].lower()),
      "measurements": [{
          "timestamp": datetime.now(timezone.utc).isoformat(),
          "weather": data["weather"][0]["main"],
          "weather_description": data["weather"][0]["description"],
          "weather_icon": data["weather"][0]["icon"],
          "temp": data["main"]["temp"],
          "temp_min": data["main"]["temp_min"],
          "temp_max": data["main"]["temp_max"],
          "pressure": data["main"]["pressure"],
          "humidity": data["main"]["humidity"],
          "wind_speed": data["wind"]["speed"],
          "wind_degree": data["wind"]["deg"],
          "rain": rain,
          "clouds": data["clouds"]["all"],
          "sunrise": data["sys"]["sunrise"],
          "sunset": data["sys"]["sunset"]
      }]
    }))

  except Exception as e:
      print("Could not process the data")
      print("city_id: " + str(city_id))
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
  config_json = open("config.json", "r").read()
  config = json.loads(config_json)
except Exception as e:
  print("Cannot read the config.json file, which is required for execution.")
  print(config_json)
  print(e)
  quit()

while ( 1 ):
    for city_id in config["cities"]:
      print("process city id: " + str(city_id))
      process_data(city_id)

    time.sleep(5*60) # total minutes to sample the api

clientSmartNetwork.loop_stop()

""" 
https://api.openweathermap.org/data/2.5/weather?id=2758401&appid=e89a4dc186a4227a3923013f414608d6
{
  "coord": {
    "lon": 4.776,
    "lat": 51.5866
  },
  "weather": [
    {
      "id": 520,
      "main": "Rain",
      "description": "light intensity shower rain",
      "icon": "09d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 278.99,
    "feels_like": 278.99,
    "temp_min": 278.1,
    "temp_max": 279.82,
    "pressure": 994,
    "humidity": 93
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.89,
    "deg": 310,
    "gust": 1.79
  },
  "rain": {
    "1h": 0.21
  },
  "clouds": {
    "all": 75
  },
  "dt": 1638627849,
  "sys": {
    "type": 2,
    "id": 2039561,
    "country": "NL",
    "sunrise": 1638602937,
    "sunset": 1638632022
  },
  "timezone": 3600,
  "id": 2758401,
  "name": "Breda",
  "cod": 200
}
"""