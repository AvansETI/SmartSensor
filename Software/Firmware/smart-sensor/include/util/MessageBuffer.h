#pragma once
/**
 * @file       : MeasurementBuffer.h
 * @description: -
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @todo       : 
 * @changes
 *  24-10-2021: Made total chars smaller, 30 is not required. Example: temperature:23.4 is 16 characters big.
 *              Having at this moment 4 measurements (light, CO2, temp and hum) this is doubled and not 10.
 */

#define MESSAGE_TOTAL_CHARS 20
#define MESSAGE_TOTAL 8

#include <stdint.h>

#include <avr/pgmspace.h>

/* Interface */
class SmartSensorMeasurement {
public:
    virtual void addMeasurement(const char* measurement) = 0;
};

struct Measurement {
    char measurement[MESSAGE_TOTAL_CHARS];
};

class MeasurementBuffer {
private:
    Measurement measurements[MESSAGE_TOTAL];  
    uint8_t startPointer;
    uint8_t insertPointer;
    bool bufferOverflow;
    uint8_t totalElements;

public:
    /* Constructor that sets all the individual time elements based on the given iso8601 string. */
    MeasurementBuffer(): startPointer(0), insertPointer(0), bufferOverflow(false), totalElements(0) {}

    uint8_t addMeasurement(const char* measurement);

    bool getBufferOverflow() { return this->bufferOverflow; }
    void resetBufferOverflow() { this->bufferOverflow = false; }
    uint8_t getSize() { return this->totalElements; }

    bool popMeasurement(char* measurement);
};
