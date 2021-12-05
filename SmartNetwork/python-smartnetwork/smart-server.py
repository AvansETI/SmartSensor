#!/usr/bin/python3
import json
import random
from datetime import datetime, timezone
import dateutil # pip install python-dateutil
import paho.mqtt.client as mqtt # pip install paho-mqtt

from influxdb_client import InfluxDBClient, Point, WritePrecision # pip install influxdb-client
from influxdb_client.client.write_api import SYNCHRONOUS

mqtt_client = mqtt.Client()

# You can generate a Token from the "Tokens Tab" in the UI
token = "ZqJdkWyrYtrfkybw1yBzA5p8eS6NcjfyIcT0PJ_R4j9N-NNbEAoMn-K_Ie95tM-61lTJ-wn89oaAD7AjfJvY3A=="
org = "smartsensor"

influx_client = InfluxDBClient(url="http://localhost:8086", token=token)
write_api     = influx_client.write_api(write_options=SYNCHRONOUS)
query_api     = influx_client.query_api()

def alert(level, type, id, message):
    point = Point("alerts").tag("id", id).tag("level", level).tag("type", type);
    point.field("message", message)
    point.time(datetime.now(), WritePrecision.NS)
    write_api.write("nodedata", org, point)

def mqtt_send_message(id, message):
    mqtt_client.publish("node/" + str(id) + "/message", json.dumps(message))
    
#SQL injection!!
def check_node_exist(id):
    query = 'from(bucket: "nodeinfo")\
|> range(start: 2020-01-01T00:00:00Z)\
|> filter(fn: (r) => r["id"] == "' + id + '")\
|> filter(fn: (r) => r["_field"] == "validated")\
|> count()';

    result = query_api.query(org=org, query=query)
    if ( len(result) == 1 and len(result[0].records) == 1 and result[0].records[0].get_value() == 1 ): #exists
        return 1;
    elif (  len(result) == 1 and len(result[0].records) == 1 and result[0].records[0].get_value() > 1 ): #alert
        alert(10, "database", id, "Multiple id's found of this node (" + str(id) + "), please fix!");
        print("ALERT!!!"); # something wrong!
        return 1;
    else:
        return 0;

def process_node_data(data):
    if ( check_node_exist(data["id"]) ):
        for measurement in data["measurements"]:
            point = Point("data").tag("id", data["id"]);
            for item in measurement.keys():
                if ( item != "timestamp" ):
                    point.field(item, measurement[item]);
                    point.time(dateutil.parser.parse(measurement["timestamp"]), WritePrecision.NS);
        write_api.write("nodedata", org, point)
        mqtt_client.publish("node/" + str(data["id"]) + "/data", json.dumps(data)) # send it further!

    else:
        print("node id not found!");

def process_node_init(data):
    if ( not check_node_exist(data["id"]) ):
        point = Point("info").tag("id", data["id"]).tag("type", data["type"]).tag("name", data["name"]);
        point.tag("location", "none").tag("reference", "none"); # Values filled in later
        point.field("pecc", data["pecc"]).field("pdhk", data["pdhk"]).field("nonce", data["nonce"]);
        point.field("hash", data["hash"]).field("sign", data["sign"]);
        point.field("measurements", json.dumps(data["measurements"]));
        point.field("actuators", json.dumps(data["measurements"]));
        point.field("validated", 0);
        write_api.write("nodeinfo", org, point)
        mqtt_send_message(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome, you have been added!"});
    else:
        mqtt_send_message(data["id"], {"status": 1, "time": datetime.now(timezone.utc).isoformat(), "message": "Welcome back!"});

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    if ( msg.topic == "node/data" ):
        try:
            process_node_data(json.loads(msg.payload))
        except:
            print("Error processing node data: " + msg.payload)

    if ( msg.topic == "node/init" ):
        try:
            process_node_init(json.loads(msg.payload));
        except:
            print("Error processing node init request: " + msg.payload);

    if ( msg.topic == "node/info" ):
        try:
            pass #process_node_info(json.loads(msg.payload));
        except:
            print("Error processing node info: " + msg.payload);

mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

mqtt_client.username_pw_set("server", password="servernode")
#mqtt_client.connect("10.0.0.31", 1884, 60)
mqtt_client.connect("sendlab.nl", 11884, 60)

mqtt_client.subscribe("node/init", qos=0)
mqtt_client.subscribe("node/data", qos=0)
mqtt_client.subscribe("node/info", qos=0)

mqtt_client.loop_forever();
