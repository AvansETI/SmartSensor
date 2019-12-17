/* SmartSensor.h
   Defines to map the pins and hardware of the SmartSensor.
*/

#pragma once
#include <Arduino.h>
#include <HDC1080.h>
#include <XBee.h>
#include <Adafruit_VEML7700.h>
#include <SoftwareSerial.h>

#include <smartsensor/referencewrapper.h>

#define VBAT_ADC0 PINA0
#define HAT_AIO1 PINA1
#define INTA_ADC3 PINA2
#define HAT_AIO2 PINA3
#define HAT_AIO6 PINA4
#define HAT_AIO4 PINA5
#define HAT_AIO5 PINA6
#define HAT_AIO3 PINA7

#define HDC1080_IO6 PINB0
#define HAT_DIO5 PINB1
#define HAT_DIO3 PINB2
#define HAT_DIO4 PINB3
#define SPI_SS PINB4
#define SPI_MOSI PINB5
#define SPI_MISO PINB6
#define SPI_SCK PINB7

#define I2C_SCL PINC0
#define I2C_SDA PINC1
#define LED_IO8 PINC2
#define Vadap_IO9 PINC3
#define XBEE_SLEEP PINC4
#define HAT_DIO1 PINC5
#define HAT_DIO6 PINC6
#define HAT_DIO7 PINC7

#define AVR_DBG_RX PIND0
#define AVR_DBG_TX PIND1
#define XBEE_ON_OFF PIND2
#define AVR_RX PIND3
#define AVR_TX PIND4
#define VEML7700_IO5 PIND5
#define HAT_DIO2 PIND6
#define HAT_DIO31 PIND7

namespace smartsensor
{
	class Application {
	public:
		static smartsensor::ReferenceWrapper<Application> Instance()
		{
			static Application application;
			return smartsensor::MakeRef<Application>(application);
		}

		void begin();

		void measureAndSend() const;

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

	private:
		explicit Application();

		static constexpr uint8_t HDC1080_I2C_ADDR = 0x40;
		static constexpr uint8_t SOFT_RX_PIN = 11;
		static constexpr uint8_t SOFT_TX_PIN = 12;
		static constexpr uint8_t JSON_DOCUMENT_SIZE = 255; // Related to the max Xbee packet size.

		mutable HDC1080 rh_sensor_;
		mutable Adafruit_VEML7700 light_sensor_;
		SoftwareSerial soft_serial_;
	};
}
