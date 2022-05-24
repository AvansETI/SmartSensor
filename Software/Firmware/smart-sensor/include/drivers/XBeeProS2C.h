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

#include <stdio.h>
#include <boards/Board.h>

#define XBEEPROS2C_SLEEP_PIN PB1
#define XBEEPROS2C_SLEEP_DDR DDRB
#define XBEEPROS2C_SLEEP_PORT PORTB

#define XBEEPROS2C_RECIEVE_BUFFER_AMOUNT 50
#define XBEEPROS2C_TIMEOUT_TIME_S 5000
#define XBEEPROS2C_PAN_ID "2316"
#define XBEEPROS2C_MAX_MESSAGES 5

enum XBeeProS2CStateReciever
{
    IDLE,              // Nothing todo...
    BUSY,              // Started recieving something that is not an API request.
    BUSY_API_LENGTH_H, // Busy with processing an received API message length
    BUSY_API_LENGTH_L, // Busy with processing an received API message length
    BUSY_API_DATA,
    PROCESSING_API,
    PROCESSING // Processing the recieved data
};

#define XBEEPROS2C_STATE_RUNNING 199
#define XBEEPROS2C_STATE_NOTFOUND 200

#define XBEEPROS2C_SEND_DELAY 5000

/* The class LedDriver handles the two leds that are on the board. */
class XBeeProS2C : public Driver, public SerialRecievedCharacter
{
private:
    uint8_t state;
    XBeeProS2CStateReciever stateReciever;

    uint8_t recieveBufferPointer;
    char recieveBuffer[XBEEPROS2C_RECIEVE_BUFFER_AMOUNT];

    bool isCoordinator;

    uint32_t timestamp;

    uint16_t apiLength;
    uint16_t counter;

    void transmitAndChecksum(char transmitChar, int *checksum);
    Queue<Message, XBEEPROS2C_MAX_MESSAGES> transmitQueue;

protected:
    /* Protected constructor in order to create a singleton class. */
    XBeeProS2C(MessageInterface *messageInterface) : Driver(messageInterface), state(0), stateReciever(XBeeProS2CStateReciever::IDLE), recieveBufferPointer(0), isCoordinator(false), timestamp(0) {}

public:
    /* Returns the singleton instance to this class. */
    static XBeeProS2C *getInstance(MessageInterface *messageInterface)
    {
        static XBeeProS2C _xbeeProS2CDriver(messageInterface);
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

    /* methods for AT commands */

    void atStart();
    void atGetPanId();
    void atGetCoordinatorEnable();
    void atGetSerialNumberHigh();
    void atGetSerialNumberLow();

    void atSetPanId(const char *id);
    void atSetCoordinator(bool enable);
    void atSetNodeIdentifier(const char *id);
    void atWrite();

    bool checkResultOk();

    bool isInstalled() { return (this->state != XBEEPROS2C_STATE_NOTFOUND); }

    bool isSendAvailable()
    {
        return this->state == XBEEPROS2C_STATE_RUNNING;
    }

    /**
     * @brief converts the given message to bytes and sends it to the coordinator
     *
     * @param message the message to send
     */
    void sendMessageToCoordinator(const char *message);

    /**
     * @brief adds a message to the queue to be sent over zigbee when available
     * 
     * @param message the message to send
     */
    void addMessageForTransfer(Message message);

    void sendToNode();

private:
};
