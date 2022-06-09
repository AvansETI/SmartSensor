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


#include <drivers/AnalogDriver.h>
#include <boards/Board.h>

#define MAX4466_PIN PA0
#define MAX4466_DDR DDRA
#define MAX4466_PORT PORTA

#define MAX4466_SAMPLING_INTERVAL 5000
#define MAX4466_SAMPLING_AMOUNT 1

/* set this to 1 if debug messages need to be printed */
#define DEBUG_MODE 1

/**
 * @brief driver class for the sound detector
 * 
 */
class MAX4466Driver : public AnalogDriver
{
private:
    /* envelope value that represents the loudness of the sound measured */
    int envelope;

    /**
     * @brief Prints debug messages to the board with driver prefix ( [MAX4466] ) and newline
     * 
     * @param message the message to print
     */
    void debug_println(const char *message);

protected:
    /* Protected constructor in order to create a singleton class. */
    MAX4466Driver(MessageInterface* messageInterface,XBeeMessageDeliverer* xBeeMessageDeliverer ) : AnalogDriver(messageInterface, xBeeMessageDeliverer) {}

public:
    /**
     * @brief Get the Instance object
     * 
     * @return SparkfunDoundDetectorDriver* : the singleton instance to this class.
     */
    static MAX4466Driver *getInstance(MessageInterface* messageInterface, XBeeMessageDeliverer* xBeeMessageDeliverer)
    {
        static MAX4466Driver _soundDetectorDriver(messageInterface, xBeeMessageDeliverer);
        return &_soundDetectorDriver;
    }

    /**
     * @brief loop method that facilitates the functionality of the driver
     * 
     * @param millis the loop time
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t late_loop(uint32_t millis);

    /**
     * @brief resets the driver
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t late_reset();

    /**
     * @brief Puts the driver to sleep and if possible in low power consumption mode.
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t late_sleep();

    /**
     * @brief Wakes the driver up so it can continue working.
     * 
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t late_wakeup();

    uint8_t initialize();
};