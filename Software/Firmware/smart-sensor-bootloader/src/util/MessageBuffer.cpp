#include <util/MessageBuffer.h>

#include <string.h>

uint8_t MeasurementBuffer::addMeasurement(const char* measurement) {
    if ( this->totalElements != 0 && this->insertPointer == this->startPointer ) { // buffer overflow, the oldest measurement becomes overwritten!
        this->bufferOverflow = true;
        this->startPointer = ( this->startPointer + 1 ) % MESSAGE_TOTAL; // Move the start pointer!
    }

    strcpy(this->measurements[this->insertPointer].measurement, measurement);
    this->insertPointer = ( this->insertPointer + 1 ) % MESSAGE_TOTAL;
    this->totalElements++;
    
    if ( this->totalElements > MESSAGE_TOTAL ) {
        this->totalElements = MESSAGE_TOTAL;
    }

    return (this->bufferOverflow ? 1 : 0);
}

bool MeasurementBuffer::popMeasurement(char* measurement) {
    if ( this->totalElements != 0 ) {
        this->insertPointer = ( this->insertPointer - 1 ) % MESSAGE_TOTAL;
        strcpy(measurement, this->measurements[this->insertPointer].measurement);
        this->totalElements--;
        return true;
    }

    return false;
}
