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
#define BOARDV1_2_ADAPTER_IN_USE_PORT PORTA

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <boards/Board.h>
#include <boards/v1_2/Timing.h>

#include <util/MessageBuffer.h>

#include <drivers/LedDriver.h>
#include <drivers/SHTC3Driver.h>
#include <drivers/MCP7940NDriver.h>

#include <tasks/Atmega324PBSerial0.h>
#include <tasks/Atmega324PBI2C0.h>

class SmartSensorBoardV1_2: public SmartSensorBoard {
private:
    Timing* timing;
    Atmega324PBSerial0* serial0;
    Atmega324PBI2C0* i2c0;

    LedDriver* ledDriver;
    SHTC3Driver* shtc3Driver;
    MCP7940NDriver* mcp7940nDriver;
        
public:
    SmartSensorBoardV1_2() { }

    void setup();

    uint32_t millis();

    bool adapterInUse();

    void debug( const char* message);
    void debug_P( const char* message);

    void addMeasurement(const char* measurement);
    
    char* getID();

};

