# SmartMeter

Another project is the SmartMeter project. This is a project that also uses the MQTT server. This project focus on teachning people about the energy transition using hardware that the people can solder themselves. This hardware is connected to the the SmartMeter at their house and the data is gathered using our MQTT server.

## SmartNetwork

So, this python file listens to the MQTT server for SmartMeter messages. When a message is received from, then the data will be published to the SmartNetwork. All the data is then immediatly available on the SmartNetwerk landscape. The python file also sends the appropiate node/init message for each SmartMeter. That means that every SmartMeter becomes a SmartNode on the SmartNetwork.


## Know issues

The python file that processes the SmartMeter's, developed by the SmartMeter project, is not working well. During execution, the memory consumption increases. Eventually, the scipt stops running and it needs to be restarted. This issues has not been resolved yet. That means that the MQTT server stops working and that this influences the SmartNetwork as well.
