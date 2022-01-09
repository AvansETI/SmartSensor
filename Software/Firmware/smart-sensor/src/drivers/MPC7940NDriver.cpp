/*
 * @file       : drivers/MPC7940NDriver.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/MCP7940NDriver.h"

#include <stdio.h>
#include <util/twi.h>

#include <tasks/Atmega324PBI2C0.h>

uint8_t MCP7940NDriver::setup() {
    this->flags = 0;

    MCP7940_MFP_DDR = MCP7940_MFP_DDR & ~(1 << MCP7940_MFP_PIN); // Set the MFP pin as input.

    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();
    if ( !i2c->isConnected(MCP7940_I2C_ADDRESS) ) {
        return 1; // Cannot select the chip
    }

    return 0;
}

uint8_t MCP7940NDriver::loop(uint32_t millis) {
    /* When the I2C0 bus was busy, this loop tries again until is is succeeded. */
    if ( Binary::isFlag(this->flags, MCP7940NFlags::TIME_GET_REQUESTED) ) {
        this->requestTime();
    }

    if ( Binary::isFlag(this->flags, MCP7940NFlags::TIME_SET_REQUESTED) ) {
        this->setTime();
    }
    return 0;
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

void MCP7940NDriver::requestTime() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    if ( !Binary::isFlag(this->flags, MCP7940NFlags::TIME_SET_REQUESTED) && i2c->isAvailable() ) {
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
        this->flags = Binary::clearFlag(this->flags, MCP7940NFlags::TIME_GET_REQUESTED);

    } else {
        this->flags = Binary::setFlag(this->flags, MCP7940NFlags::TIME_GET_REQUESTED);
    }
}

void MCP7940NDriver::i2cReadEvent(uint8_t data, uint8_t index) {
    this->data[index] = data;

    if ( index == 6 ) { // last one, so call the time is complete!
        RTCTime rtcTime(this->data);
        char time[MESSAGE_LENGTH];
        rtcTime.getIso8601String(time);
        char m[MESSAGE_LENGTH];
        sprintf(m, "ts:%s", time);
        this->getMessageInterface()->addMessage(Message(MessageType::TIMESTAMP, m));
    }
}

void MCP7940NDriver::setTime(const RTCTime &t) {
    this->data[0] = RTCTime::int2bcd(t.getSeconds());
    this->data[1] = RTCTime::int2bcd(t.getMinutes());
    this->data[2] = RTCTime::int2bcd(t.getHours());
    this->data[3] = RTCTime::int2bcd(t.getWeekDay());
    this->data[4] = RTCTime::int2bcd(t.getDay());
    this->data[5] = RTCTime::int2bcd(t.getMonth());
    this->data[6] = RTCTime::int2bcd(t.getYear());

    this->setTime();
}

void MCP7940NDriver::setTime() {
    Atmega324PBI2C0* i2c = Atmega324PBI2C0::getInstance();

    if ( i2c->isAvailable() ) {
        i2c->cmdStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x07); // Switch off oscillator
        i2c->cmdWrite(0x00);
        i2c->cmdRepeatedStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x00); // Start address of register to write to
        i2c->cmdWrite(0x80 | this->data[0]);
        for ( uint8_t i=1; i < 7; ++i ) {
            i2c->cmdWrite(this->data[i]);
        }
        i2c->cmdRepeatedStart();
        i2c->cmdSelectWrite(MCP7940_I2C_ADDRESS);
        i2c->cmdWrite(0x03); // Switch on oscillator and VBAT enable for backup battery
        i2c->cmdWrite(this->data[3] | 0b0010'1000);
        i2c->cmdStop();
        this->flags = Binary::clearFlag(this->flags, MCP7940NFlags::TIME_SET_REQUESTED);

    } else {
        this->flags = Binary::setFlag(this->flags, MCP7940NFlags::TIME_SET_REQUESTED);
    }
}

void MCP7940NDriver::setTime(const char* iso8601) {
    RTCTime time(iso8601);
    this->setTime(time);
}
