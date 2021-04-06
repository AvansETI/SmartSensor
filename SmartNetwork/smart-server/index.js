var mqtt = require('mqtt');

console.log("test");

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
  })
})
 
client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  client.end()
})
