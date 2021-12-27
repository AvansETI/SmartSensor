import sys
import base64
import json

import cryptography
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF

# Generate a private key for use in the exchange.
private_key_dh = ec.generate_private_key(
    ec.SECP256R1()
)

signature_algorithm = ec.ECDSA(hashes.SHA256())
private_key_sign = ec.generate_private_key(
    ec.SECP256R1()
)

# Make private and public keys from the private value + curve
#priv_key = ec.derive_private_key(private_value, curve, default_backend())
#pub_key = priv_key.public_key()

config = {
    "dh": {
        "private": "%x" % private_key_dh.private_numbers().private_value,
        "public" : "%s" % private_key_dh.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()
    },
    "sign": {
        "private": "%x" % private_key_sign.private_numbers().private_value,
        "public" : "%s" % private_key_sign.public_key().public_bytes(serialization.Encoding.X962, serialization.PublicFormat.CompressedPoint).hex()
    }
}

print( json.dumps(config, indent=4) )
