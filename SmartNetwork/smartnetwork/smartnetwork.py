#!/usr/bin/python3
import time
from smartnetwork.smartnetwork import SmartNetwork

smartnetwork = SmartNetwork()

smartnetwork.debug = True
#smartnetwork.test  = True

smartnetwork.start()

print(smartnetwork)

while (1==1):
    time.sleep(10)

smartnetwork.stop()


