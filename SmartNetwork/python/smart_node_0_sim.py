#!/usr/bin/python3

import json
import random
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

sensor_id = "_simulation_0"

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
    "type":  "simulation",
    "mode": 0,
    "id":    sensor_id,
    "name":  "test 1",
    "measurements": [{
        "name": "temperature",
        "description": "Temperature sensor -40 to 100 with 0.1 accuracy.",
        "unit": "degree of Celsius",
    },{
        "name": "humidity",
        "description": "Humidity sensor 0 to 100 with 0.5 accuracy.",
        "unit": "%",
    }],
    "actuators": [{
        "name": "cv",
        "description": "Central heating control from 10 tp 40 degree of Celsius.",
        "unit": "degree of Celsius",
    }],
}
    
client = mqtt.Client()
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_message = on_message

#client.username_pw_set("server", password="servernode")
client.username_pw_set("node", password="smartmeternode")
#client.connect("10.0.0.31", 1884, 60)
client.connect("sendlab.nl", 11884, 60)

client.subscribe("node/" + sensor_id + "/message", qos=0)

print("Sending init message...")
client.publish("node/init", json.dumps(sensor_init))

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
#client.loop_forever()
client.loop_start()

timestamp = datetime.now()
temp = 21.4;
humidity = 56.5;
while ( 1 ):
    timediff = datetime.now() - timestamp;
    if ( timediff.seconds > 1 ):
        data = {
            "id": sensor_id,
            "measurements": [{
                "timestamp": datetime.now(timezone.utc).isoformat(),
                "temperature": temp,
                "humidity": humidity,
            }],
        }
        client.publish("node/data", json.dumps(data))
        temp = temp + random.random()*1 - 0.5;
        humidity = humidity + random.random()*1 - 0.5;
        timestamp = datetime.now()
        print(data)

    #client.loop()

client.loop_stop()
