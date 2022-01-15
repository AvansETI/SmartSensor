/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/CCS811.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>

#include <tasks/Atmega324PBI2C0.h>

uint8_t CCS811Driver::setup() {
    // MS: These statements below causes the avr to reset once, why I do not know!
    CCS811_INT_DDR = CCS811_INT_DDR & ~(1 << CCS811_INT_PIN); // set int pin as input
    CCS811_NWAKE_DDR = CCS811_NWAKE_DDR | (1 << CCS811_NWAKE_PIN); // Set nWake  as output!
    

    //CCS811_INT_DDR = CCS811_INT_DDR & ~(1 << CCS811_INT_PIN); // set int pin as input
    this->lowWakePin(); // set wake pin to low!

    if ( !this->isConnected() ) {
        return 1; // Cannot select the chip
    }

    if ( this->appStart() != 0 ) {
        return 2; // app is not started!
    }

    this->setMode(1); // Set mode 1

    this->samplingInterval = 10; // 10s
    this->busy             = false;

    return 0;
}

bool CCS811Driver::isConnected() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    return i2c->isConnected(CCS811_I2C_ADDRESS);
}

uint8_t CCS811Driver::loop(uint32_t millis) {
    uint32_t seconds = (millis / 1000);
    uint8_t  modulo  = seconds % this->samplingInterval;

    if ( modulo > 0 && modulo < (this->samplingInterval / 2) ) {
        if ( !this->busy ) {
            this->busy = true;
            this->sample();
        }
    } else {
        this->busy = false;
    }

    if ( this->waitingOnI2C ) { // Last time the sample could not be processed.
        this->sample();
    }

    return 0;
}

uint8_t CCS811Driver::reset() {

    return 0;
}

uint8_t CCS811Driver::sleep() {
    
    return 0;
}

uint8_t CCS811Driver::wakeup() {
    
    return 0;
}

void CCS811Driver::i2cReadEvent(uint8_t data, uint8_t index) {
    this->data[index] = data;

    if ( index == CCS811Data::RAW_LSB ) { // All the measurements have been received.
        char m[30];

        sprintf_P(m, PSTR("c2:%d"), this->getCO2Data());
        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));

        sprintf_P(m, PSTR("tv:%d"), this->getTVOCData());
        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));
    }
}

uint8_t CCS811Driver::sample() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    
    if ( i2c->isAvailable() ) {
        this->waitingOnI2C = false;
        i2c->cmdStart();
        i2c->cmdSelectWrite(CCS811_I2C_ADDRESS);
        i2c->cmdWrite(0x02); // select ALG_RESULT
        i2c->cmdRepeatedStart();
        i2c->cmdSelectRead(CCS811_I2C_ADDRESS);
        i2c->cmdReadAck(this, 0); // CO2_MSB
        i2c->cmdReadAck(this, 1); // CO2_LSB
        i2c->cmdReadAck(this, 2); // TVOC_MSB
        i2c->cmdReadAck(this, 3); // TVOC_LSB
        i2c->cmdReadAck(this, 4); // STATUS
        i2c->cmdReadAck(this, 5); // ERROR_ID
        i2c->cmdReadAck(this, 6); // RAW_MSB
        i2c->cmdReadNack(this, 7); // RAW_LSB
        i2c->cmdStop();
    
    } else {
        this->waitingOnI2C = true;
    }

    return 0;
}

void CCS811Driver::lowWakePin() {
    CCS811_NWAKE_PORT = CCS811_NWAKE_PORT & ~(1 << CCS811_NWAKE_PIN); // Note that led is on when bit is low!
}

void CCS811Driver::highWakePin() {
    CCS811_NWAKE_PORT = CCS811_NWAKE_PORT | (1 << CCS811_NWAKE_PIN);
}

uint8_t CCS811Driver::setMode(uint8_t mode) {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    i2c->start(); i2c->wait(TW_START);
    i2c->select(CCS811_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //Select MEAS_MODE 0x01
    i2c->write(0x01); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0x10); i2c->wait(TW_MT_DATA_ACK); // Set mode 1 (4 << mode)
    i2c->stop();

    return 0;

}

uint8_t CCS811Driver::appStart() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    i2c->start(); i2c->wait(TW_START);
    i2c->select(CCS811_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //Select APP_START 0xF4
    i2c->write(0xF4); i2c->wait(TW_MT_DATA_ACK);
    i2c->stop();

    _delay_ms(2);

    i2c->start(); i2c->wait(TW_START);
    i2c->select(CCS811_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //Select APP_START 0xF4
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    i2c->repeatedStart(); i2c->wait(TW_START);
    i2c->select(CCS811_I2C_ADDRESS, TW_READ); i2c->wait(TW_MR_SLA_ACK);
    i2c->readNack(); i2c->wait(TW_MR_DATA_NACK);
    this->data[CCS811Data::STATUS] = i2c->getData();
    i2c->stop();

    if ( (this->data[CCS811Data::STATUS] & 0x90) != 0x90 ) { // FW_MODE=1 and APP_LOADED=1 otherwise cannot work!
        return 1;
    }

    return 0;
}

uint16_t CCS811Driver::getCO2Data() {
    uint16_t t = this->data[CCS811Data::CO2_MSB] << 8;
    t         |= this->data[CCS811Data::CO2_LSB];

    return t;
}

uint16_t CCS811Driver::getTVOCData() {
    uint16_t t = this->data[CCS811Data::TVOC_MSB] << 8;
    t         |= this->data[CCS811Data::TVOC_LSB];

    return t;
}
