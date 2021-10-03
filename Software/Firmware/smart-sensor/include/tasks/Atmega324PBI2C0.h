#pragma once
/**
 * @file       : I2C0.h
 * @description: This module handles the I2C interface.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#include <stdint.h>

#include <util/twi.h>
#include <avr/pgmspace.h>

#include <util/Queue.h>

#include <drivers/Driver.h>

#include <tasks/Task.h>

#define I2C_SCL_CLOCK 400'000L

/* Interface */
class I2C0InterruptEvent {
public:
    virtual void i2c0Interrupt() = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

class I2C0ReadEvent {
public:
    virtual void i2c0ReadEvent(uint8_t data, uint8_t userData) = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

enum I2C0State {
    WAITING, // Nothing to do
    COMMAND, // A command recieved, so it can be executed.
    CHECK,   // Command has been executed, checking if the I2C has been done
    STATUS,  // Command has been executed and the check was okay, check for the correct status.
};

enum I2C0Command {
    START,
    REPEATED_START,
    SELECT,
    WRITE,
    READ_ACK,
    READ_NACK,
    DATA,
    STOP
};

/*
static const uint8_t I2C0CommandResultStatus[] {
    TW_START,
    TW_REP_START,
    TW_MT_SLA_ACK,
    TW_MT_DATA_ACK,
    TW_MR_SLA_ACK,
    TW_MR_SLA_NACK
}; */

/* A callback to the class that is busy with the TWI interface. */
static I2C0InterruptEvent* cbInterruptEvent;

/* The class I2CDriver handles the i2c 0 interface on the board. */
class Atmega324PBI2C0: public Task {
private:
    I2C0State state;
    Queue<I2C0Command, 15> commands;
    Queue<uint8_t, 15> data;


protected:
    Atmega324PBI2C0(): state(I2C0State::WAITING) { cbInterruptEvent = NULL; } // Singleton

public:
    static Atmega324PBI2C0* getInstance() {
        static Atmega324PBI2C0 _i2c;
        return &_i2c;
    }

    bool claim(I2C0InterruptEvent* event);
    bool release(I2C0InterruptEvent* event);

    /* Task method overrides.
    */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();
    
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

    //void executeCommands();
    void i2c0ReadEvent(uint8_t data, uint8_t userData); 
};
