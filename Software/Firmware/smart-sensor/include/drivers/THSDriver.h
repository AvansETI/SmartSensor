#ifndef SMART_SENSOR_THSDRIVER_H
#define SMART_SENSOR_THSDRIVER_H

#include <board-support/drivers/TWIDriver.h>

/**
 * Temperature Humidity Sensor Driver
 * Written for the HIH6031 sensor.
 *
 * @author Paul Hobbel
 * @version 1.0
 */
class THSDriver : public TWIDriver {
    public:
        /**
         * Enum for holding the THS status
         */
        enum THSStatus {
            /**
             * Sensor is operating normally, measurement is up to date.
             */
            NORMAL,

            /**
             * Stale Data. Data was already fetched since last measurement,
             * or was fetched before measurement was complete.
             */
            STALE,

            /**
             * Sensor is in command mode.
             */
            COMMAND,

            /**
             * Not used/reserved.
             */
            NONE
        };

        /**
         * Initiates new THSDriver instance.
         */
        THSDriver();

        /**
         * Sends a measurement request to the HumTemp sensor.
         * @return true if successful, false if communication failed
         */
        bool update();

        /**
         * Get the last known {@link THSStatus} of the sensor
         * @return last known status
         */
        THSStatus get_status();

        /**
         * Get the last known humidity data of the sensor.
         * @return humidity in %RH
         */
        float get_humidity() const;

        /**
         * Get the last known temperature data of the sensor.
         * @return temperature in °C
         */
        float get_temperature() const;

    private:
        THSStatus m_last_status;
        float m_last_humidity;
        float m_last_temperature;
};

#endif //SMART_SENSOR_THSDRIVER_H
