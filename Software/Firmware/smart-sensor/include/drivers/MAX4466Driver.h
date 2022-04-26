#pragma once

/**
 * @brief      : Driver for the Sparkfun sound detector
 * @file       : MAX4466Driver.h
 * @description: This driver handles the input from the sparkfun sound detector
 * @date       : 21-04-2022
 * @author     : Sem van der Hoeven
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Implement
 *
 */


#include <drivers/Driver.h>
#include <boards/Board.h>

#define MAX4466_PIN PA0
#define MAX4466_DDR DDRA
#define MAX4466_PORT PORTA

#define MAX4466_SAMPLING_INTERVAL 1000

/**
 * @brief driver class for the sound detector
 * 
 */
class MAX4466Driver : public Driver
{
private:
    /* envelope value that represents the loudness of the sound measured */
    int envelope;

    /* Boolean to keep track of if this driver is sleeping or not */
    bool sleeping = false;

    /* Interval to specify the interval in which the sensor should sample */
    uint32_t samplingInterval;

    /* Variable to hold the timestamp of the milliseconds elapsed in the loop */
    uint32_t samplingTimestamp;

    /* Amount of samples the sensor should take to get the average */
    uint8_t samplingAmount;

    /**
     * @brief Samples the sensor and puts the value in the envelope variable
     * 
     * @return uint8_t a status code of 0 if sampling went successful, nonzero if something went wrong
     */
    uint8_t sample();

    /**
     * @brief Takes an audio measurement by setting the ADSC bit high and waiting for it to go lowmeasurement 
     * 
     * @return int the measured value
     */
    uint32_t take_measurement();

    /**
     * @brief Prints debug messages to the board with driver prefix ( [MAX4466] ) and newline
     * 
     * @param message the message to print
     */
    void debug_println(const char *message);

protected:
    /* Protected constructor in order to create a singleton class. */
    MAX4466Driver(MessageInterface* messageInterface) : Driver(messageInterface) {}

public:
    /**
     * @brief Get the Instance object
     * 
     * @return SparkfunDoundDetectorDriver* : the singleton instance to this class.
     */
    static MAX4466Driver *getInstance(MessageInterface* messageInterface)
    {
        static MAX4466Driver _soundDetectorDriver(messageInterface);
        return &_soundDetectorDriver;
    }

    /**
     * @brief setup method to initialize the driver
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t setup();

    /**
     * @brief loop method that facilitates the functionality of the driver
     * 
     * @param millis the loop time
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t loop(uint32_t millis);

    /**
     * @brief resets the driver
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t reset();

    /**
     * @brief Puts the driver to sleep and if possible in low power consumption mode.
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t sleep();

    /**
     * @brief Wakes the driver up so it can continue working.
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t wakeup();
};