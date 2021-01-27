#ifndef SMART_SENSOR_XBEEDATA_H
#define SMART_SENSOR_XBEEDATA_H

#include "sensor-data/IXBeeData.h"

class XBeeData : public IXBeeData {
    public:
        /**
         * Initializes the XBeeData
         *
         * @param temperature   Specified temperature in degrees Celcius
         * @param humidity      Specified humidity in %
         * @param illuminance   Specified illuminance in lx
         */
        XBeeData(float temperature, float humidity, float illuminance);

        /**
         * Gets the generated packet from the inserted parameters in the constructor
         *
         * @return The generated packet as an char pointer (string)
         */
        char* get_packet() override;
		
    private:
        float m_temperature;
        float m_humidity;
        float m_illuminance;
        char m_packet[PACKET_SIZE];

        void initialize_packet();
};

#endif