#pragma once
/**
 * @file       : boards/SmartSensorMeasurement.h
 * @description: -
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */

class SmartSensorMeasurement {
public:
    virtual void addMeasurement(const char* measurment, ...) = 0;
};