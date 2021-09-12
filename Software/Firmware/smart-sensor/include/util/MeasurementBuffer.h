#pragma once
/**
 * @file       : MeasurementBuffer.h
 * @description: -
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : 
 * @updates
 * 
 */

#define MEASUREMENT_TOTAL_CHARS 30
#define MEASUREMENT_TOTAL 20

#include <stdint.h>

#include <avr/pgmspace.h>

struct Measurement {
    char measurement[MEASUREMENT_TOTAL_CHARS];
};

class MeasurementBuffer {
private:
    Measurement measurements[MEASUREMENT_TOTAL];  
    uint8_t startPointer;
    uint8_t insertPointer;
    bool bufferOverflow;
    uint8_t totalElements;

public:
    /* Constructor that sets all the individual time elements based on the given iso8601 string. */
    MeasurementBuffer(): startPointer(0), insertPointer(0), bufferOverflow(false), totalElements(0) {}

    uint8_t addMeasurement(char* measurement);

    bool getBufferOverflow() { return this->bufferOverflow; }
    void resetBufferOverflow() { this->bufferOverflow = false; }
    uint8_t getSize() { return this->totalElements; }

    char* popMeasurement();

};
