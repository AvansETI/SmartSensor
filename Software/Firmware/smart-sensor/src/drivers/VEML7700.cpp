#include "drivers/VEML7700.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>
#include <util/I2C0.h>
#include <util/Serial0.h>

//TODO: Reset, Sleep, and wakeup functions
//TODO: Figure out checksum, productcode and id
//TODO: Figure out how accurate the VEML7700 sensor is, currently readings sometimes vary greatly from what is expected

uint8_t VEML7700Driver::setup() {
    if (!this->isConnected())
    {
        return 1; //cannot select the VEML7700
    }

    if (this->getId() == 0)
    {
        return 2; //incorrect ID given for VEML7700
    }

    //minimum interval of 2.5 seconds as per VEML7700 documentation
    this->samplingInterval = 3*1; // seconds
    this->loopTiming       = 0;

    return 0;
        
}

bool VEML7700Driver::isConnected() {
    I2C0* i2c = I2C0::getInstance();
    return i2c->isConnected(VEML7700_I2C_ADDRESS);
}

uint8_t VEML7700Driver::loop(uint32_t millis) {
    if (this->loopTiming == 0) //start timer
    {
        this->loopTiming = millis/1000;
    }

    I2C0* i2c = I2C0::getInstance();
    uint32_t loopTime = ((millis/1000) - this->loopTiming);

    if (loopTime > this->samplingInterval && this->state == 0 && i2c->claim(this))
    {
        this->sampleLoop();
        this->loopTiming = millis/1000;
    }
    
    return 0;
}

//TODO: WIP
uint8_t VEML7700Driver::reset() {
    return 0;
}

//TODO: WIP
uint8_t VEML7700Driver::sleep() {
    return 0;
}

//TODO: WIP
uint8_t VEML7700Driver::wakeup() {
    return 0;
}

//temp until checksum is figured out
//TODO: WIP
bool VEML7700Driver::checkChecksum(const uint16_t data, const uint8_t checksum) {

    return true;
}

//temp until product code is figured out
//TODO: WIP
uint16_t VEML7700Driver::getProductCode() {
    return this->getId() & 0;
}

//TODO: WIP
uint16_t VEML7700Driver::getId() {
    if ( this->id != 0 ) {
        return this->id;
    }

    I2C0* i2c = I2C0::getInstance();
    i2c->start(); i2c->wait(TW_START);
    i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0x01); i2c->wait(TW_MT_DATA_ACK);
    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(VEML7700_I2C_ADDRESS, TW_READ); i2c->wait(TW_MR_SLA_ACK);
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

//loop for collecting data, currently recieves data
uint8_t VEML7700Driver::sampleLoop() {

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
            i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE);
            break;
        case 2:
            this->state++;
            i2c->status(TW_MT_SLA_ACK);
            i2c->write(0x04);
            break;
        case 3:
            this->state++;
            i2c->status(TW_MT_DATA_ACK);
            i2c->repeatedStart();
            break;
        case 4:
            this->state++;
            i2c->status(TW_REP_START);
            i2c->select(VEML7700_I2C_ADDRESS, TW_READ);
            break;
        case 5:
            this->state++;
            i2c->status(TW_MR_SLA_ACK);
            i2c->readAck();
            break;
        case 6:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            this->lightValue = i2c->getData() << 8;
            i2c->readAck();
            break;
        case 7:
            this->state++;
            i2c->status(TW_MR_DATA_ACK);
            i2c->getData();
            i2c->stop();
            i2c->release(this);
            
            Serial0* s = Serial0::getInstance();
            char m[30];
            float _luminosity = float(this->lightValue) * 0.0576f;
            
            sprintf_P(m, PSTR("Luminosity: %.1f Lux\n"), (double)_luminosity);
            s->print(m);
            this->getMeasurementCallback()->addMeasurement(m);
            
            this->setDataValid();
            this->state = 0; // Start over
    }
    return 0;
}

void VEML7700Driver::i2c0Interrupt() {
    this->sampleLoop();
}