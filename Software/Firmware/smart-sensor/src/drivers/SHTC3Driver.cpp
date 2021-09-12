#include "drivers/SHTC3Driver.h"

#include <stdio.h>
#include <string.h>

uint8_t SHTC3Driver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the SHTC3 chip
    }

    if ( this->getID() == 0 ) {
        return 2; // The given ID is not correct!
    }

    return 0;
}

uint8_t SHTC3Driver::loop(uint32_t millis) {
    this->sample();
    return 0;
}

// Software reset 0x805D 1000’0000’0101’1101 => page 8: https://taoic.oss-cn-hangzhou.aliyuncs.com/sku/pdf/d16078ca630c4b401c5bec25674afc26833e7455.pdf
uint8_t SHTC3Driver::reset() {
    
    return 0;
}

uint8_t SHTC3Driver::sleep() {
    
    return 0;
}

uint8_t SHTC3Driver::wakeup() {
    
    return 0;
}

float SHTC3Driver::getTemperature() {
    return this->temperature;
}

float SHTC3Driver::getHumidity() {
    return this->humidity;
}

// Where is the source of this calculation?
bool SHTC3Driver::checkChecksum(const uint16_t data, const uint8_t checksum) {
    constexpr auto polynomial = 0x131; // P(x) = x^8 + x^5 + x^4 + 1 = 100110001

    uint8_t bit;        // bit mask
    uint8_t crc = 0xFF; // calculated checksum
    uint8_t byteCtr;    // byte counter

     // calculates 8-Bit checksum with given polynomial
    for(byteCtr = 0; byteCtr < 2; byteCtr++) {
        crc ^= static_cast<uint8_t>(data >> ((1-byteCtr)*8));
        for(bit = 8; bit > 0; --bit) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc = (crc << 1);
            }
        }
    }

    return crc == checksum;
}

bool SHTC3Driver::isConnected() {    
    return false;
}

uint16_t SHTC3Driver::getProductCode() {
    return this->getID() & 0b0000'1000'0011'1111;
}

uint16_t SHTC3Driver::getID() {
    if ( this->id != 0 ) {
        return this->id;
    }

    return 0;
}

uint8_t SHTC3Driver::sample() {
    this->setDataInvalid();

    // Get the sample values here!

    this->setDataValid();

    return 0;
}