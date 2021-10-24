#pragma once
/**
 * @file       : I2C.h
 * @description: This file contains all generic classes for I2C functions.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : -
 * @changes
 *  24-10-2021: MS: Improved memory to bring I2CCommandResultStatus to PROGMEM, make sure your read with pgm_read_byte.
 */
#include <stdint.h>

#include <avr/pgmspace.h>
#include <util/twi.h>

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

/* The I2C commands are configured with this enumeration type. */
enum I2CCommand {
    START,
    REPEATED_START,
    SELECT_WRITE,
    SELECT_READ,
    WRITE,
    READ_ACK,
    READ_NACK,
    STOP
};

/* An array that contains the result statuses of the I2CCommand enumeration. It
 * is stored in flash, so you need to get it using the progmem interface.
 * Example: pgm_read_byte(&I2CCommandResultStatus[4]);
 */
static const uint8_t I2CCommandResultStatus[] PROGMEM = {
    TW_START,
    TW_REP_START,
    TW_MT_SLA_ACK,
    TW_MR_SLA_ACK,
    TW_MT_DATA_ACK,
    TW_MR_DATA_ACK,
    TW_MR_DATA_NACK,
};
