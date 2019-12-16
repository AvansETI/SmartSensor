#include <SmartSensor.h>
#include <HDC1080.h>
#include <XBee.h>
#include <Adafruit_VEML7700.h>

// TODO: fix? Move declartion to a neater place
HDC1080 rh;
Adafruit_VEML7700 light_sensor;

void driver_init()
{
	rh.begin(HDC1080_I2C_ADDR);
	light_sensor.begin();

	light_sensor.setGain(VEML7700_GAIN_1);
	light_sensor.setIntegrationTime(VEML7700_IT_800MS);
}

void enableHumiditySensor()
{
	digitalWrite(HDC1080_IO6, HIGH);
}

void disableHumiditySensor()
{
	digitalWrite(HDC1080_IO6, LOW);
}

void enableLightSensor()
{
	digitalWrite(VEML7700_IO5, HIGH);
}

void disableLightSensor()
{
	digitalWrite(VEML7700_IO5, LOW);
}

void enableXBee()
{
	digitalWrite(XBEE_ON_OFF, HIGH);
}

void disableXBee()
{
	digitalWrite(XBEE_ON_OFF, LOW);
}

void sleepXBee(uint8_t state)
{
	digitalWrite(XBEE_SLEEP, state);
}
