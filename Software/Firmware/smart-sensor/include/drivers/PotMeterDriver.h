#pragma once
/**
 * @file       : PotMeterDriver.h
 * @description: This driver handles the measuring of data from a standard 10 kOhm slide potentiometer
 * @date       : 28-4-2022
 * @author     : Sebastiaan Colijn
 * @version    : 0.1
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 */

#include <drivers/Driver.h>
#include <stdio.h>

//Define port(s)


class PotMeterDriver: public Driver
{
private:
    /* data */

    //sampling timing
   /* Set the sampling interval of the sensor in seconds. */
    uint16_t samplingInterval;

    /* Hold the timestamp in seconds where we have started the sampling. */
    uint16_t samplingTimestamp;    // last sample

    bool isMeasuring; // needed to prevent conflicts with other devices on ADC - solve with manager later?

protected:
    /* Protected constructor to create a singleton. */
    PotMeterDriver(MessageInterface* messageInterface): Driver(messageInterface) {};


public:

    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();
    void measure();

    static PotMeterDriver* getInstance(MessageInterface* messageInterface) {
        static PotMeterDriver _potMeterDriver(messageInterface);
        return &_potMeterDriver;
    }
};