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
#include <boards/Board.h>

#define I2C_SCL_CLOCK 400'000L

/* Interface: I2CInterruptEvent
   When an interrupt is used, this interface is used to implement the callback that will
   be called when the interrupt has been runned. Implement small methods, while the method
   runs in interrupt mode!
 */
class I2CInterruptEvent {
public:
    virtual void i2cInterrupt() = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

/* Interface: I2C0ReadEvent
   This interface is used to implement te event to get data from the I2C interface.
 */
class I2CReadEvent {
public:
    virtual void i2cReadEvent(uint8_t data, uint8_t index) = 0; // This function is called when the interrupt has been activated! Not interrupt space!
};

/* The I2CState enumeration type. This type contains the states of the state machine of the
   I2C bus. It is used by the I2Cx libraries if required. When the module starts, the first state
   it enters is WAITING. When someone pushed commands to the command buffer, this module goes
   to the state COMMAND. In the loop it will execute the first command in the queue. The next
   state is CHECK. When the loop is runned again, it checks whether the I2C has been finished.
   The next state STATUS is selected. In this status, the outcome it checked. When the outcome
   is succesfull, the command is popped from the queu. When the command queue is not empty, the
   next state is COMMAND. When it is empty, the state becomes WAITING. When an error has occurred
   the full queue is removed until the stop command. When the queue is not empty the state becomes
   COMMAND otherwise WAITING.
 */
enum I2CState {
    WAITING, // Nothing to do
    COMMAND, // A command recieved, so it can be executed.
    CHECK,   // Command has been executed, checking if the I2C has been done
    STATUS,  // Command has been executed and the check was okay, check for the correct status.
};

/* The I2C commands are configured with this enumeration type.
 */
enum I2CCommand {
    START,
    REPEATED_START,
    SELECT,
    WRITE,
    READ_ACK,
    READ_NACK,
    STOP
};

static const uint8_t I2CCommandResultStatus[] {
    TW_START,
    TW_REP_START,
    TW_MT_SLA_ACK,
    TW_MT_DATA_ACK,
    TW_MR_SLA_ACK,
    TW_MR_SLA_NACK
};

/* A callback to the class that is busy with the TWI interface. */
static I2CInterruptEvent* cbInterruptEvent;

/* The class I2CDriver handles the i2c 0 interface on the board. */
class Atmega324PBI2C0: public Task, public I2CInterruptEvent, public I2CReadEvent {
private:
    /* State of the I2C library */
    I2CState state;

    /* Queue of the commands that need to be executed. */
    Queue<I2CCommand, 15> commands;

    /* Queue of the data that needs to be send. In the case a callback is used,
       this queue is used a index.
    */
    Queue<uint8_t, 15> data;

    /* Queue that contain the callback function. */
    Queue<I2CReadEvent*, 15> cbReadEvents;

protected:
    Atmega324PBI2C0(): state(I2CState::WAITING) { cbInterruptEvent = NULL; } // Singleton

public:
    static Atmega324PBI2C0* getInstance() {
        static Atmega324PBI2C0 _i2c;
        return &_i2c;
    }

    bool claim(I2CInterruptEvent* event);
    bool release(I2CInterruptEvent* event);

    /* Task method overrides.
    */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();
    
    /* Add the commands. */
    uint8_t cmdStart();
    uint8_t cmdRepeatedStart();
    uint8_t cmdSelect(uint8_t address, uint8_t mode);
    uint8_t cmdWrite(uint8_t byte);
    uint8_t cmdReadAck(I2CReadEvent* cbReadEvent, uint8_t index);
    uint8_t cmdReadNack(I2CReadEvent* cbReadEvent, uint8_t index);
    uint8_t cmdStop();

    // Make the functions below private or protected.

    void executeCommand();



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

    // Interface: I2CInterruptEvent
    void i2cInterrupt();

    // Interface:
    void i2cReadEvent(uint8_t data, uint8_t index);

    void test();

};
