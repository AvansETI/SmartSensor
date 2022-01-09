#!/usr/bin/python3
"""
@author	    Maurice Snoeren
@contact	macsnoeren@gmail.com
@copyright	2021 (c) Avans Hogeschool
@license	GNUv3
@date	    28-12-2021
@version	1.0
@desciprion This script implements a SmartNode connection with the SmartNetwork.
"""

import os
import json
import base64
import random
from datetime import datetime, timezone

import paho.mqtt.client as mqtt # pip install paho-mqtt

# pip install cryptography
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

sensor_id = "_simulation_1"
pubkey_server = {}
shared_value: bytes = ""

# When the SmartNode has exchanged keys, this will be the key!!
private_key_ecc = "2ec2ebcc055d67427442e7083dabf6e77f345c0adcb909c9f8d5340634786705"
private_key_dh  = ec.derive_private_key(int(private_key_ecc, 16), ec.SECP256R1(), default_backend())
shared_value    = "443d3767d6ebf7c77b7e8d527cfb438f28a250d3dc66f287731ac4385b36fa25" # This should be stored when found!
shared_key      = bytes.fromhex(shared_value)

def aes256_encrypt(key, message):
    """Encrypt the message with the given key using the AES 256 algorithm"""
    try:
        message = bytes(message, 'utf-8')
        iv = os.urandom(16)
        backend = default_backend()
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
        encryptor = cipher.encryptor()
        padder = padding.PKCS7(128).padder()
        padded_data = padder.update(message) + padder.finalize()
        enc_content = encryptor.update(padded_data) + encryptor.finalize()
        return base64.b64encode(iv + enc_content).decode('utf-8')
    except Exception as e:
        print("aes256_encrypt error: %s" % str(e))
        return None

def aes256_decrypt(key, ciphertext):
    """Decrypt the message with the given key using the AES 256 algorithm"""
    try:
        ciphertext = base64.b64decode(ciphertext)
        iv = ciphertext[:16]
        enc_content = ciphertext[16:]
        backend = default_backend()
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
        unpadder = padding.PKCS7(128).unpadder()
        decryptor = cipher.decryptor()
        dec_content = decryptor.update(enc_content) + decryptor.finalize()
        real_content = unpadder.update(dec_content) + unpadder.finalize()
        return real_content.decode('utf-8')

    except Exception as e:
        print("aes256_encrypt error: %s" % str(e))
        return None

def on_connect(client, userdata, flags, rc):
    """MQTT callback method when a connection is made with the MQTT server. Note that
       it is wise to also subscribe to the topics in this method. When a reconnection
       occurs, you also subscribe to the topics."""
    print("Connected with result code "+str(rc))
    client.subscribe("node/" + sensor_id + "/message", qos=0)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    """MQTT callback method when a message is received of the topics that have been
       subscribed to."""
    print(msg.topic+" "+str(msg.payload))
    try:
        data = json.loads(msg.payload)

    except:
        print("Could not load the json: " + str(msg.payload))

    if msg.topic == "node/" + sensor_id + "/message":
        if "pubkey_dh" in data:
            public_key_from_text = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), bytes.fromhex(data["pubkey_dh"]))

            global shared_value
            shared_value = private_key_dh.exchange(ec.ECDH(), public_key_from_text)

            # The server sends a check message that contains SmartNetwork
            check = aes256_decrypt(shared_value, data["check"])
            if check != None and check == "SmartNetwork":
                print("Shared keys are the same ... yes!")
            else:
                print("Shared keys are NOT the same ... bummer!")

# SmartNode init message to initialize a SmartNode of mode 1
sensor_init = {
    "type":  "simulation",
    "mode": 1,
    "pubkey": "%s" % private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex(),
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

# MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set("node", password="smartmeternode")
client.connect("sendlab.nl", 11885, 60) # 11883/4 production, 11885 test

# Send the initialization message. If correctly processed by the server, the server
# sends back a message on node/<sensor-id>message
print("Sending init message...")
client.publish("node/init", json.dumps(sensor_init))

# Simulation of sampling temperature and humidity to simulate an active sensor
# TODO: This is not correctly implemented yet!
timestamp = datetime.now()
temp = 21.4
humidity = 56.5
while ( 1 ):
    timediff = datetime.now() - timestamp
    if ( timediff.seconds > 30 ): # Every 30 seconds
        data = {
            "id": sensor_id,
            "test": aes256_encrypt(shared_key, "Bericht van SmartNode!"),
            "measurements": [{
                "timestamp": datetime.now(timezone.utc).isoformat(),
                "temperature": temp,
                "humidity": humidity,
            }],
        }
        client.publish("node/data", json.dumps(data))
        temp = temp + random.random()*1 - 0.5
        humidity = humidity + random.random()*1 - 0.5
        timestamp = datetime.now()

    client.loop()
