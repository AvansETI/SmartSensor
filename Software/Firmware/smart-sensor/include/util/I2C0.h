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
public:
    virtual void i2c0Interrupt() = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

/* A callback to the class that is busy with the TWI interface. */
static I2C0InterruptEvent* cbInterruptEvent;

/* The class I2CDriver handles the i2c 0 interface on the board. */
class I2C0 {
private:
    uint8_t state;
    bool busy;

    // TESTING
    uint16_t humidity;
    uint16_t temperature;
    uint16_t luminosity;
    uint32_t startI2C;

protected:
    I2C0(): state(0), busy(false) { cbInterruptEvent = NULL; } // Singleton

public:
    static I2C0* getInstance() {
        static I2C0 _i2c;
        return &_i2c;
    }

    bool claim(I2C0InterruptEvent* event);
    bool release(I2C0InterruptEvent* event);

    uint8_t setup();
    

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

    bool isConnected(uint8_t address);
};
