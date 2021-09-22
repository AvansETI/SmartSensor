#pragma once
/**
 * @file       : VEML7700.h
 * @description: This driver handles the ambient light sensor, able to measure changes in the brightness of light. 
 *               [PLACEHOLDER until proper link to VEML7700 is found]
 * @date       : 21-09-2021
 * @author     : Tom Kaasenbrood
 * @version    : 0.2
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
    uint16_t id;
    uint8_t state;
    uint16_t lightValue;
    uint16_t whiteLightValue;

    uint32_t samplingInterval;
    uint32_t loopTiming;
protected:
    VEML7700Driver(SmartSensorMeasurement* luMeasurement): Driver(luMeasurement), id(1), state(0) {};

    bool isConnected();    
public:
    static VEML7700Driver* getInstance(SmartSensorMeasurement* luMeasurement) {
        static VEML7700Driver _veml7700Driver(luMeasurement);
        return &_veml7700Driver;
    }

    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    static bool checkChecksum(uint16_t data, uint8_t checksum);
    uint8_t sampleLoop();

    //Returns id
    uint16_t getId();

    //Returns product code
    uint16_t getProductCode();

    // When using the I2C module, this event is issued when an I2C is ready!
    void i2c0Interrupt();

    void setSamplingInterval(uint32_t samplingInterval) { this->samplingInterval = samplingInterval; }

};