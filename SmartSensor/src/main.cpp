/*
 * Entry point.
 */

#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>
#include <XBee.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <Sparkfun_APDS9301_Library.h>
#include <Adafruit_MCP9808.h>

#include <avr/io.h>
#include <avr/wdt.h>

static XBee xbee;
static SoftwareSerial SoftSerial(3,4);
static ZBRxResponse response;
static StaticJsonDocument<128> json_buffer;

/* Sensor objects */
static Adafruit_SHT31 sht;
static APDS9301 apds;
static Adafruit_MCP9808 mcp;
static String output;

#ifndef wdt_reset
#define wdt_reset() __asm__ __volatile__("wdr")
#endif

static uint16_t sensor_id;

static void state_sleep();

/*static void set_xbee_sleep_mode()
{
	AtCommandRequest rq;
	uint8_t value = 1;
	uint8_t cmd[] = {'S', 'M'};

	rq.setCommand((uint8_t*)cmd);
	rq.setCommandValue(&value);
	rq.setCommandValueLength(sizeof(value));

	xbee.send(rq);
	delay(100);

	xbee.readPacketUntilAvailable();
	xbee.getResponse().reset();
}*/

#ifndef WDTO_8S
#define WDTO_8S 9
#endif

static void state_sleep()
{
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(10, LOW);
	digitalWrite(8, HIGH);

	cli();
	ADCSRA &= ~(1 << ADEN);
	wdt_enable(WDTO_8S);
	WDTCSR |= (1 << WDIE);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
	sei();
}

static void state_check_network()
{
	if(xbee.readPacket(500)) {
		if(xbee.getResponse().isAvailable()) {
			xbee.getResponse().reset();
		}
	}
}

static void state_transmit_sensor_data()
{
	ZBTxRequest tx;

	output = "";
	json_buffer.clear();
	json_buffer["rh"] = sht.readHumidity();
	json_buffer["id"] = sensor_id;
	json_buffer["li"] = apds.readLuxLevel();
	json_buffer["t"] = mcp.readTempC();

	serializeJsonPretty(json_buffer, output);

	tx.setPayload((uint8_t*)output.c_str());
	tx.setPayloadLength(output.length());
	tx.setAddress16(0x0);
	tx.setAddress64(0L);
	xbee.send(tx);
}

void setup()
{
	Serial.begin(9600);
	SoftSerial.begin(9600);
	Wire.begin();

	xbee.begin(SoftSerial);
	while(!Serial);

	wdt_disable();
	WDTCSR &= ~(1 << WDIE);
	Serial.println("Starting sensor..");
	pinMode(6, OUTPUT);
	digitalWrite(6, HIGH);

	pinMode(5, OUTPUT);
	digitalWrite(5, HIGH);

	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	pinMode(8, OUTPUT);
	digitalWrite(8, LOW);

	//set_xbee_sleep_mode();
	delay(100);
	sensor_id = rand() % 9000 + 1000;

	apds.begin(0x39);
	apds.setGain(APDS9301::LOW_GAIN);
	apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS);
	apds.setLowThreshold(0);
	apds.setHighThreshold(50);

	sht.begin();

	if(!mcp.begin(MCP9808_I2CADDR_DEFAULT)) {
		while(true);
	}

	mcp.setResolution(2);
	mcp.wake();
	delay(130);
}

void loop()
{
	Serial.println("Transmitting sensor data!");
	state_transmit_sensor_data();
	state_check_network();
	state_sleep();
}
