#include <util/MeasurementBuffer.h>

#include <string.h>

uint8_t MeasurementBuffer::addMeasurement(char* measurement) {
    if ( this->totalElements != 0 && this->insertPointer == this->startPointer ) { // buffer overflow, the oldest measurement becomes overwritten!
        this->bufferOverflow = true;
        this->startPointer = ( this->startPointer + 1 ) % MEASUREMENT_TOTAL; // Move the start pointer!
    }

    strcpy(this->measurements[this->insertPointer].measurement, measurement);
    this->insertPointer = ( this->insertPointer + 1 ) % MEASUREMENT_TOTAL;
    this->totalElements++;
    
    if ( this->totalElements > MEASUREMENT_TOTAL ) {
        this->totalElements = MEASUREMENT_TOTAL;
    }

    return (this->bufferOverflow ? 1 : 0);
}

char* MeasurementBuffer::popMeasurement() {
    if ( this->totalElements != 0 ) {
        this->insertPointer = ( this->insertPointer - 1 ) % MEASUREMENT_TOTAL;
        return this->measurements[this->insertPointer].measurement;
        this->totalElements--;
    }
}
