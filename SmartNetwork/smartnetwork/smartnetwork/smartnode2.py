import os
import json
import base64
from datetime import datetime, timezone
import dateutil

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

# pip install cryptography
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

"""
Author: Maurice Snoeren <mac.snoeren(at)avans.nl>
Version: 0.1 beta (use at your own risk)
Date: 7-4-2021
"""

class SmartNode1:

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode1. This SmartNode uses ECDH algoritm to exchange a secret key with each
           other. For this class the SECP256R1 curve is used."""
        super(SmartNode1, self).__init__()

        # Debugging on or off!
        self.debug = False

        self.smartnetwork = smartnetwork

        # Generate a private key for use in the exchange using stored keys in the configuration
        self.private_key_dh   = ec.derive_private_key(int(smartnetwork.config["ecc"]["dh"]["private"], 16), ec.SECP256R1(), default_backend())
        self.private_key_sign = ec.derive_private_key(int(smartnetwork.config["ecc"]["sign"]["private"], 16), ec.SECP256R1(), default_backend())
        self.shared_keys      = {}

    def get_public_key_dh(self):
        return "%s" % self.private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()

    def get_public_key_sign(self):
        return "%s" % self.private_key_sign.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()

    def debug_print(self, message):
        """When the debug flag is set to True, all debug messages are printed in the console."""
        if self.debug:
            print("DEBUG: " + message)

    def send_message_to_node(self, id, message):
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/message", json.dumps(message))

    def send_event_to_node(self, id, event):
        self.smartnetwork.mqtt.publish("node/" + str(id) + "/event", json.dumps(event))

    def aes256_encrypt(self, key, message):
        message = bytes(message, 'utf-8')
        iv = os.urandom(16)
        backend = default_backend()
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
        encryptor = cipher.encryptor()
        padder = padding.PKCS7(128).padder()
        padded_data = padder.update(message) + padder.finalize()
        enc_content = encryptor.update(padded_data) + encryptor.finalize()
        return base64.b64encode(iv + enc_content).decode('utf-8')

    def aes256_decrypt(self, key, ciphertext):
        ciphertext = base64.b64decode(ciphertext)
        iv = ciphertext[:16]
        enc_content = ciphertext[16:]
        backend = default_backend()
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
        unpadder = padding.PKCS7(128).unpadder()
        decryptor = cipher.decryptor()
        dec_content = decryptor.update(enc_content) + decryptor.finalize()
        real_content = unpadder.update(dec_content) + unpadder.finalize()
        return str(real_content)

    def add_node_to_network(self, data):
        required_fields = ("id", "type", "name", "mode", "measurements", "actuators", "pubkey") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("add_node_to_network: required field '" + required_field + " missing.")
                return

        # Add the SmartNode to the info bucket
        point = Point("info").tag("id", data["id"]).tag("type", data["type"]).tag("name", data["name"])
        point.tag("location", "none").tag("reference", "none").tag("mode", data["mode"]) # Values filled in later
        point.field("measurements", json.dumps(data["measurements"]))
        point.field("actuators", json.dumps(data["measurements"]))
        point.field("validated", 0)
        if not self.smartnetwork.test:
            self.smartnetwork.write.write("nodeinfo", self.smartnetwork.org, point)

        # Calculate the shared key that can be used to define the signing keys
        public_key_from_text = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), bytes.fromhex(data["pubkey"]))
        shared_value         = self.private_key_dh.exchange(ec.ECDH(), public_key_from_text)

        # Derive the shared key
        kdf = PBKDF2HMAC(algorithm=hashes.SHA256(), length=32, salt=b'0123456789012345', iterations=100000)
        shared_key_main = kdf.derive(shared_value)

        kdf = PBKDF2HMAC(algorithm=hashes.SHA256(), length=32, salt=os.urandom(16), iterations=100000)
        shared_key_session = kdf.derive(shared_value)

        self.shared_keys[data["id"]] = {
            "public_key"        : data["pubkey"],
            "shared_key"        : shared_value,
            "shared_key_main"   : shared_key_main,
            "shared_key_session": shared_key_session
        }

        # When the SmartNode does not has the public key, it can request the public key from the server
        # Note that this is not secure, while an active man-in-the-middle attacker, can compromise the communication
        if "pubserver" in data and data["pubserver"] == True:
            self.send_message_to_node(data["id"], {
                "status": 1, 
                "time": datetime.now(timezone.utc).isoformat(), 
                "message": "Welcome, you have been added to the network!", 
                "pubkey_dh": self.get_public_key_dh(), 
                "pubkey_sign": self.get_public_key_sign(),
                "session": self.aes256_encrypt(shared_key_main, shared_key_session.hex()),
            })
        else:
            self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome, you have been added to the network!", })

    def welcome_node_to_network(self, data):
        self.send_message_to_node(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome back to the network!"})

    def process_node_data(self, data):
        required_fields = ("id", "measurements") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("process_node_data: required field '" + required_field + " missing.")
                return

        for measurement in data["measurements"]:
            point = Point("data").tag("id", data["id"])
            for item in measurement.keys():
                if ( item != "timestamp" ):
                    point.field(item, measurement[item])
                    point.time(dateutil.parser.parse(measurement["timestamp"]), WritePrecision.NS)
        if not self.smartnetwork.test:
            self.smartnetwork.write.write("nodedata", self.smartnetwork.org, point)
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/data", json.dumps(data)) # relay it further!

    def process_node_info(self, data):
        self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/info", json.dumps(data)) # relay it further!

    def __str__(self):
        return 'SmartNode' #: {}:{}'.format(self.host, self.port)

    def __repr__(self):
        return '<SmartNode>' # {}:{} id: {}>'.format(self.host, self.port, self.id)
