# SmartNetwork

The SmartNetwork is developed by the research group Smart Energy to create a data sharing network. Initially, SmartNodes connected to the SmartNetwork to exchange their measurement data. The SmartNodes have also the ability to control appliances and therefore controllers on the SmartNetwork can control the appliances as well. It is a MQTT based network that is controlled by an agent. Eventually you do not want that someone perform unauthorized control of your actuators! Or you do not want that someone is able to change the data send by your sensors. Besides the SmartNodes, everyone is able to connect to this network. If you implement the protocol, then it is easy to participate to the network!

## MQTT

The MQTT bus has been made smart with all kinds of messages and specific protocol.
It purpose is to create a safe sensor environment in which sensors can push data
and know that the integrity of the data is correct! This document is used to create
the documentation of this network.

## PM2 - Process Monitoring

To start PM2 process monitoring for the python file, use the following:
```python
pm2 start smartmeter.py --name SmartNetwork --interpreter python3
```