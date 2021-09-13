#include "drivers/SHTC3Driver.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>
#include <util/I2C0.h>
#include <util/Serial0.h> // kan weg voor debug!

uint8_t SHTC3Driver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the SHTC3 chip
    }

    if ( this->getID() == 0 ) {
        return 2; // The given ID is not correct!
    }

    this->samplingInterval = 60*1; // seconds
    this->loopTiming       = 0;

    return 0;
}

bool SHTC3Driver::isConnected() {
    I2C0* i2c = I2C0::getInstance();
    return i2c->isConnected(SHTC3_I2C_ADDRESS);
}

uint8_t SHTC3Driver::loop(uint32_t millis) {
    if ( this->loopTiming == 0 ) { // Start the timing process
        this->loopTiming = millis/1000;        
    }

    I2C0* i2c = I2C0::getInstance();
    uint32_t loopTime = ((millis/1000) - this->loopTiming);
    if ( loopTime > this->samplingInterval &&
         this->state == 0 && i2c->claim(this) ) {
        this->sampleLoop(); // Start the sampling process which is interrupt driven!
        this->loopTiming = millis/1000; // Restart the timing
    }

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

uint16_t SHTC3Driver::getProductCode() {
    return this->getID() & 0b0000'1000'0011'1111;
}

uint16_t SHTC3Driver::getID() {
    if ( this->id != 0 ) {
        return this->id;
    }

    // TODO: handle result of the wait functions.
    I2C0* i2c = I2C0::getInstance();
    i2c->start(); i2c->wait(TW_START);
    i2c->select(SHTC3_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0xEF); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0xC8); i2c->wait(TW_MT_DATA_ACK);
    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(SHTC3_I2C_ADDRESS, TW_READ); i2c->wait(TW_MR_SLA_ACK);
    i2c->readAck(); i2c->wait(TW_MR_DATA_ACK);
    this->id = i2c->getData() << 8;
    i2c->readAck(); i2c->wait(TW_MR_DATA_ACK);
    this->id |= i2c->getData();
    i2c->readAck(); i2c->wait(TW_MR_DATA_ACK);
    uint8_t checksum = i2c->getData();
    i2c->stop();

    if ( !this->checkChecksum(this->id, checksum) ) {
        this->id = 0;
    }

    return this->id;
}

// Sample loop is interrupt driven.
uint8_t SHTC3Driver::sampleLoop() {
    I2C0* i2c = I2C0::getInstance();

    switch (this->state) {
        case 0:
            this->state++;
            this->setDataInvalid();
            i2c->start();
            break;
        case 1:
            this->state++;
            i2c->status(TW_START);
            i2c->select(0xE0, TW_WRITE);
            break;
        case 2:
            this->state++;
            i2c->status(TW_MT_SLA_ACK);
            i2c->write(0x5C);
            break;
        case 3:
            this->state++;
            i2c->status(TW_MT_DATA_ACK);
            i2c->write(0x24);
            break;
        case 4:
            this->state++;
            i2c->status(TW_MT_DATA_ACK);
            i2c->repeatedStart();
            break;
        case 5:
            this->state++;
            i2c->status(TW_REP_START);
            i2c->select(0xE0, TW_READ);
            break;
        case 6:
            this->state++;
            i2c->status(TW_MR_SLA_ACK);
            i2c->readAck();
            break;
        case 7:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            this->humidity = i2c->getData() << 8;
            i2c->readAck();
            break;
        case 8:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            this->humidity |= i2c->getData();
            i2c->readAck();
            break;
        case 9:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            i2c->getData();
            i2c->readAck();
            break;
        case 10:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            this->temperature = i2c->getData() << 8;
            i2c->readAck();
            break;
        case 11:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            this->temperature |= i2c->getData();
            i2c->readNack();
            break;
        case 12:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            i2c->getData();
            i2c->stop();
            i2c->release(this);
            
            Serial0* s = Serial0::getInstance();
            char m[30];
            float _humidity = 100 * float(this->humidity) / 65536.0f;
            float _tempature = 175 * float(this->temperature) / 65536.0f - 45.0f;

            sprintf_P(m, PSTR("humidity: %.1f"), (double)_humidity);
            s->print(m);
            this->getMeasurementCallback()->addMeasurement(m);
            
            sprintf_P(m, PSTR("temperature: %.1f"), (double)_tempature);
            s->print(m);
            this->getMeasurementCallback()->addMeasurement(m);
            
            this->setDataValid();
            this->state = 0; // Start over
    }

    return 0;
}

void SHTC3Driver::i2c0Interrupt() {
    this->sampleLoop();
}
