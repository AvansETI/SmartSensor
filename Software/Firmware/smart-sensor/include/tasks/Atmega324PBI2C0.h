#pragma once
/**
 * @file       : I2C0.h
 * @description: This module handles the I2C interface. The interrupts needs to be enabled to let this
 *               module properly run.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : -
 * @changes
 * 
 */
#include <stdint.h>

#include <util/twi.h>
#include <avr/pgmspace.h>

#include <util/Queue.h>
#include <util/I2C.h>
#include <drivers/Driver.h>
#include <tasks/Task.h>

/* Define the I2C0 clock speed. */
#define I2C0_SCL_CLOCK 400'000L

/* Define how many I2C commands can be given at once. */
#define I2C0_BUFFER_LENGTH 20

/* The class I2CDriver handles the i2c 0 interface on the board. */
class Atmega324PBI2C0: public Task {
private:
    /* State of the I2C library */
    I2CState state;

    /* Queue of the commands that need to be executed. */
    Queue<I2CCommand, I2C0_BUFFER_LENGTH> commands;

    /* Queue of the data that needs to be send. In the case a callback is used,
       this queue is used a index.
    */
    Queue<uint8_t, I2C0_BUFFER_LENGTH> data;

    /* Queue that contain the callback function. */
    Queue<I2CReadEvent*, I2C0_BUFFER_LENGTH> cbReadEvents;

    /* Timing to check whether the I2C bus is stuck?! */
    uint32_t timer;

protected:
    /* Protected constructor to create a singleton of the class. */
    Atmega324PBI2C0(): state(I2CState::WAITING) { }

public:
    /* Get the singleton instance of this class. */
    static Atmega324PBI2C0* getInstance() {
        static Atmega324PBI2C0 _i2c;
        return &_i2c;
    }

    /* Task method overrides.
    */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();
    
    /* Check that the specific address responds to a select message. */
    bool isConnected(uint8_t address);

    /* Add the commands. */
    uint8_t cmdStart();
    uint8_t cmdRepeatedStart();
    uint8_t cmdSelectWrite(uint8_t address);
    uint8_t cmdSelectRead(uint8_t address);
    uint8_t cmdWrite(uint8_t byte);
    uint8_t cmdReadAck(I2CReadEvent* cbReadEvent, uint8_t index);
    uint8_t cmdReadNack(I2CReadEvent* cbReadEvent, uint8_t index);
    uint8_t cmdStop();
    uint8_t isAvailable();

    // Use the below functions only when the loop is not called.

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

private:
    /* Execute the specific command that is in the buffer. */
    void executeCommand();

};
