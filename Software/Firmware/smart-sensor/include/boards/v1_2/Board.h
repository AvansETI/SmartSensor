#pragma once
/**
 * @file       : boards/BoardV1_2.h
 * @description: This file contains the specific board v1.2.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#define BOARDV1_2_ADAPTER_IN_USE_PIN PA6
#define BOARDV1_2_ADAPTER_IN_USE_DDR DDRA
#define BOARDV1_2_ADAPTER_IN_USE_PORT PINA

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <boards/Board.h>
#include <boards/v1_2/Timing.h>

#include <util/Serial.h>
#include <util/Message.h>

#include <drivers/LedDriver.h>
#include <drivers/SHTC3Driver.h>
#include <drivers/MCP7940NDriver.h>
#include <drivers/XBeeProS2C.h>

#include <tasks/Atmega324PBSerial0.h>
#include <tasks/Atmega324PBSerial1.h>
#include <tasks/Atmega324PBI2C0.h>

/* Class SmartSensorBoardV1_2 implements the specific hardware for the board version 1.2. */ 
class SmartSensorBoardV1_2: public SmartSensorBoard, public SerialRecievedCharacter {
private:
    /* The timing class that implements millis(). */
    Timing* timing;

    /* The class that handles the serial0. */
    Atmega324PBSerial0* serial0;

    /* The class that handles the serial1 and is connected with XBee. */
    Atmega324PBSerial1* serial1;

    /* The class that handles the I2C0 bus. */
    Atmega324PBI2C0* i2c0;

    /* The class that handles the two leds implemented on the board. */
    LedDriver* ledDriver;

    /* The class that handles the SHTC3 chip that measures the temperature and humidity. */
    SHTC3Driver* shtc3Driver;

    /* The class that handles the RTC chip that contains the time in real-time. */
    MCP7940NDriver* mcp7940nDriver;

    /* The class that handles the XBeeProS2C communication and configuration. */
    XBeeProS2C* xbeeProS2CDriver;

    SerialBuffer<MESSAGE_LENGTH> serialBuffer;
        
public:
    SmartSensorBoardV1_2() { }

    void setup();

    uint32_t millis();

    bool adapterInUse();

    /* Returns true when this board is connected to a gateway. */
    bool isGateway();

    void debug( const char* message);
    void debug_P( const char* message);

    void getActualTimestamp();
    void setActualTimestamp(const RTCTime &time);
    
    /* Get the serial number that is stored in the Atmega324PB. */
    const char* getID();

    uint8_t sendDataString(const char* data);
    uint8_t sendDataStringAvailable();

    uint8_t processCommand(const char* data);


    void recievedCharacter(char c);
};
