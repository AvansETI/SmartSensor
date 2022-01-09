/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/VEML7700.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>

#include <tasks/Atmega324PBI2C0.h>

uint8_t VEML7700Driver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the SHTC3 chip
    }

    this->writeGain(VEML7700_GAIN_1);

    this->samplingInterval = 10; // 10s
    this->samplingTimestamp = 0;

    return 0;
}

//function to write gain to sensor, gains are defined in the VEML7700.h file, please use those provided
uint8_t VEML7700Driver::writeGain(uint8_t gain) {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    i2c->start(); i2c->wait(TW_START);
    //select config
    i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //write to config register 0x00
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    //write gain
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    //will overwrite without bitshifting, doesn't work with bitshifting WIP
    uint8_t tempValue = 0x00;
    i2c->write((tempValue &= ~(0x03 << 3)) |= ((gain & 0x03) << 3)); i2c->wait(TW_MT_DATA_ACK);
    i2c->stop();

    return 0;
}

bool VEML7700Driver::isConnected() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    return i2c->isConnected(VEML7700_I2C_ADDRESS);
}

uint8_t VEML7700Driver::loop(uint32_t millis) {
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

uint8_t VEML7700Driver::reset() {

    return 0;
}

uint8_t VEML7700Driver::sleep() {
    
    return 0;
}

uint8_t VEML7700Driver::wakeup() {
    
    return 0;
}

void VEML7700Driver::i2cReadEvent(uint8_t data, uint8_t index) {
    this->data[index] = data;

    if ( index == VEML7700Data::ALS_MSB ) { // All the measurements have been received.
        char m[30];

        sprintf_P(m, PSTR("li:%.1f"), (double)this->getLuminosity());
        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));
    }
}

uint8_t VEML7700Driver::sample() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    
    if ( i2c->isAvailable() ) {
        this->waitingOnI2C = false;
        i2c->cmdStart();
        i2c->cmdSelectWrite(VEML7700_I2C_ADDRESS);
        i2c->cmdWrite(0x04); // ALS register
        i2c->cmdRepeatedStart();
        i2c->cmdSelectRead(VEML7700_I2C_ADDRESS);
        i2c->cmdReadAck(this, 0); // ALS 0 (LSB)
        i2c->cmdReadNack(this, 1); // ALS 1 (MSB)
        i2c->cmdStop();
    
    } else {
        this->waitingOnI2C = true;
    }

    return 0;
}

uint16_t VEML7700Driver::getAlsData() {
    uint16_t t = this->data[VEML7700Data::ALS_MSB] << 8;
    t         |= this->data[VEML7700Data::ALS_LSB];

    return t;
}

float VEML7700Driver::getLuminosity() {
    return float(this->getAlsData() * 0.0576f);
}
