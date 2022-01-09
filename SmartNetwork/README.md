# SmartNetwork

The MQTT bus has been made smart with all kinds of messages and specific protocol.
It purpose is to create a safe sensor environment in which sensors can push data
and know that the integrity of the data is correct! This document is used to create
the documentation of this network.

## PM2 - Process Monitoring

To start PM2 process monitoring for the python file, use the following:
```python
pm2 start smartmeter.py --name SmartNetwork --interpreter python3
```