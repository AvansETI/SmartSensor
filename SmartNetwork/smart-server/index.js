const mqtt    = require('mqtt');
const express = require('express')
const http    = require('http')
const os      = require('os')

const InfluxDB = require('influxdb-v2')

const influxdb = new InfluxDB ({
  host: 'localhost',
  protocol: 'http',
  port: 8086,
  token: 'ZqJdkWyrYtrfkybw1yBzA5p8eS6NcjfyIcT0PJ_R4j9N-NNbEAoMn-K_Ie95tM-61lTJ-wn89oaAD7AjfJvY3A=='
});

const app = express()

influxdb.query(
  { org: 'smartsensor' },
  { query: 'from(bucket: "nodeinfo") |> range(start: -100h)' }
).then( result => {
  console.log(result);
});


var client  = mqtt.connect('mqtt://sendlab.nl:11884', {
    username: 'server',
    password: 'servernode' 
  });
 
client.on('connect', function () {
  console.log("connected!");
  client.subscribe('node/init', function (error, message) {
    if (!error) {
      console.log(message);
    }
  });

  client.subscribe('node/data', function (error, message) {
    if (!error) {
      console.log(message);
    }
  });

});
 
client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  client.end()
})
