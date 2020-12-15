#include <boardsupport.h>
#include "board-support/drivers/TWIDriver.h"

TWIDriver::TWIDriver(TWIDriver::Instance instance) {
    m_instance = instance;
}

void TWIDriver::init() {
    #if TWI0_ENABLED
        TWI0_SR = 0;
        TWI0_BR = ((F_CPU/TWI0_SCL_CLOCK)-16)/2;
    #endif

    #if TWI1_ENABLED
        TWI1_SR = 0;
        TWI1_BR = ((F_CPU/TWI1_SCL_CLOCK)-16)/2;
    #endif
}

bool TWIDriver::twi_start() {
    uint8_t status;

    if (m_instance == TWI0) {
        TWI0_CR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        twi_wait();
        status = TWI0_SR & 0xF8;
    } else {
        TWI1_SR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        twi_wait();
        status = TWI1_SR & 0xF8;
    }

    return status == TW_START || status != TW_REP_START;
}

void TWIDriver::twi_stop() {
    if (m_instance == TWI0) {
        TWI0_CR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

        #ifndef NATIVE_UNIT_TEST
            while (TWI0_CR & (1 << TWSTO));
        #endif
    } else {
        TWI1_CR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
        #ifndef NATIVE_UNIT_TEST
            while (TWI1_CR & (1 << TWSTO));
        #endif
    }
}

void TWIDriver::twi_wait() {
    #ifndef NATIVE_UNIT_TEST
        if (m_instance == TWI0)
            while (!(TWI0_CR & (1 << TWINT)));
        else
            while (!(TWI1_CR & (1 << TWINT)));
    #endif
}

bool TWIDriver::twi_select(uint8_t addr, TWIDriver::SelectMode mode) {
    uint8_t status;

    if (m_instance == TWI0) {
        TWI0_DR = addr + mode;
        TWI0_CR = (1 << TWINT) | (1 << TWEN);

        twi_wait();

        status = TWI0_SR & 0xF8;
    } else {
        TWI1_DR = addr + mode;
        TWI1_CR = (1 << TWINT) | (1 << TWEN);

        twi_wait();

        status = TWI1_SR & 0xF8;
    }

    return status == TW_MT_SLA_ACK || status == TW_MR_SLA_ACK;
}

void TWIDriver::twi_write(uint8_t data) {
    if (m_instance == TWI0) {
        TWI0_DR = data;
        TWI0_CR = (1 << TWINT) | (1 << TWEN);
    } else {
        TWI1_DR = data;
        TWI1_CR = (1 << TWINT) | (1 << TWEN);
    }

    twi_wait();
    // TODO: Check TWSRn register for status DATA_ACK
}

uint8_t TWIDriver::twi_read_ack() {
    if (m_instance == TWI0)
        TWI0_CR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    else
        TWI1_CR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    twi_wait();

    if (m_instance == TWI0)
        return TWI0_DR;

    return TWI1_DR;
}

uint8_t TWIDriver::twi_read_nack() {
    if (m_instance == TWI0)
        TWI0_CR = (1 << TWINT) | (1 << TWEN);
    else
        TWI1_CR = (1 << TWINT) | (1 << TWEN);

    twi_wait();

    if (m_instance == TWI0)
        return TWI0_DR;

    return TWI1_DR;
}
