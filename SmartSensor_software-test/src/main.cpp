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

static HDC1080 rh;
static Adafruit_VEML7700 light_sensor;

void loop()
{

}

// Set up the pins of your HAT module here!
// Default everything is set to INPUT.
void setupHAT() {
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
void setup() {
    pinMode(VBAT_ADC0, INPUT);  //Battery measurement
    pinMode(INTA_ADC3, OUTPUT); // Realtime clock: /INTA
    //digitalWrite(INTA_ADC3, LOW); // ??

    pinMode(HDC1080_IO6, OUTPUT);   // HDC1080 Humidity/Temp On/Off
    pinMode(SPI_SS, OUTPUT); // SS
    pinMode(SPI_MOSI, OUTPUT); // MOSI
    pinMode(SPI_MISO, INPUT);  // MISO
    pinMode(SPI_SCK, OUTPUT); // SCK

    pinMode(I2C_SCL, OUTPUT);
    pinMode(I2C_SDA, OUTPUT);
    pinMode(LED_IO8, OUTPUT);
    pinMode(Vadap_IO9, INPUT); // When adapter is plugged in 5V (Does it work?)
    
    pinMode(XBEE_SLEEP, OUTPUT);

    pinMode(AVR_DBG_RX, INPUT); // The real UART!!
    pinMode(AVR_DBG_TX, OUTPUT);
    
    pinMode(XBEE_ON_OFF, OUTPUT); // XBee module

    pinMode(AVR_RX, INPUT); // Soft UART??
    pinMode(AVR_TX, OUTPUT); // ??

    pinMode(VEML7700_IO5, OUTPUT); // Light sensor

    disableHumiditySensor();
    disableLightSensor();
    disableXBee();
    sleepXBee(LOW);

    rh.begin(HDC1080_I2C_ADDR);
	light_sensor.begin();

	light_sensor.setGain(VEML7700_GAIN_1);
	light_sensor.setIntegrationTime(VEML7700_IT_800MS);

    setupHAT();
}
