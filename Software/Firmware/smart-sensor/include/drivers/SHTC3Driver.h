#pragma once
/**
 * @file       : SHT3Driver.h
 * @description: This driver handles all the aspects of the SHT3 chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to measure the temperature and humidity. 
 *               https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensor-shtc3-our-new-standard-for-consumer-electronics/
 * @date       : 10-09-2021
 * @author     : Floris Bob van Elzelingen, Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : The loop contains blocking function calls!
 *               Idea is to create a class for I2C that contains some mutex to get the resource for yourself. 
 *               each driver that requires the I2C need to wait until it gets the unique access and use it until is releases it.
 * @updates
 * 
 */
#include <drivers/Driver.h>

#include <math.h>
#include <avr/pgmspace.h>

#include <util/I2C0.h>

/* Address of the SHTC3 chip on the I2C bus */
constexpr uint8_t SHTC3_I2C_ADDRESS PROGMEM = 0xE0;

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class SHTC3Driver: public Driver, I2C0InterruptEvent {
private:
    uint16_t id;
    uint8_t state;
    uint16_t humidity;
    uint16_t temperature;

    uint32_t samplingInterval;
    uint32_t loopTiming;

protected:
    bool isConnected();

public:
    SHTC3Driver(): id(0), state(0) { }; // Should not use the default constructor!

    /* This driver contains measurements, so implement this constructor. */
    SHTC3Driver(SmartSensorMeasurement* cbMeasurement): Driver(cbMeasurement), id(0), state(0) {};

    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    static bool checkChecksum(uint16_t data, uint8_t checksum);
    uint8_t sampleLoop();

    /* Returns the unique ID of the SHTC3 chip. Note that bit 15L12 and 10:6 contain unspecified info
       that vary from sensor to sensor. Bits 11 and 5:0 contain the SHTC3 specific product code.
    */
    uint16_t getID();

    /* Returns the specific product code of the sensor. */
    uint16_t getProductCode();

    // When using the I2C module, this event is issued when an I2C is ready!
    void i2c0Interrupt();

    void setSamplingInterval(uint32_t samplingInterval) { this->samplingInterval = samplingInterval; }
};
