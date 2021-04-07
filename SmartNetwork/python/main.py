#!/usr/bin/python3
import time
from smartnetwork import SmartNetwork

host = "http://localhost:8086"
org = "smartsensor"
token = "ZqJdkWyrYtrfkybw1yBzA5p8eS6NcjfyIcT0PJ_R4j9N-NNbEAoMn-K_Ie95tM-61lTJ-wn89oaAD7AjfJvY3A=="

smartnetwork = SmartNetwork(host, org, token)

smartnetwork.debug = True

smartnetwork.start()

print(smartnetwork)

time.sleep(10)

smartnetwork.stop()


