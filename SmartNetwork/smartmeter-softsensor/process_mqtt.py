#!/usr/bin/python3

# mongoexport --db=SmartMeterData --collection=smart_meter_data_decoded --out dump-smart_meter_data_decoded.json

import json
import random
import time

try:
    f_in  = open('dump-smart_meter_data_decoded.json','r')
    f_out = open('result.csv','w')
    f_out.write("timestamp, signature, tariff, power_received_kw, power_delivered_kw, energy_delivered_1_kwh, energy_received_1_kwh, energy_delivered_2_kwh, energy_received_2_kwh\n")

except:
    print("Cannot open the file")

try:
    line = f_in.readline()

    while ( line ):
        data = json.loads(line)
        
        if ( data["signature"] == "2019-ETI-EMON-V01-695FA5-1640EF"):
            record = [
                "\"" + str(data["createdAt"]["$date"]) + "\"",
                "\"" + str(data["signature"]) + "\"",
                str(data["p1_decoded"]["tariff"]),
                str(data["p1_decoded"]["power"][1]["received"]["value"]),
                str(data["p1_decoded"]["power"][0]["delivered"]["value"]),
                str(data["p1_decoded"]["energy"][0]["delivered"]["value"]),
                str(data["p1_decoded"]["energy"][0]["received"]["value"]),
                str(data["p1_decoded"]["energy"][1]["delivered"]["value"]),
                str(data["p1_decoded"]["energy"][1]["received"]["value"])
            ]
            f_out.write( ",".join(record) + "\n" )

        line = f_in.readline()

    f_in.close()
    f_out.close()

except Exception as e:
    print("Could not process the line")
    print(e)
