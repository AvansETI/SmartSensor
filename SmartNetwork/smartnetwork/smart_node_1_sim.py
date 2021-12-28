#!/usr/bin/python3
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

# Generate a private key for use in the exchange.
private_key_dh = ec.generate_private_key(
    ec.SECP256R1()
)

def aes256_encrypt(key, message):
    message = bytes(message, 'utf-8')
    iv = os.urandom(16)
    backend = default_backend()
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
    encryptor = cipher.encryptor()
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(message) + padder.finalize()
    enc_content = encryptor.update(padded_data) + encryptor.finalize()
    return base64.b64encode(iv + enc_content).decode('utf-8')

def aes256_decrypt(key, ciphertext):
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

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("node/" + sensor_id + "/message", qos=0)

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

        print("session")
        print(aes256_decrypt(shared_value, data["session"]) )

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
