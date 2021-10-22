#include "drivers/MCP7940NDriver.h"

#include <util/twi.h>
#include <tasks/Atmega324PBI2C0.h>

#include <stdio.h>

/* for the setup
bit 4 PWRFAIL: Power Failure Status bit(1,2)
1 = Primary power was lost and the power-fail time-stamp registers have been loaded (must be
cleared in software). Clearing this bit resets the power-fail time-stamp registers to ‘0’.
0 = Primary power has not been lost
bit 3 VBATEN: External Battery Backup Supply (VBAT) Enable bit
1 = VBAT input is enabled
0 = VBAT input is disabled
*/
uint8_t MCP7940NDriver::setup() {
    MCP7940_MFP_DDR = MCP7940_MFP_DDR & ~(1 << MCP7940_MFP_PIN); // Set the MFP pin as input.

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    if ( !i2c->isConnected(MCP7940_I2C_ADDRESS) ) {
        return 1; // Cannot select the chip
    }

    this->rtcTime = this->getTime();

    // TODO: Finish the setup! Read the date

    this->samplingInterval = 1000; // msecond
    this->loopTiming       = 0;

    this->rtcTime = RTCTime(01, 02, 03, 04, 05, 06, 07);
    this->setTimeLoop();

/*
    // start clock
    i2c->start();
    i2c->select(MCP7940_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x07); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0b0000'0100); i2c->wait(TW_MT_DATA_ACK);

    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(MCP7940_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x04); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0b0000'0001); i2c->wait(TW_MT_DATA_ACK);

    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(MCP7940_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0b1000'0000); i2c->wait(TW_MT_DATA_ACK);
    
    i2c->stop();
    // end
*/
    return 0;
}

uint8_t MCP7940NDriver::loop(uint32_t millis) {
    if ( this->loopTiming == 0 ) { // Start the timing process
        this->loopTiming = millis;        
    }

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    uint32_t loopTime = (millis - this->loopTiming);
    if ( loopTime > this->samplingInterval && i2c->isAvailable() ) {
        this->getTimeLoop(); 
        this->loopTiming = millis; // Restart the timing
    }

    return 0;
}

void MCP7940NDriver::sample() {
    //Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    //i2c->release(this);
    //RTCTime t("20110101T10:11:11");
    //this->rtcEvent->rtcReadTimestampEvent(this);

}

uint8_t MCP7940NDriver::reset() {
    // TODO
    return 0;
}

uint8_t MCP7940NDriver::sleep() {
    // TODO
    return 0;
}

uint8_t MCP7940NDriver::wakeup() {
    // TODO
    return 0;
}

bool MCP7940NDriver::isConnected() {
    return false;
}

RTCTime MCP7940NDriver::getPowerDownTimestamp() {
    // TODO
    return RTCTime(PSTR("20110101T10:10:10"));
 }

RTCTime MCP7940NDriver::getTime() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    i2c->start(); i2c->wait(TW_START);
    i2c->select(MCP7940_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    
    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(MCP7940_I2C_ADDRESS, TW_READ); i2c->wait(TW_MR_SLA_ACK);
    
    uint8_t data[7];
    for ( uint8_t i=0; i < 7; ++i ) {
        i2c->readAck(); i2c->wait(TW_MR_DATA_ACK);
        data[i] = i2c->getData();
    }

    i2c->repeatedStart(); i2c->wait(TW_REP_START);
    i2c->select(MCP7940_I2C_ADDRESS, TW_WRITE); i2c->wait(TW_MT_SLA_ACK);
    i2c->write(0x00); i2c->wait(TW_MT_DATA_ACK);
    i2c->write(0x80 | data[0]); i2c->wait(TW_MT_DATA_ACK); // Set ST bit!

    i2c->stop();

    return RTCTime(data);
}

// Kan ook weg na de test!!
#include <boards/Board.h>
void MCP7940NDriver::i2cReadEvent(uint8_t data, uint8_t index) {
    SmartSensorBoard* board = SmartSensorBoard::getBoard();

    this->data[index] = data;

    if ( index == 6 ) { // last one!
        this->rtcTime = RTCTime(this->data);
        char m[30];
        this->rtcTime.getIso8601String(m);
        board->debugf_P(PSTR("TIME LOOP: %s\n"), m);
    }
}

void MCP7940NDriver::getTimeLoop() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    if ( i2c->isAvailable() ) {
        i2c->cmdStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x00); // Select start address 0x00
        i2c->cmdRepeatedStart();
        i2c->cmdSelectRead(MCP7940_I2C_ADDRESS);
        i2c->cmdReadAck(this, 0); // seconds
        i2c->cmdReadAck(this, 1); // minutes
        i2c->cmdReadAck(this, 2); // hours
        i2c->cmdReadAck(this, 3); // weekday
        i2c->cmdReadAck(this, 4); // day
        i2c->cmdReadAck(this, 5); // month
        i2c->cmdReadNack(this, 6); // year
        i2c->cmdStop(); 
    }
}

/*
: To avoid rollover issues when loading
new time and date values, the oscillator/
clock input should be disabled by clearing
the ST bit for External Crystal mode and
the EXTOSC bit for External Clock Input
mode. After waiting for the OSCRUN bit
to clear, the new values can be loaded
and the ST or EXTOSC bit can then be
re-enabled
*/

void MCP7940NDriver::setTime(const RTCTime &t) {
    this->rtcTime = t;

    //if ( )

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
}

void MCP7940NDriver::setTime(const char* iso8601) {
    RTCTime time(iso8601);
    this->setTime(time);
}

void MCP7940NDriver::setTimeLoop() {
    uint8_t data[7] ={
        RTCTime::int2bcd(this->rtcTime.getSeconds()),
        RTCTime::int2bcd(this->rtcTime.getMinutes()),
        RTCTime::int2bcd(this->rtcTime.getHours()),
        RTCTime::int2bcd(this->rtcTime.getWeekDay()),
        RTCTime::int2bcd(this->rtcTime.getDay()),
        RTCTime::int2bcd(this->rtcTime.getMonth()),
        RTCTime::int2bcd(this->rtcTime.getYear())
    };

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    if ( i2c->isAvailable() ) {
        i2c->cmdStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x07); // Switch off oscillator
        i2c->cmdWrite(0x00);
        i2c->cmdRepeatedStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x00); // Start address of register to write to
        i2c->cmdWrite(0x80 | data[0]);
        for ( uint8_t i=1; i < 7; ++i ) {
            i2c->cmdWrite(data[i]);
        }
        i2c->cmdRepeatedStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x03); // Switch on oscillator
        i2c->cmdWrite(data[3] | 0b0010'0000);
        i2c->cmdStop(); 
    }
}

