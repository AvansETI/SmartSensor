#include "drivers/I2C0Driver.h"

#include "avr/io.h"
#include <util/twi.h>
#include <util/delay.h>

#include <util/Serial0.h> // moet weg na debug!
#include <stdio.h>

uint8_t I2C0Driver::setup() {
    TWSR0 = 0x00;
    TWBR0 = ((F_CPU/I2C_SCL_CLOCK)-16)/2;
    
    return 0;
}

uint8_t I2C0Driver::loop(uint32_t millis) {
    // Experiment to test whether the I2C0 works and how non blocking I2C could be done, experiment with switch!

    // CASE works, now we can look to some call back functionality when data is ready or future things.

    switch(this->state) {
        case 0:
            this->startI2C = millis;
            this->start();
            this->state++;
            break;
        case 1:
            if ( this->ready() ) {
                this->status(TW_START);
                this->state++;
            }
            break;
        case 2:
            this->select(0xE0, TW_WRITE);
            this->state++;
            break;
        case 3:
            if ( this->ready() ) {
                this->status(TW_MT_SLA_ACK);
                this->state++;
            }
            break;
        case 4:
            this->write(0x5C);
            this->state++;
            break;
        case 5:
            if ( this->ready() ) {
                this->status(TW_MT_DATA_ACK);
                this->state++;
            }
            break;
        case 6:
            this->write(0x24);
            this->state++;
            break;
        case 7:
            if ( this->ready() ) {
                this->status(TW_MT_DATA_ACK);
                this->state++;
            }
            break;
        case 8:
            this->repeatedStart();
            this->state++;
            break;
        case 9:
            if ( this->ready() ) {
                this->status(TW_REP_START);
                this->state++;
            }
            break;
        case 10:
            this->select(0xE0, TW_READ);
            this->state++;
            break;
        case 11:
            if ( this->ready() ) {
                this->status(TW_MR_SLA_ACK);
                this->state++;
            }
            break;
        case 12:
            this->readAck();
            this->state++;
            break;
        case 13:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 14:
            this->humidity = this->getData() << 8;
            this->readAck();
            this->state++;
            break;
        case 15:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 16:
            this->humidity |= this->getData();
            this->readAck();
            this->state++;
            break;
        case 17:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 18:
            this->getData();
            this->readAck();
            this->state++;
            break;
        case 19:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 20:
            this->temperature = this->getData() << 8;
            this->readAck();
            this->state++;
            break;
        case 21:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 22:
            this->temperature |= this->getData();
            this->readNack();
            this->state++;
            break;
        case 23:
            if ( this->ready() ) {
                this->status(TW_MR_DATA_ACK);
                this->state++;
            }
            break;
        case 24:
            this->getData();
            this->stop();
            this->state++;
            break;
        case 25:
            uint16_t timing = millis - this->startI2C;
            Serial0* serial0 = Serial0::getInstance();
            char message[20];
            sprintf(message, "I2C Timing: %l ms\n", timing);

            float _humidity = 100 * float(this->humidity) / 65536.0f;
            float _tempature = 175 * float(this->temperature) / 65536.0f - 45.0f;
            //sprintf(message, "H: %0.1f, T: %0.1f\n", (double)_humidity, (double)_tempature);
            serial0->print(message);
            this->state = 0; // Start over
    }

    return 0;
}

uint8_t I2C0Driver::reset() {

    return 0;
}

uint8_t I2C0Driver::sleep() {
    return 0;
}

uint8_t I2C0Driver::wakeup() {
    return 0;
}

bool I2C0Driver::ready() {
    return (TWCR0 & (1<<TWINT));
}

bool I2C0Driver::status(uint8_t status) {
    return (TWSR0 & 0xF8) == status;
}

bool I2C0Driver::wait(uint8_t status) { // TW_START
    while (!(TWCR0 & (1<<TWINT)));
    return (TWSR0 & 0xF8) == status;
}

void I2C0Driver::repeatedStart() { // Same as start different result
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void I2C0Driver::start() {
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void I2C0Driver::select(uint8_t address, uint8_t mode) {
    TWDR0 = address + mode;
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

void I2C0Driver::write(uint8_t data) {
    TWDR0 = data;
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

void I2C0Driver::readAck() {
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
}

void I2C0Driver::readNack() {
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

uint8_t I2C0Driver::getData() {
    return TWDR0;
}

void I2C0Driver::stop() {
    TWCR0 = (1<<TWINT) | (1<<TWEN)|(1<<TWSTO);
}
