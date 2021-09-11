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

class SmartSensorBoardV1_2: public SmartSensorBoard {
private:
    uint8_t id;

public:
    SmartSensorBoardV1_2(): id(0) {}

};

