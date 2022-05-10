#pragma once

/**
 * @brief      : Driver for the Sparkfun sound detector
 * @file       : AnalogDriver.h
 * @description: This is a driver that can be used for reading analog pins
 * @date       : 28-04-2022
 * @author     : Sem van der Hoeven
 * @version    : 1.0
 * @license    : GNU version 3.0
 *
 */

#include <drivers/Driver.h>
#include <boards/Board.h>

#define MAX_ANALOG_PIN 4

/**
 * @brief Analog Driver class that facilitates functionality for sensors that read from an analog pin.
 * The analog pin can be set with the analog_pin variable. To implement the methods of the Driver class, 
 * the late_ methods can be used. They will be called in the normal driver functions. The initialize function 
 * is called after the setup function, so you can use this to execute any setup code you want your driver to perform.
 *
 */
class AnalogDriver : public Driver
{
private:
protected:
    // /* Protected constructor in order to create a singleton class. */
    AnalogDriver(MessageInterface *messageInterface) : Driver(messageInterface) {}

    /**
     * @brief The analog pin for this driver. This must be between 0 and 4 (inclusive).
     *
     */
    uint8_t analog_pin = 0;

    /**
     * @brief boolean that specifies if the driver is sleeping
     *
     */
    bool sleeping;

    /* Interval to specify the interval (in milliseconds) in which the sensor should sample */
    uint32_t samplingInterval;

    /* Variable to hold the timestamp of the milliseconds elapsed in the loop */
    uint32_t samplingTimestamp;

    /* Amount of samples the sensor should take every loop */
    uint8_t samplingAmount;

public:
    /**
     * @brief setup method to initialize the driver
     *
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t setup() final;

    /**
     * @brief measures a value and parses it with the ADC on the specified pin ()
     *
     * @return uint32_t the measured value of the ADC.
     */
    uint32_t measure_analog_value();

    /**
     * @brief this function is called after the setup() function that initializes the ADC. Implment this if you want to add functionality to the setup of your driver.
     *
     * @return uint8_t the return value of the function
     */
    virtual uint8_t initialize() = 0;

    /**
     * @brief loop method that facilitates the functionality of the driver
     *
     * @param millis the loop time
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t loop(uint32_t millis) final;

    /**
     * @brief resets the driver
     *
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t reset() final;

    /**
     * @brief Puts the driver to sleep and if possible in low power consumption mode.
     *
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t sleep() final;

    /**
     * @brief Wakes the driver up so it can continue working.
     *
     * @return uint8_t return code, 0 if successful, nonzero if not successful
     */
    uint8_t wakeup() final;

    /**
     * @brief loop function that gets called in the loop function of the base class. Put your loop code in here
     *
     * @param millis the millis since the last call
     * @return uint8_t return value exit code
     */
    virtual uint8_t late_loop(uint32_t millis) = 0;

    /**
     * @brief reset function that gets called in the reset function of the base class. Put your reset code in here.
     *
     * @return uint8_t return value exit code
     */
    virtual uint8_t late_reset() = 0;

    /**
     * @brief sleep function that gets called in the sleep function of the base class. Put your sleep code in here.
     *
     * @return uint8_t return value exit code
     */
    virtual uint8_t late_sleep() = 0;

    /**
     * @brief wakeup function that gets called in the wakeup function of the base class. Put your wakeup code in here.
     *
     * @return uint8_t return value exit code.
     */
    virtual uint8_t late_wakeup() = 0;
};
