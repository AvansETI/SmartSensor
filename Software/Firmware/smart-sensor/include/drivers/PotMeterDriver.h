#pragma once
/**
 * @file       : PotMeterDriver.h
 * @description: This driver handles the measuring of data from a standard 10 kOhm slide potentiometer
 * @date       : 12-5-2022
 * @author     : Sebastiaan Colijn
 * @version    : 0.2
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes    :
 * Rebased on AnalogDriver class
 */

#include <drivers/Driver.h>
#include "drivers/AnalogDriver.h"
#include <stdio.h>

//Define port(s)


class PotMeterDriver: public AnalogDriver
{
private:
    /* data */
    uint32_t lastMeasurement;
protected:
    /* Protected constructor to create a singleton. */
    PotMeterDriver(MessageInterface* messageInterface, XBeeMessageDeliverer* xBeeMessageDeliverer): AnalogDriver(messageInterface,xBeeMessageDeliverer) {};

public:

    uint8_t late_loop(uint32_t millis);
    uint8_t late_reset();
    uint8_t late_sleep();
    uint8_t late_wakeup();
    uint8_t initialize();
    void sample();

    static PotMeterDriver* getInstance(MessageInterface* messageInterface, XBeeMessageDeliverer* xBeeMessageDeliverer) {
        static PotMeterDriver _potMeterDriver(messageInterface, xBeeMessageDeliverer);
        return &_potMeterDriver;
    }
};