#!/usr/bin/python3

# https://www.influxdata.com/blog/getting-started-with-python-and-influxdb-v2-0/

# pip3 install --upgrade influxdb-client

import influxdb_client
from influxdb_client import InfluxDBClient
from influxdb_client.client.write_api import SYNCHRONOUS

client = InfluxDBClient(url="http://localhost:9999", token='Uhc2SHBjcDaNuYmDJnOsmBh-3RmGFgvrjgeRn2dMvPflWYb4QXcroBS_F3-UUvv9GJaHEP1ggoFqlCqyki4RMg==', org='smartsensor')

write_api = client.write_api(write_options=SYNCHRONOUS)

p = influxdb_client.Point("nodedata").tag("location", "Prague").field("temperature", 25.3)

write_api.write(bucket='nodes', org='smartsensor', record=p)


