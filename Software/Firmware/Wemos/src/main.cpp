// Avans University of Applied Sciences (Avans Hogeschool)
// Lectoraat Smart Energy
// Project: Smart Sensor
// Author: Maurice Snoeren
// Date  : 19-12-2021
//
// Add Wi-Fi gateway functionality to the SmartSensor as a pants module!
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <fsm.h>
#include <Queue.h>

// Create the wifi-client to connect to the Internet
WiFiClient client;

// Create the MQTT client to connect to a MQTT Broker (server)
PubSubClient mqtt;

// Finite state machine
enum FSM_STATES {
  STATE_WIFI,
  STATE_MQTT,
  STATE_WAIT_ON_DATA,
  STATE_PROCESS_MQTT_DATA,
  STATE_PROCESS_SENSOR_DATA,
  STATES_TOTAL // Add this one always!
};

// Finite state machine events
enum FSM_EVENTS {
  EVENT_MQTT_DATA_RECEIVED,
  EVENT_SENSOR_DATA_RECEIVED,
  EVENT_READY,
  EVENT_ERROR,
  EVENT_STATE_EXECUTED, // Add this one always!
  EVENTS_TOTAL          // Add this one always!
};

// Finite state machine callback methods forward declarations
void preWifi();
void loopWifi();
void postWifi();
void preMqtt();
void loopMqtt();
void postMqtt();
void preWaitOnData();
void loopWaitOnData();
void postWaitOnData();
void preMqttData();
void loopMqttData();
void postMqttData();
void preSensorData();
void loopSensorData();
void postSensorData();

//FSM
FSM fsm(STATES_TOTAL, EVENTS_TOTAL, false);

constexpr char MQTT_SERVER[] = "sendlab.nl";
constexpr int  MQTT_PORT     = 11883;

// Timer method for timing purposes
Queue<String, 40> mqttMessageQueue;
unsigned long timer;
StaticJsonDocument<4096> jsondoc;

void callbackMQTT(char* topic, byte* pl, unsigned int length) {
  Serial.printf("MQTT message received: %s\n", topic);
  
  String payload = "";
  for (unsigned int i=0;i<length;i++) {
    payload += (char)pl[i];
  }

  mqttMessageQueue.add(String(topic), false);
  mqttMessageQueue.add(payload, false);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // Switch on and off the led!
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);

  // For debugging purposes
  Serial.begin(9600);
  Serial.printf_P(PSTR("\n\nSdk version: %s\n"),   ESP.getSdkVersion());
  Serial.printf_P(PSTR("Core Version: %s\n"),      ESP.getCoreVersion().c_str());
  Serial.printf_P(PSTR("Boot Version: %u\n"),      ESP.getBootVersion());
  Serial.printf_P(PSTR("Boot Mode: %u\n"),         ESP.getBootMode());
  Serial.printf_P(PSTR("CPU Frequency: %u MHz\n"), ESP.getCpuFreqMHz());
  Serial.printf_P(PSTR("Reset reason: %s\n"),      ESP.getResetReason().c_str());

  // Add the state method to the FSM
  fsm.addState(STATE_WIFI,                preWifi, loopWifi, postWifi);
  fsm.addState(STATE_MQTT,                preMqtt, loopMqtt, postMqtt);
  fsm.addState(STATE_WAIT_ON_DATA,        preWaitOnData, loopWaitOnData, postWaitOnData);
  fsm.addState(STATE_PROCESS_MQTT_DATA,   preMqttData, loopMqttData, postMqttData);
  fsm.addState(STATE_PROCESS_SENSOR_DATA, preSensorData, loopSensorData, postSensorData);

  // Add the events to the FSM
  fsm.addTransition(STATE_WIFI, EVENT_READY, STATE_MQTT);
  fsm.addTransition(STATE_MQTT, EVENT_READY, STATE_WAIT_ON_DATA);
  fsm.addTransition(STATE_WAIT_ON_DATA, EVENT_MQTT_DATA_RECEIVED, STATE_PROCESS_MQTT_DATA);
  fsm.addTransition(STATE_PROCESS_MQTT_DATA, EVENT_READY, STATE_WAIT_ON_DATA);  
  fsm.addTransition(STATE_WAIT_ON_DATA, EVENT_SENSOR_DATA_RECEIVED, STATE_PROCESS_SENSOR_DATA);
  fsm.addTransition(STATE_PROCESS_SENSOR_DATA, EVENT_READY, STATE_WAIT_ON_DATA);
  fsm.addTransition(STATE_WAIT_ON_DATA, EVENT_ERROR, STATE_WIFI);
  fsm.addTransition(STATE_MQTT, EVENT_ERROR, STATE_WIFI);

  // Some mqtt configuration
  mqtt.setClient(client); // Setup the MQTT client
  mqtt.setBufferSize(1024); // override MQTT_MAX_PACKET_SIZE
  mqtt.setCallback(callbackMQTT);
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);

  fsm.setup(STATE_WIFI, EVENT_STATE_EXECUTED);
}

// Ardiuno loop
void loop() {   
  mqtt.loop();
  fsm.loop();
}

void preWifi() {
  if ( !WiFi.isConnected() ) { 
    WiFi.begin("MaCMaN_GUEST", "GUEST@MACMAN"); // Connect to the Wi-Fi (if not known use WifiManager from tzapu!)
    Serial.printf_P(PSTR("Setup Wi-Fi:"));
    while ( WiFi.status() != WL_CONNECTED ) {
        delay(500);
        Serial.printf_P(PSTR("."));
    }
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
  }
}

void loopWifi() {
  if ( WiFi.isConnected() ) {
    Serial.println();
    Serial.printf_P(PSTR("Connected:"));
    Serial.println(WiFi.localIP());

    fsm.raiseEvent(EVENT_READY);
  }
}

void postWifi() { }

void preMqtt() {
  if ( WiFi.status() != WL_CONNECTED ) { // If we are not connected, raise an error
    fsm.raiseEvent(EVENT_ERROR);
  }
}

void loopMqtt() {
  if ( WiFi.status() != WL_CONNECTED ) { // If we are not connected, raise an error
    fsm.raiseEvent(EVENT_ERROR);

  } else {
    char mqttClientId[15] = "";
    sprintf_P(mqttClientId, PSTR("SNGW-%04X"), system_get_chip_id());
    Serial.printf_P(PSTR("mqtt ID: %s\n"), mqttClientId);
    if ( mqtt.connect(mqttClientId, "node", "smartmeternode") ) {
      if ( mqtt.subscribe("node/test/data") ) {//node/+/data") ) {
        Serial.printf_P(PSTR("Subscribed to node/+/data!\n"));
      }
      fsm.raiseEvent(EVENT_READY);
      Serial.printf_P(PSTR("MQTT CONNECTED!\n"));

    } else {
      Serial.printf_P(PSTR("MQTT NOT CONNECTED!"));
      Serial.printf_P(PSTR("MQTT State: %d\n"), mqtt.state());
      Serial.printf_P(PSTR("WiFi State: %d\n"), WiFi.status());
    }

    delay(1000);
  }
}

void postMqtt() {}

void preWaitOnData() {
  timer = millis();
}

void loopWaitOnData() {
  if ( WiFi.status() != WL_CONNECTED || !mqtt.connected() ) { // If we are not connected, raise an error
    fsm.raiseEvent(EVENT_ERROR);
  }

  if ( millis() > (timer+5000) ) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle led each 5 seconds
    timer = millis();
    Serial.printf("Total messages: %d\n", mqttMessageQueue.size());
  }

  // Process the MQTT message queue
  while ( mqttMessageQueue.size() > 0 ) {
    String *topic   = mqttMessageQueue.pop();
    String *message = mqttMessageQueue.pop();

    Serial.printf("Topic: %s\n", topic->c_str());

    DeserializationError err = deserializeJson(jsondoc, message->c_str());
    if (err) {
      Serial.println("No JSON: " + String(err.c_str()));
    
    } else {
      String event = jsondoc["event"];
      Serial.println("JSON EVENT: " + event);
    }
  }



}

void postWaitOnData() {}
void preMqttData() {}
void loopMqttData() {}
void postMqttData() {}
void preSensorData() {}
void loopSensorData() {}
void postSensorData() {}
