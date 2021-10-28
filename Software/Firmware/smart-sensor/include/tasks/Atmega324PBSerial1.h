#pragma once
/**
 * @file       : util/Serial0.h
 * @description: -
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : -
 * @changes
 *  11-09-2021: Updated to be used async as task.
 *  24-10-2021: 
 */
#include <stdint.h>

#include <avr/pgmspace.h>

#include <tasks/Task.h>

/* Set the BAUD rate of the serial communicatio port.
*/
//#define SERIAL1_BAUD 9600
#define SERIAL1_BAUD 115200

/* Calculate the UBRR to set it to the correct BAUD rate. */
#define SERIAL1_UBRR F_CPU/16/SERIAL1_BAUD-1

/* Interface: SerialRecievedCharacter */
class SerialRecievedCharacter {
public:
    virtual void recievedCharacter(char c) = 0;
};

/* Class: Atmega324PBSerial0
   This class implements the task to write data to the serial port.
 */ 
class Atmega324PBSerial1: public Task {
private:
    /* When the class is busy to send a message, this busy flag is set to true. */
    uint8_t busy;

    /* The buffer that is used to copy the message to and send on the serial port. */
    char buffer[30];

    /* The pointer points to the position of the character that needs to be send. */
    uint8_t pointer;

protected:
    /* Also this class uses a specific part of the hardware, and therefore it is
       required to be singleton.
    */
    Atmega324PBSerial1() {}; // singleton!

public:
    /* Returns the instance of the singleton.
    */
    static Atmega324PBSerial1* getInstance() {
        static Atmega324PBSerial1 _serial1;
        return &_serial1;
    }

    void setCallback( SerialRecievedCharacter* callback );

    /* Task method overrides.
    */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    /* This method prints the message to the serial port. Note it is a blocking function.
    */
    uint8_t print(const char* message);
    uint8_t print_P(const char* message);

    /* This method prints the message to the serial port non blocking.
    */
    uint8_t printAsync(const char* message);
    uint8_t printAsync_P(const char* message);

    bool isCharacterReceieved();
    char readCharacter();

    /* Check wheter the serial port is busy.
    */
   uint8_t isBusy();

    /* Transmits one character over the serial port.
    */
    void transmitChar(char data);
};
