#pragma once

/**
 * @brief      : Driver for the Sparkfun sound detector
 * @file       : SparkfunSoundDetector.h
 * @description: This driver handles the input from the sparkfun sound detector
 * @date       : 21-04-2022
 * @author     : Sem van der Hoeven
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Implement
 *
 */

#include <drivers/Driver.h>

#define ENVELOPE_PIN PA0

/**
 * @brief driver class for the sound detector
 * 
 */
class MAX4466Driver : public Driver
{
private:
    /*envelope value that represents the loudness of the sound measured*/
    int envelope; 

protected:
    /* Protected constructor in order to create a singleton class. */
    MAX4466Driver() {}

public:
    /**
     * @brief Get the Instance object
     * 
     * @return SparkfunDoundDetectorDriver* : the singleton instance to this class.
     */
    static MAX4466Driver *getInstance()
    {
        static MAX4466Driver _soundDetectorDriver;
        return &_soundDetectorDriver;
    }

    /* Interface Task methods. */
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