#pragma once
/**
 * @file       : drivers/XBeeProS2C.h
 * @description: This file contains the class that handles the XBeePro communication and configuration.
 *               https://www.digi.com/resources/documentation/digidocs/pdfs/90002002.pdf.
 *               Optimization consideration is to do the low-level serial in here or MOSI/MISO. More compact.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @license    : GNU version 3
 * @todo       : -
 * @changes
 * 
 */
#include <stdint.h>

#include <avr/pgmspace.h>

#include <drivers/Driver.h>
#include <tasks/Atmega324PBSerial1.h>

#define XBEEPROS2C_SLEEP_PIN PB1
#define XBEEPROS2C_SLEEP_DDR DDRB
#define XBEEPROS2C_SLEEP_PORT PORTB

#define XBEEPROS2C_RECIEVE_BUFFER_AMOUNT 50
#define XBEEPROS2C_TIMEOUT_TIME_S 2000
#define XBEEPROS2C_PAN_ID "2316"

enum XBeeProS2CStateReciever {
    IDLE, // Nothing todo...
    BUSY, // Started recieving something
    PROCESSING // Processing the recieved data
};

#define XBEEPROS2C_STATE_NOTFOUND 200

/* The class LedDriver handles the two leds that are on the board. */
class XBeeProS2C: public Driver, public SerialRecievedCharacter {
private:
    uint8_t state;
    XBeeProS2CStateReciever stateReciever;

    uint8_t recieveBufferPointer;
    char recieveBuffer[XBEEPROS2C_RECIEVE_BUFFER_AMOUNT];

    bool isCoordinator;

    uint32_t timestamp;

protected:
    /* Protected constructor in order to create a singleton class. */
    XBeeProS2C(): state(0), stateReciever(XBeeProS2CStateReciever::IDLE), recieveBufferPointer(0), isCoordinator(false), timestamp(0) {}

public:
    /* Returns the singleton instance to this class. */
    static XBeeProS2C* getInstance() {
        static XBeeProS2C _xbeeProS2CDriver;
        return &_xbeeProS2CDriver;
    }

public:
    /* Interface Task methods. */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    /* Interface: SerialRecievedCharacter
     * Note that this is called from an interrupt, so do not make it too long!
     */
    void recievedCharacter(char c);

    void enableCoordinator(); 

    void atStart();
    void atGetPanId();
    void atGetCoordinatorEnable();
    void atGetSerialNumberHigh();
    void atGetSerialNumberLow();
    
    void atSetPanId(const char* id);
    void atSetCoordinator(bool enable);
    void atSetNodeIdentifier(const char* id);
    void atWrite();

    bool checkResultOk();


    bool isInstalled() { return (this->state != XBEEPROS2C_STATE_NOTFOUND); }

    void test();

private:

};
