#include <Arduino.h>

#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>


#include "config.h"

EthernetClient ethClient;
PubSubClient mqtt_client(ethClient);


byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0x01, 0x8B };

String data;

void setup() {
	Serial.begin(9600);
	pinMode(8, OUTPUT);
	// Ethernet shield configuration
	Ethernet.begin(mac);
	delay(1500); // Allow hardware to stabilize
	mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);

	while(!mqtt_client.connected()) {
		if(mqtt_client.connect("Coordinator")) {
			mqtt_client.publish(MQTT_TOPIC,"Connected");
		} else
		{
			delay(2000);
		}
	}
	
}

void loop() {	
	if(Serial.available()>0) { 
		data = Serial.readStringUntil('}')+'}'; 
		if(data.length() > 1) {
			if(data.substring(0,1).equals("{") &&
			data.substring(data.length() - 1, data.length()).equals("}")) {
				mqtt_client.publish(MQTT_TOPIC,data.c_str()); 
			}

		}
		
	}
	Serial.flush();
	delay(10);
}