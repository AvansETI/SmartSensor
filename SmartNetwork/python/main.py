#!/usr/bin/python3
import time
from smartnetwork.smartnetwork import SmartNetwork

host = "http://localhost:8086"
org = "smartsensor"

#token = "zkrK26xfHz9rvGY7rBqcvPadvgwojmtLgcv7Cuc0dlpNUMs9fhlBnsoi2oBHdmMDY0C7V-s90Clb5ApUIEmxvQ=="#ZqJdkWyrYtrfkybw1yBzA5p8eS6NcjfyIcT0PJ_R4j9N-NNbEAoMn-K_Ie95tM-61lTJ-wn89oaAD7AjfJvY3A=="
token = "zkrK26xfHz9rvGY7rBqcvPadvgwojmtLgcv7Cuc0dlpNUMs9fhlBnsoi2oBHdmMDY0C7V-s90Clb5ApUIEmxvQ=="

smartnetwork = SmartNetwork(host, org, token)

smartnetwork.debug = True

smartnetwork.start()
#smartnetwork.delete_all_node_info()
#smartnetwork.delete_all_node_data()
#smartnetwork.delete_all_node_alerts()

print(smartnetwork)

while (1==1):
    time.sleep(10)

smartnetwork.stop()


