#include "sensor-data/XBeeData.h"

#include <stdio.h>
#include <string.h>
#include <board-support/util/SerialLogger.h>

#define NAME_TEMPERATURE    "\"Temperature\""
#define NAME_HUMIDITY       "\"Humidity\""
#define NAME_ILLUMINANCE    "\"Illuminance\""

#define UNIT_TEMPERATURE    "\"C\""
#define UNIT_HUMIDITY       "\"%\""
#define UNIT_ILLUMINANCE    "\"lx\""

XBeeData::XBeeData(float temperature, float humidity, float illuminance) {
    this->m_temperature = temperature;
    this->m_humidity = humidity;
    this->m_illuminance = illuminance;

    initialize_packet();
}

void XBeeData::initialize_packet() {
	SerialLogger0.printf("{\"temperature\": %f,\"humidity\": %f,\"illuminance\": %f }\n", this->m_temperature, this->m_humidity, this->m_illuminance);



}

char *XBeeData::get_packet() {
    return this->m_packet;
}