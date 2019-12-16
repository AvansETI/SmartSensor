/*
 * Entry point.
 * 
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <stdlib.h>
#include <Arduino.h>

#include <HDC1080.h>
#include <XBee.h>
#include <Adafruit_VEML7700.h>

static HDC1080 rh;
static Adafruit_VEML7700 light_sensor;

static constexpr uint8_t HDC1080_I2C_ADDR = 0x40;

void loop()
{
}

void setup()
{
	rh.begin(HDC1080_I2C_ADDR);
	light_sensor.begin();

	light_sensor.setGain(VEML7700_GAIN_1);
	light_sensor.setIntegrationTime(VEML7700_IT_800MS);
}
