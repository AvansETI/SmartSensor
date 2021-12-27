#!/usr/bin/python3
import os
import json
import random
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

# pip install cryptography
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF

sensor_id = "_simulation_1"
pubkey_server = {}

# Generate a private key for use in the exchange.
private_key_dh = ec.generate_private_key(
    ec.SECP256R1()
)

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    try:
        data = json.loads(msg.payload)

    except:
        print("Could not load the json: " + str(msg.payload))

    if msg.topic == "node/" + sensor_id + "/message":
        if "pubkey_dh" in data and "pubkey_sign" in data:
            pubkey_server = { 
                "public_key_dh": data["pubkey_dh"],
                "public_key_sign": data["pubkey_sign"]
            }

        public_key_from_text = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), bytes.fromhex(pubkey_server["public_key_dh"]))

        shared_value = private_key_dh.exchange(ec.ECDH(), public_key_from_text)
        print(shared_value.hex())

        # Derive the shared key
        salt = os.urandom(16)
        kdf = PBKDF2HMAC(algorithm=hashes.SHA256(), length=32, salt=b'0123456789012345', iterations=100000)
        shared_key_main = kdf.derive(shared_value)

        print(shared_key_main.hex())

# Init message
sensor_init = {
    "type":  "simulation",
    "mode": 1,
    "pubkey": "%s" % private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex(),
    "pubserver": True,
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
client.on_message = on_message

#client.username_pw_set("server", password="servernode")
client.username_pw_set("node", password="smartmeternode")
#client.connect("10.0.0.31", 1884, 60)
client.connect("sendlab.nl", 11885, 60)

client.subscribe("node/" + sensor_id + "/message", qos=0)

print("Sending init message...")
client.publish("node/init", json.dumps(sensor_init))

timestamp = datetime.now()
temp = 21.4
humidity = 56.5
while ( 1 ):
    timediff = datetime.now() - timestamp
    if ( timediff.seconds > 1 ):
        data = {
            "id": sensor_id,
            "measurements": [{
                "timestamp": datetime.now(timezone.utc).isoformat(),
                "temperature": temp,
                "humidity": humidity,
            }],
        }
        #client.publish("node/data", json.dumps(data))
        temp = temp + random.random()*1 - 0.5
        humidity = humidity + random.random()*1 - 0.5
        timestamp = datetime.now()

    client.loop()
