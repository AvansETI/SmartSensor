/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/SHTC3Driver.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>

#include <tasks/Atmega324PBI2C0.h>

uint8_t SHTC3Driver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the SHTC3 chip
    }

    if ( this->getID() == 0 ) {
        return 2; // The given ID is not correct!
    }

    this->samplingInterval = 10;//60*5; // five minutes
    this->samplingTimestamp = 0;

    return 0;
}

bool SHTC3Driver::isConnected() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    return i2c->isConnected(SHTC3_I2C_ADDRESS);
}

uint8_t SHTC3Driver::loop(uint32_t millis) {
    if ( this->samplingTimestamp == 0 ) {
        this->samplingTimestamp = millis/1000;
    }

    if ( this->waitingOnI2C ) { // Last time the sample could not be processed.
        this->sample();
    }

    if ( (millis/1000) - this->samplingTimestamp > this->samplingInterval ) {
        this->samplingTimestamp = millis/1000;
        this->sample(); // Start the sampling process using callbacks when the measurement is ready!
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

// See the documentation for the checksum calculation.
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

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
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

void SHTC3Driver::i2cReadEvent(uint8_t data, uint8_t index) {
    this->data[index] = data;

    if ( index == 5 ) { // All the measurements have been received.
        char m[30];

        sprintf_P(m, PSTR("mh:%.1f"), (double)this->getHumidity());
        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));
        
        sprintf_P(m, PSTR("mt:%.1f"), (double)this->getTemperature());
        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));
    }
}

uint8_t SHTC3Driver::sample() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    
    if ( i2c->isAvailable() ) {
        this->waitingOnI2C = false;
        i2c->cmdStart();
        i2c->cmdSelectWrite(SHTC3_I2C_ADDRESS);
        i2c->cmdWrite(0x5C); //??
        i2c->cmdWrite(0x24); //??
        i2c->cmdRepeatedStart();
        i2c->cmdSelectRead(SHTC3_I2C_ADDRESS);
        i2c->cmdReadAck(this, 0); // humidity 0
        i2c->cmdReadAck(this, 1); // humidity 1
        i2c->cmdReadAck(this, 2); // humidity checksum
        i2c->cmdReadAck(this, 3); // temperature 0
        i2c->cmdReadAck(this, 4); // temperature 1
        i2c->cmdReadNack(this, 5); // temperature checksum
        i2c->cmdStop();
    
    } else {
        //this->waitingOnI2C = true;
    }

    return 0;
}

uint16_t SHTC3Driver::getTemperatureData() {
    uint16_t t = this->data[SHTC3Data::TEMPERATURE_0] << 8;
    t         |= this->data[SHTC3Data::TEMPERATURE_1];

    return t;
}

uint16_t SHTC3Driver::getHumidityData() {
    uint16_t h = this->data[SHTC3Data::HUMIDITY_0] << 8;
    h         |= this->data[SHTC3Data::HUMIDITY_1];

    return h;
}

float SHTC3Driver::getTemperature () {
    return 175 * float(this->getTemperatureData()) / 65536.0f - 45.0f;
}

float SHTC3Driver::getHumidity () {
    return 100 * float(this->getHumidityData()) / 65536.0f;
}

bool SHTC3Driver::isTemperatureValid() {
    return this->checkChecksum(this->getTemperatureData(), this->data[SHTC3Data::TEMPERATURE_CHECKSUM]);
}

bool SHTC3Driver::isHumidityValid() {
    return this->checkChecksum(this->getHumidityData(), this->data[SHTC3Data::HUMIDITY_CHECKSUM]);
}
