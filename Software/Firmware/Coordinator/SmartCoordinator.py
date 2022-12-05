#!/usr/bin/python3

import serial
import logging
import threading
import time
import re
import json
import random
from datetime import datetime, timezone
import paho.mqtt.client as mqtt # pip install paho-mqtt

# The abbreviation of the measurements that has been defined
# MEASUREMENTS:loop_time (lt), temperature (te), humidity (hu), ligth (li), co2 (c2), GPIO_STATUS (gi), ANALOG_INPUT (ai), RS232_REC (rs)\n
measurements_mapping = {
    "lt": {
        "name": "loop_time",
        "description": "Loop time is the time how long it takes to go through all the tasks.",
        "unit": "ms"
    },
    "te": {
        "name": "temperature",
        "description": "Measured temperature.",
        "unit": "Celsius"
    },
    "hu": {
        "name": "humidity",
        "description": "Measured humidity.",
        "unit": "%"
    },
    "li": {
        "name": "light",
        "description": "Measurement of the ambient light.",
        "unit": "lux"
    },
    "c2": {
        "name": "co2",
        "description": "Measurement of the CO2.",
        "unit": "ppm"
    },
    "gi": {
        "name": "gpio",
        "description": "The status of the GPIO pins, based on the configuration.",
        "unit": "hex"
    },
    "ai": {
        "name": "analog",
        "description": "Is configured the analogue value of the respective pins.",
        "unit": "hex"
    },
    "rs": {
        "name": "rs232",
        "description": "The bytes that has been received on the RS232 connection. Setup gpio 6-7 as S!",
        "unit": "-"
    },
    "tv": {
        "name": "tvoc",
        "description": "The equivalent Total Volatile Organic Compound (eTVOC)",
        "unit": "ppb"
    },
    "ts": {
        "name": "timestamp",
        "description": "Is not a measurement, but is send!",
        "unit": "-"
    },
    "so": {
        "name": "sound",
        "description": "sound level",
        "unit": "db"
    },
    "pot": {
        "name": "pot",
        "description": "potmeter value",
        "unit": "-"
    }
}

# The abbreviation of the actuators that has been defined
# ACTUATORS:BOOT_MODE(bm), GPIO_SETUP (gs), GPIO_OUTPUT (go), RS232_SEND (rs)
actuators_mapping = {
    "bm": {
        "name": "boot_mode",
        "description": "Switch to boot mode to update the software.",
        "unit": "-"
    },
    "gs": {
        "name": "gpio_setup",
        "description": "Configureation of the gpio pins: (I)nput, (O)utput, (A)nalog, (P)TC, (N)ot_used, (S)erial: 0-3(I/O/A/N/P), 4-5(I/O/N/P), 6-7(I/O/N/P/S)",
        "unit": "-"
    },
    "go": {
        "name": "gpio",
        "description": "Set the state of the gpio pins that have been configured as output.",
        "unit": "hex"
    },
    "rs": {
        "name": "rs232",
        "description": "Send data characters to the rs232, not more that 25 character each time! Setup gpio 6-7 as S!",
        "unit": "-"
    }
}

# init_ids = [] # list with ids we have already sent an init message for
# add = False
# All the smartnodes that have been found
smartnodes = {}

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    
    for smartnode in smartnodes:
        client.subscribe("node/" + smartnode["name"] + "-" + smartnode["id"] + "/message", qos=0)     

# The callback for when the client receives a CONNACK response from the server.
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected MQTT disconnection. Will auto-reconnect")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    #print(msg.topic+" "+str(msg.payload))
    pass

def get_init_message(smartnode):
    print("get init message")
    measurements_line:str = smartnode["measurements"]
    actuators_line:str = smartnode["actuators"]

    measurements = []  
    actuators = []
    for m in measurements_line.split(":"):
        measurements.append(measurements_mapping[m])
    act = actuators_line.split(":")
    if (len(act) > 0):
        for a in actuators_line.split(":"):
            actuators.append(actuators_mapping[a])

    
    return {
        "type":  "smartnode",
        "mode": 0,
        "id": smartnode["id"], # smartnode["name"] + "-" + smartnode["id"],
        "name":  smartnode["name"],
        "measurements": measurements,
        # "actuators": actuators,
    }

def get_data_message(smartnode):
    measurements = {}
    for value in smartnode["values"]:
        for key in value:
            if re.match("^\d+.\d+$|^\d+$", str(value[key])):
                value[key] = float(value[key])
            
            if (key in measurements_mapping):
                measurements[measurements_mapping[key]["name"]] = value[key]

    if (measurements["timestamp"] == "2000-00-00T00:00:00"):
        measurements["timestamp"] = str(datetime.now());
        print("timestamp was false, it is now " + measurements["timestamp"])
    
    return {
        "id": smartnode["id"], # smartnode["name"] + "-" + smartnode["id"],
        "measurements": [measurements],
        "timestamp": measurements["timestamp"]
    }

client = mqtt.Client()
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_message = on_message

client.username_pw_set("node", password="smartmeternode")
client.connect("sendlab.nl", 11883, 60)
client.loop_start()


ser = serial.Serial('/dev/ttyUSB0') # /dev/ttyTHS1 on nano4

while (1):
    try:
        line = bytes(ser.readline()).decode('utf-8') # ser.readline().decode('utf-8')
        # print(line.rstrip())

        #INIT:86FF1312170E0932554E:smartnode-v1.2
        match = re.match("^INIT:(.+):(.+)$", line)
        if match:
            print("init match")
            id   = match.groups()[0]
            name = match.groups()[1]
            smartnodes[id] = { 
                "id": id,
                "name": name,
                "measurements": "",
                "actuators": "",
                "values": []
            }

        #MEA:86FF1312170E0932554E:lt:te:hu:li:c2:gi:ai:rs
        match = re.match("^MEA:([^:]+):(.+)$", line)
        if match:
            print("measurement match")
            id   = match.groups()[0]
            measurements = match.groups()[1]
            smartnodes[id]["measurements"] = measurements

        #ACT:86FF1312170E0932554E:bm:gs:go:rs
        match = re.match("^ACT:([^:]+):(.+)$", line)
        if match:
            print("actuators match")
            id   = match.groups()[0]
            actuators = match.groups()[1]
            smartnodes[id]["actuators"] = actuators

        #END:86FF1312170E0932554E
        # init: {'id': '86FF1312170E0932554E', 'name': 'smartnode-v1-2', 'measurements': 'lt:te:hu:li:c2:so', 'actuators': '', 'values': []}
        # data: {"id": "smartnode-v1-2-86FF1312170E0932554E", "measurements": [{"sound": 31.0, "loop_time": 0.0, "timestamp": "2000-00-00T00:00:00"}], "timestamp": "2000-00-00T00:00:00"}
        match = re.match("^END:(.+)$", line)
        if match:
            print("end match")
            id   = match.groups()[0]
            client.publish("node/init", json.dumps(get_init_message(smartnodes[id])))
            print("node/init", json.dumps(get_init_message(smartnodes[id])))

        #GWAV => TODO
        match = re.match("^GWAV\n$", line)
        if match:
            print("Matched GWAV")


        #86FF1312170E0932554E:te:22.7
        match = re.match("^([^:]+):([^:]+):(.+)$", line)
        if match:
            id    = match.groups()[0]
            key   = match.groups()[1]
            value = match.groups()[2]
            
            if not id in smartnodes:
                smartnodes[id] = {"id": id, "values": []}

            smartnodes[id]["values"].append({key: value})

            if ( key == "ts" ):
                if len(smartnodes[id]["values"]) <= 1:
                    print("MMMM??!")
                else:
                    pass
                    client.publish("node/data", json.dumps(get_data_message(smartnodes[id])))
                    print("node/data", json.dumps(get_data_message(smartnodes[id])))
                smartnodes[id]["values"] = []
    except:
        pass
    
client.loop_stop()


