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
#include <stdint.h>

#include <boards/Board.h>
#include <drivers/LedDriver.h>
#include <drivers/SHTC3Driver.h>
#include <drivers/MCP7940NDriver.h>

class SmartSensorBoardV1_2: public SmartSensorBoard {
private:
    LedDriver ledDriver;
    SHTC3Driver shtc3Driver;
    MCP7940NDriver mcp7940nDriver;
        
public:
    SmartSensorBoardV1_2() {}

    void setup();

};

