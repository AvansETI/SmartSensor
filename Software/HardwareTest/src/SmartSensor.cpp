/*
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <SmartSensor.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

namespace smartsensor
{
	Application::Application() : soft_serial_(SOFT_RX_PIN, SOFT_TX_PIN, false), xbee_()
	{
	}

	void Application::begin()
	{
		this->rh_sensor_.begin(HDC1080_I2C_ADDR);
		this->light_sensor_.begin();

		this->light_sensor_.setGain(VEML7700_GAIN_1);
		this->light_sensor_.setIntegrationTime(VEML7700_IT_800MS);

		this->soft_serial_.begin(9600);
		this->xbee_.begin(Serial);
	}

	/**
	 * @brief Measure and send data.
	 * @note Precondition: all sensors have been enabled and have data available.
	 * @note Precondition: The XBee is connected and ready to send data.
	 */
	void Application::measureAndSend() const
	{
		static StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
		String output;

		doc.clear();
		doc["t"]  = this->rh_sensor_.readTemperature();
		doc["rh"] = this->rh_sensor_.readHumidity();
		doc["l"]  = this->light_sensor_.readLux();

		serializeJson(doc, output);

		Serial.printf(F("JSON document: \n%s"), output.c_str());

		XBeeAddress64 addr(0, 0);
		ZBTxRequest request(addr, (uint8_t*) output.c_str(), output.length());

		request.setAddress16(0);
		this->xbee_.send(request);
	}
}
