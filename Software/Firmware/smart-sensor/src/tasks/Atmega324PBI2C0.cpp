#include <tasks/Atmega324PBI2C0.h>

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <util/delay.h>

ISR(TWI0_vect) {
    if ( cbInterruptEvent != NULL ) {
        cbInterruptEvent->i2c0Interrupt();
    }
}

uint8_t Atmega324PBI2C0::setup() {
    TWSR0 = 0x00;
    TWBR0 = ((F_CPU/I2C_SCL_CLOCK)-16)/2;
    
    return 0;
}

uint8_t Atmega324PBI2C0::loop(uint32_t millis) {
    return 0;
}

uint8_t Atmega324PBI2C0::reset() {
    return 0;
}

uint8_t Atmega324PBI2C0::sleep() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

uint8_t Atmega324PBI2C0::wakeup() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

bool Atmega324PBI2C0::ready() {
    return (TWCR0 & (1<<TWINT));
}

bool Atmega324PBI2C0::status(uint8_t status) {
    return (TWSR0 & 0xF8) == status;
}

bool Atmega324PBI2C0::wait(uint8_t status) { // TW_START
    while (!(TWCR0 & (1<<TWINT)));
    return (TWSR0 & 0xF8) == status;
}

void Atmega324PBI2C0::repeatedStart() { // Same as start different result
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
}

void Atmega324PBI2C0::start() {
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
}

void Atmega324PBI2C0::select(uint8_t address, uint8_t mode) {
    TWDR0 = address + mode;
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
}

void Atmega324PBI2C0::write(uint8_t data) {
    TWDR0 = data;
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
}

void Atmega324PBI2C0::readAck() {
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) | (1<<TWIE);
}

void Atmega324PBI2C0::readNack() {
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
}

uint8_t Atmega324PBI2C0::getData() {
    return TWDR0;
}

void Atmega324PBI2C0::stop() {
    TWCR0 = (1<<TWINT) | (1<<TWEN)|(1<<TWSTO) | (1<<TWIE);
}

bool Atmega324PBI2C0::claim(I2C0InterruptEvent* event) {
    if ( this->state != I2C0State::WAITING ) return false;

    cbInterruptEvent = event;
    //this->busy = true;
    return true;
}

bool Atmega324PBI2C0::release(I2C0InterruptEvent* event) {
    if ( this->state != I2C0State::WAITING ) return false;
    if ( event != cbInterruptEvent ) return false;

    cbInterruptEvent = NULL;
    //this->busy = false;

    return true;
}

bool Atmega324PBI2C0::isConnected(uint8_t address) {
    if ( this->state != I2C0State::WAITING ) return false; // Do nothing when already busy for another function!

    bool result = true;

    this->start();
    result = result & this->wait(TW_START);
    this->select(address, TW_WRITE);
    result = result & this->wait(TW_MT_SLA_ACK);
    this->stop();
    
    return result;
}
