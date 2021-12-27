#!/usr/bin/python3

import time
import sys
from datetime import datetime, timezone

from influxdb_client import InfluxDBClient, Point, WritePrecision #pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

if len(sys.argv) != 2:
    print("syntax: clean.py smartnode_id")
    quit()

host = "http://localhost:8086"
org = "smartsensor"

token = "zkrK26xfHz9rvGY7rBqcvPadvgwojmtLgcv7Cuc0dlpNUMs9fhlBnsoi2oBHdmMDY0C7V-s90Clb5ApUIEmxvQ=="

influx = InfluxDBClient(url=host, token=token)

write  = influx.write_api(write_options=SYNCHRONOUS)
query  = influx.query_api()
delete = influx.delete_api()

id = str(sys.argv[1])
start = "1970-01-01T00:00:00Z"
stop = datetime.now(timezone.utc).isoformat()
delete.delete(start, stop, '_measurement="data" AND id="' + str(id) + '"', bucket='nodedata', org=org)
delete.delete(start, stop, '_measurement="info" AND id="' + str(id) + '"', bucket='nodeinfo', org=org)

