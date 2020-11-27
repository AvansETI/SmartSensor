/*
 * SmartSensor main
 * 
 * @author Michel Megens
 * @email  michel@michelmegens.net
 * @author Maurice Snoeren
 * @email  mac.snoeren@avans.nl
 */

#include <stdlib.h>
#include <Arduino.h>

#include <HDC1080.h>
#include <XBee.h>
#include <Adafruit_VEML7700.h>
#include <SmartSensor.h>

void loop()
{
	auto sensor = smartsensor::Application::Instance();

	sensor->enableHumiditySensor();
	sensor->enableLightSensor();
	sensor->enableXBee();
	sensor->sleepXBee(HIGH);

	delay(800); // Sample time

	sensor->measureAndSend();

	delay(2000);
}

void test()
{
}

static void setupHAT()
{
    pinMode(HAT_AIO1, INPUT);
    pinMode(HAT_AIO2, INPUT);
    pinMode(HAT_AIO3, INPUT);
    pinMode(HAT_AIO4, INPUT);
    pinMode(HAT_AIO5, INPUT);
    pinMode(HAT_AIO6, INPUT);

    pinMode(HAT_DIO1, INPUT);
    pinMode(HAT_DIO2, INPUT);
    pinMode(HAT_DIO3, INPUT);
    pinMode(HAT_DIO4, INPUT);
    pinMode(HAT_DIO5, INPUT);
    pinMode(HAT_DIO6, INPUT);
    pinMode(HAT_DIO7, INPUT);
    pinMode(HAT_DIO31, INPUT);
}

// Configure the Atmega according the hardware design!
void setup()
{
	Serial.begin(9600, SERIAL_8N1);
	SPI.begin();
	Wire.begin();

    pinMode(VBAT_ADC0, INPUT);  //Battery measurement
    pinMode(INTA_ADC3, OUTPUT); // Realtime clock: /INTA
    //digitalWrite(INTA_ADC3, LOW); // ??

    pinMode(HDC1080_IO6, OUTPUT);   // HDC1080 Humidity/Temp On/Off
    digitalWrite(HDC1080_IO6, LOW); // Switch HDC1080 default off

    pinMode(LED_IO8, OUTPUT);
    pinMode(Vadap_IO9, INPUT); // When adapter is plugged in 5V (Does it work?)
    
    pinMode(XBEE_SLEEP, OUTPUT);

    pinMode(XBEE_ON_OFF, OUTPUT); // XBee module

    pinMode(AVR_RX, INPUT); // Soft UART??
    pinMode(AVR_TX, OUTPUT); // ??

    pinMode(VEML7700_IO5, OUTPUT); // Light sensor

	auto instance = smartsensor::Application::Instance();
	instance->begin();

    setupHAT();
}
