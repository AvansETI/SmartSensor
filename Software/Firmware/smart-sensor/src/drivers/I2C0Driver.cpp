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
    
    this->start();
    this->wait(TW_START);
    this->select(0xE0, TW_WRITE);
    this->wait(TW_MT_SLA_ACK);
    this->write(0x5C);
    this->wait(TW_MT_DATA_ACK);
    this->write(0x24);
    this->wait(TW_MT_DATA_ACK);

    this->repeatedStart();
    this->wait(TW_REP_START);
    this->select(0xE0, TW_READ);
    this->wait(TW_MR_SLA_ACK);
    
    this->readAck();
    this->wait(TW_MR_DATA_ACK);
    uint16_t humidity = this->getData() << 8;
    this->readAck();
    this->wait(TW_MR_DATA_ACK);
    humidity |= this->getData();

    this->readAck();
    this->wait(TW_MR_DATA_ACK);
    uint8_t checksumHumidity = this->getData();

    this->readAck();
    this->wait(TW_MR_DATA_ACK);
    uint16_t temperature = this->getData() << 8;
    this->readAck();
    this->wait(TW_MR_DATA_ACK);
    temperature |= this->getData();

    this->readNack();
    this->wait(TW_MR_DATA_ACK);
    uint8_t checksumTemperature = this->getData();

    this->stop();

    float _humidity = 100 * float(humidity) / 65536.0f;
    float _tempature = 175 * float(temperature) / 65536.0f - 45.0f;

    Serial0* serial0 = Serial0::getInstance();

    char message[50];

    sprintf(message, "H: %0.1f, T: %0.1f", _humidity, _tempature);

    serial0->print(message);

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
    return !(TWCR0 & (1<<TWINT));
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
