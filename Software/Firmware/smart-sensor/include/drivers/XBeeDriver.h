#ifndef SMART_SENSOR_XBEEDRIVER_H
#define SMART_SENSOR_XBEEDRIVER_H

#include <sensor-data/IXBeeData.h>
#include <board-support/util/SerialLogger.h>

class XBeeDriver {
    public:
        /**
         * Setup the XBee chip to function proparly
         */
        static void setup();

        /**
         * Sends data to the XBee to send using the ZigBee protocol
         *
         * @param data Data to send
         * @return Whether the data was send successfully
         */
        static bool send(IXBeeData& data);
};

#endif
