import sys
import base64
import json

import cryptography
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF

if len(sys.argv) != 2:
    print("Syntax: ecdh_test.py <config_file>")
    quit()

# Read the config file
try:
    config_json = open(sys.argv[1], "r").read()
    config = json.loads(config_json)

except Exception as e:
    print("Cannot read the config.json file '{}', which is required for execution." % sys.argv[1])
    quit()

print(config["ecc"]["dh"]["private"])
print(config["ecc"]["sign"]["private"])

# Generate a private key for use in the exchange.
private_key_dh   = ec.derive_private_key(int(config["ecc"]["dh"]["private"], 16), ec.SECP256R1(), default_backend())
private_key_sign = ec.derive_private_key(int(config["ecc"]["sign"]["private"], 16), ec.SECP256R1(), default_backend())

test = {
    "dh": {
        "private": "%x" % private_key_dh.private_numbers().private_value,
        "public" : "%s" % private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()
    },
    "sign": {
        "private": "%x" % private_key_sign.private_numbers().private_value,
        "public" : "%s" % private_key_sign.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()
    }
}

print("TEST:")
print( json.dumps(test, indent=4) )
print("REAL:")
print( json.dumps(test, indent=4) )

print( test["dh"]["public"] == config["ecc"]["dh"]["public"] )
print( test["sign"]["public"] == config["ecc"]["sign"]["public"] )
print( test["dh"]["private"] == config["ecc"]["dh"]["private"] )
print( test["sign"]["private"] == config["ecc"]["sign"]["private"] )

# Get a public key
public_key_from_text = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), bytes.fromhex(test["dh"]["public"]))

print( "public from text: 0x%s" % public_key_from_text.public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex())