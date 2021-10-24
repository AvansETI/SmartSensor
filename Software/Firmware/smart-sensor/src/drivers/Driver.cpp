/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/Driver.h"

SmartSensorMeasurement* Driver::getMeasurementCallback() {
    return this->cbMeasurement;
}


