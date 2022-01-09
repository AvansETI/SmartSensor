"""
@author	     Maurice Snoeren
@contact	 macsnoeren@gmail.com
@copyright	 2021 (c) Avans Hogeschool
@license	 GNUv3
@date	     14-12-2021
@version	 0.1
@description Under construction, initialization correctly implemented, receiving data not yet, should be signed or so
"""

import os
import json
import base64
from datetime import datetime, timezone
import dateutil
import sqlite3

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

# pip install cryptography
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

from smartnetwork.smartnode import SmartNode

class SmartNode1 (SmartNode):
    """This class implements how the SmartNode using mode 1 is processed by the SmartNetwork."""

    def __init__(self, smartnetwork):
        """Create instance of a SmartNode1. This SmartNode uses ECDH algoritm to exchange a secret key with each
           other. For this class the SECP256R1 curve is used."""
        super().__init__(smartnetwork)

        # Generate a private key for use in the exchange using stored keys in the configuration
        self.private_key_dh   = ec.derive_private_key(int(smartnetwork.config["ecc"]["dh"]["private"], 16), ec.SECP256R1(), default_backend())
        
        # Create the database connection
        self.sqlite = sqlite3.connect(smartnetwork.config["sqlitedb"]["smartnodes"])
        self.initialize_db()

    def initialize_db(self):
        """Initialize the database and create the tables if they do not exist."""
        sql = """CREATE TABLE IF NOT EXISTS smartnodes (
	             id TEXT PRIMARY KEY,
	             public_key TEXT NOT NULL,
	             shared_key TEXT NOT NULL,
	             public_server TEXT NOT NULL,
                 created_at TEXT DEFAULT CURRENT_TIMESTAMP
            );"""
        self.sqlite.cursor().execute(sql)
        self.sqlite.commit()

    def add_smartnode_secrets(self, id, public_key, shared_key, public_server):
        """Add the SmartNode secrets to the database only if only the SmartNode does not exist in the table!"""
        if self.get_smartnode_shared_key(id) == None:
            sql = "INSERT INTO smartnodes (id, public_key, shared_key, public_server) VALUES (?, ?, ?, ?)"
            self.sqlite.cursor().execute(sql, (id, public_key, shared_key.encode('utf-8'), public_server))
            self.sqlite.commit()
            print("Adding new secrets for: " + id)
            print(self.sqlite.cursor().lastrowid)
        else:
            self.debug_print("add_smartnode_secrets: Secrets already stored for " + str(id))

    def get_smartnode_shared_key(self, id):
        """Return the shared key of the node. If not known, the method returns None."""
        sql = "SELECT shared_key FROM smartnodes WHERE id=?"
        cursor = self.sqlite.cursor()
        cursor.execute(sql, (id,))
        record = cursor.fetchone()

        if record != None:
            shared_value:str = record[0].decode('utf-8')
            return bytes.fromhex(shared_value)

        return None

    def get_public_key_dh(self):
        """Returns the public key that is stored in the configuration of the server. This is an ECC
           based public key. This key is used for the key exchange Diffie-Hellman: ECDH."""
        return "%s" % self.private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()

    def aes256_encrypt(self, key, message):
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
            self.debug_print("aes256_encrypt error: %s" % str(e))
            return None

    def aes256_decrypt(self, key, ciphertext):
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
            self.debug_print("aes256_decrypt error: %s" % str(e))
            return None

    def add_node_to_network(self, data):
        """Add the node to the network when the required security details have been exchanged.
           TODO: Store the information of the SmartNode, so next time it used the already exchanged
                 credentials."""
        required_fields = ("id", "type", "name", "mode", "measurements", "actuators", "pubkey") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("add_node_to_network: required field '" + required_field + " missing.")
                return

        try:
            # Calculate the shared key that can be used to define the signing keys
            public_key_from_text = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), bytes.fromhex(data["pubkey"]))
            shared_value         = self.private_key_dh.exchange(ec.ECDH(), public_key_from_text)

            self.add_smartnode_secrets(data["id"], data["pubkey"], shared_value.hex(), self.get_public_key_dh())

            # Add the SmartNode to the info bucket
            point = Point("info").tag("id", data["id"]).tag("type", data["type"]).tag("name", data["name"])
            point.tag("location", "none").tag("reference", "none").tag("mode", data["mode"]) # Values filled in later
            point.field("measurements", json.dumps(data["measurements"]))
            point.field("actuators", json.dumps(data["measurements"]))
            point.field("validated", 0)
            if not self.smartnetwork.test:
                self.smartnetwork.write.write("nodeinfo", self.smartnetwork.org, point)
            
            # When the SmartNode does not has the public key, it can request the public key from the server
            # Note that this is not secure, while an active man-in-the-middle attacker, can compromise the communication
            self.send_message_to_node(data["id"], {
                "status": 1, 
                "time": datetime.now(timezone.utc).isoformat(), 
                "message": "Welcome, you have been added to the network!", 
                "pubkey_dh": self.get_public_key_dh(),
                "check": self.aes256_encrypt(self.get_smartnode_shared_key(data["id"]), "SmartNetwork")
            })
        except Exception as e:
            self.debug_print("add_node_to_network: Could not create the secrets: %s!" % str(e))

    def process_node_data(self, data):
        """Process the data that has been received by the SmartNode.
           TODO: Work in progress..."""
        required_fields = ("id", "measurements") # Check required fields
        for required_field in required_fields:
            if ( not required_field in data ):
                print("process_node_data: required field '" + required_field + " missing.")
                return

        shared_key = self.get_smartnode_shared_key(data["id"])
        print(self.aes256_decrypt(shared_key, data["test"]))

        for measurement in data["measurements"]:
            point = Point("data").tag("id", data["id"])
            for item in measurement.keys():
                if ( item != "timestamp" ):
                    point.field(item, measurement[item])
                    point.time(dateutil.parser.parse(measurement["timestamp"]), WritePrecision.NS)

        # TODO: How to check the signature of the message!
        signature_correct = False

        if not self.smartnetwork.test and signature_correct:
            self.smartnetwork.write.write("nodedata", self.smartnetwork.org, point)
            self.smartnetwork.mqtt.publish("node/" + str(data["id"]) + "/data", json.dumps(data)) # relay it further!
        else:
            self.debug_print("process_node_data: signature incorrect!")

    def __str__(self):
        """Default Python method to convert the class to a string represntation"""
        return 'SmartNode (mode:{})' % 1

    def __repr__(self):
        """Default Python method to convert the class to a string represntation"""
        return 'SmartNode (mode:{})' % 1
        