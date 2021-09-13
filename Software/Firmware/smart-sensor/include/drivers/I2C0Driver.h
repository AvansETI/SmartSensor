#pragma once
/**
 * @file       : LedDriver.h
 * @description: This driver handles the leds on the board.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#include <stdint.h>
#include <avr/pgmspace.h>

#include <drivers/Driver.h>

#define I2C_SCL_CLOCK 400'000L

/* Interface */
class I2C0InterruptEvent {
    virtual void interrupt() = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

/* The class I2CDriver handles the i2c 0 interface on the board. */
class I2C0Driver: public Driver {
private:
    uint8_t state;// TESTING
    uint16_t humidity;
    uint16_t temperature;
    uint32_t startI2C;

public:
    I2C0Driver(): state(0) {}

    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

private:
    /* Wait until the I2C0 is ready again. */
    bool wait(uint8_t status);

    /* Check whether the I2C0 is ready. If true, the I2C0 is ready for the next step. */
    bool ready(); // for non blocking functionality
    bool status(uint8_t status); // If ready read status

    void repeatedStart();
    void start();

    void select(uint8_t address, uint8_t mode);

    void write(uint8_t data);

    void readAck();
    void readNack();

    uint8_t getData();

    void stop();
};
