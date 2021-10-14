#include "drivers/VEML7700.h"

#include <stdio.h>
#include <string.h>
#include <util/twi.h>
#include <util/I2C0.h>
#include <util/Serial0.h>

//TODO: Reset, Sleep, and wakeup functions
//TODO: Figure out checksum, productcode and id
//TODO: Figure out how accurate the VEML7700 sensor is, currently readings sometimes vary greatly from what is expected
//TODO: Figure out how to properly utilise all config

uint8_t VEML7700Driver::setup() {
    if (!this->isConnected())
    {
        return 1; //cannot select the VEML7700
    }

    this->configValue = 0x00;

    I2C0* i2c = I2C0::getInstance();
    //start I2C
    i2c->start(); i2c->wait(TW_START);
    // //Select VEML7700 Address
    // i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    // //write to config
    // i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    // //write shutdown true
    // i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    // //Select VEML7700 Address
    // i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    // //write to config
    // i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    // //write persistence
    // i2c->write(VEML7700_PERS_1 << 4); i2c->wait(TW_MT_DATA_ACK);
    // //select VEML7700 Address
    // i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    // //write to config
    // i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    // //write interrupt
    // i2c->write(VEML7700_IT_100MS << 6); i2c->wait(TW_MT_DATA_ACK);
    // //Select VEML7700 Address
    // i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    // //write to config
    // i2c->write(VEML7700_POWER_SAVE); i2c->wait(TW_MT_DATA_ACK);
    // //write power_save disable
    // i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    // //Select VEML7700 Address
    // i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    // //write to config
    // i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    // //write Shutdown false
    // i2c->write(0x01); i2c->wait(TW_MT_DATA_ACK);
    this->writeGain(VEML7700_GAIN_1);
    i2c->stop();
    

    //minimum interval of 2.5 seconds as per VEML7700 documentation
    this->samplingInterval = 3*1; // seconds
    this->loopTiming       = 0;

    return 0;
        
}

bool VEML7700Driver::isConnected() {
    I2C0* i2c = I2C0::getInstance();
    return i2c->isConnected(VEML7700_I2C_ADDRESS);
}

//function to read all of the config, used with the configValue variable to keep track of all parts of config
//also functions as an update of the configValue
uint16_t VEML7700Driver::readConfig() {
    I2C0* i2c = I2C0::getInstance();
    i2c->start(); i2c->wait(TW_START);
    //read from config, the current gain
    i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(VEML7700_I2C_ADDRESS, TW_READ); i2c->wait(TW_MR_SLA_ACK);
    //read command, shift bits so the two 8bit recieved become one 16bit
    i2c->readAck(); i2c->wait(TW_MR_DATA_ACK);
    this->configValue = i2c->getData();
    i2c->readNack(); i2c->wait(TW_MR_DATA_NACK);
    this->configValue |= i2c->getData() << 8;
    i2c->stop();

    return this->configValue;
}

//function to write shutdown command to the sensor, 0x00 is on, 0x01 is off
//for all write commands please use defines from the header file when available to prevent errors
uint8_t VEML7700Driver::writeShutdown(uint8_t power) {
    
    I2C0* i2c = I2C0::getInstance();
    i2c->start(); i2c->wait(TW_START);
    //select config
    i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //write to config
    i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    //write gain
    uint8_t tempValue = this->configValue << 8;
    i2c->write((tempValue &= ~((power & 0x01) << 0)) |= ((power & 0x01) << 0)); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(this->configValue >> 8); i2c->wait(TW_MT_DATA_ACK);
    // i2c->write(0b0001'1000); i2c->wait(TW_MT_DATA_ACK);
    i2c->stop();

    return 0;
}

//function to read the gain from the sensor
uint8_t VEML7700Driver::readGain() {

    uint8_t currentGain = 0x00;
    uint8_t tempValue = this->configValue >> 8;
    currentGain = tempValue & (0x03 << 3);
    return currentGain;
}

//function to write gain to sensor, gains are defined in the VEML7700.h file, please use those provided
uint8_t VEML7700Driver::writeGain(uint8_t gain) {
    I2C0* i2c = I2C0::getInstance();
    i2c->start(); i2c->wait(TW_START);
    //select config
    i2c->select(VEML7700_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    //write to config
    i2c->write(VEML7700_CONFIG); i2c->wait(TW_MT_DATA_ACK);
    //write gain
    i2c->write(this->configValue << 8); i2c->wait(TW_MT_DATA_ACK);
    uint8_t tempValue = this->configValue;
    i2c->write((tempValue &= ~((gain & 0x03) << 3)) |= ((gain & 0x03) << 3)); i2c->wait(TW_MT_DATA_ACK);
    i2c->stop();

    return 0;
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
            i2c->readNack();
            break;
        case 8:
            this->state++;
            i2c->status(TW_MR_DATA_NACK);
            i2c->getData();
            i2c->stop();
            this->readConfig();
            if (this->testloop == 0)
            {
                // this->readGain();
                this->writeGain(VEML7700_GAIN_1);
            }
            if (this->testloop == 3)
            {
                // this->readGain();
                this->writeGain(VEML7700_GAIN_1_8);
            }
            if (this->testloop == 6)
            {
                // this->readGain();
                this->writeGain(VEML7700_GAIN_2);
            }
            if (this->testloop == 9)
            {
                this->writeShutdown(VEML7700_POWER_OFF);
            }
            if (this->testloop == 12)
            {
                this->writeShutdown(VEML7700_POWER_ON);
            }
            if (this->testloop == 15)
            {
                this->testloop = 0;
            } else {
                this->testloop++;
            }
            
            i2c->release(this);
            
            Serial0* s = Serial0::getInstance();
            char m[30];
            float _luminosity = float(this->lightValue) * 0.0576f;
            
            sprintf_P(m, PSTR("Luminosity:%.1f\n"), (double)_luminosity);
            s->print(m);
            this->getMeasurementCallback()->addMeasurement(m);
            sprintf_P(m, PSTR("Config:%p\n"), this->readConfig());
            s->print(m);
            sprintf_P(m, PSTR("Gain:%p\n"), this->readGain());
            s->print(m);
            
            this->setDataValid();
            this->state = 0; // Start over
    }
    return 0;
}

void VEML7700Driver::i2c0Interrupt() {
    this->sampleLoop();
}