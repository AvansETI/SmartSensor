#pragma once
/**
 * @file       : VEML7700.h
 * @description: This driver handles the ambient light sensor, able to measure changes in the brightness of light. 
 *               [PLACEHOLDER until proper link to VEML7700 is found]
 * @date       : 16-09-2021
 * @author     : Tom Kaasenbrood
 * @version    : 0.1
 * @todo       : 
 * @updates
 * 
 */
#include "drivers/Driver.h"

#include <util/I2C0.h>

// Address of the VEML7700 sensor
constexpr uint8_t VEML7700_I2C_ADDRESS PROGMEM = 0x20;

// The concrete driver to handle the sensor
class VEML7700Driver: public Driver, public I2C0InterruptEvent {
private:
    uint8_t state;

    uint32_t samplingInterval;
    uint32_t loopTiming;
protected:
    
public:

};