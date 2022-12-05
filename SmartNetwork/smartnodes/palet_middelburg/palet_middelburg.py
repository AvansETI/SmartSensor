#!/usr/bin/python3

import json
import random
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

sensor_id = "dashboard-palet-middelburg"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT disconnection. Will auto-reconnect")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

# Init message
sensor_init = {
    "type":  "data-provider",
    "mode": 0,
    "id":    sensor_id,
    "name":  "Palet Middelburg",
    "measurements": [{
        "name": "outside_temp",
        "description": "Temperature outside the Palet building.",
        "unit": "Celsius",
    },{
        "name": "inside_temp",
        "description": "Temperature inside the Palet building.",
        "unit": "Celsius",
    },{
        "name": "irradiance",
        "description": "Solar irradiance.",
        "unit": "J/cm^2",
    },{
        "name": "irradiance_toal_next_day",
        "description": "Solar irradiance cummalative (forecast) next day.",
        "unit": "J/cm^2",
    },{
        "name": "wind_direction",
        "description": "Wind direction.",
        "unit": "Degree",
    },{
        "name": "wind_speed",
        "description": "Wind speed.",
        "unit": "m/s",
    },{
        "name": "wind_speed_max_next_day",
        "description": "Maximum forecast of the windspeed for the next day.",
        "unit": "m/s",
    }],
    "actuators": [],
}
    
client = mqtt.Client()
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_message = on_message

client.username_pw_set("node", password="smartmeternode")
client.connect("sendlab.nl", 11884, 60)

client.subscribe("node/" + sensor_id + "/message", qos=0)

print("Sending init message...")
client.publish("node/init", json.dumps(sensor_init))

client.loop_start()

timestamp = datetime.now()
while ( 1 ):
    timediff = datetime.now() - timestamp
    if ( timediff.seconds > 60 ):
        data = {
            "id": sensor_id,
            "measurements": [{
                "timestamp": datetime.now(timezone.utc).isoformat(),
                "outside_temp": 12.0,
                "inside_temp": 20.0,
                "irradiance": 30.0,
                "irradience_total_next_day": 240.0,
                "wind_direction": 270,
                "wind_speed": 8.0,
                "wind_speed_max_next_day": 12.0
            }],
        }
        timestamp = datetime.now()
        client.publish("node/data", json.dumps(data))
        print(data)

client.loop_stop()
