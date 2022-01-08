/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <tasks/Atmega324PBI2C0.h>

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <util/delay.h>

#include <boards/Board.h>

uint8_t Atmega324PBI2C0::setup() {
    TWSR0 = 0x00;
    TWBR0 = ((F_CPU/I2C0_SCL_CLOCK)-16)/2;
    
    this->timer = 0;
    this->state = I2CState::WAITING;

    return 0;
}

uint8_t Atmega324PBI2C0::loop(uint32_t millis) { // TODO: Use millis to check when the I2C is stuck.
    SmartSensorBoard *b = SmartSensorBoard::getBoard();
    //b->debugf("Total commands: %d, data: %d\n", this->commands.size(), this->data.size());

    switch (this->state) {
    case I2CState::WAITING:
        if ( this->commands.size() > 0 ) {
            this->state = I2CState::COMMAND;
        }
        break;

    case I2CState::COMMAND:
        executeCommand();
        this->state = I2CState::CHECK;
        break;

    case I2CState::CHECK:
        {
            I2CCommand* command = this->commands.peek();

            if ( this->ready() || *command == I2CCommand::STOP ) { // When the I2C operation has finished, proceed to check the status.
                this->state = I2CState::STATUS;
            }
        }
        break;

    case I2CState::STATUS:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            I2CCommand* command = this->commands.pop();
            if ( *command != I2CCommand::STOP ) {
                uint8_t status = pgm_read_byte(&I2CCommandResultStatus[*command]);
                if ( this->status(status) ) { // The status is correct, we are finished!
                    if ( *command == I2CCommand::READ_ACK || *command == I2CCommand::READ_NACK ) { // Get the data!
                        I2CReadEvent** readEvent = this->cbReadEvents.pop();
                        uint8_t index = *this->data.pop();
                        readEvent[0]->i2cReadEvent(this->getData(), index);
                    }

                } else { // The status is not correct, empty the queue
                    b->debugf_P(PSTR("I2C0 Error: command: %d, status: %d, got: %d\n"), *command, status, (int) (TWSR0 & 0xF8));
                    //this->commands.empty();
                    //this->data.empty();
                    //this->cbReadEvents.empty();
                }

            }
            this->state = I2CState::WAITING;
        }
        break;
    }

    return 0;
}

void Atmega324PBI2C0::executeCommand() {
    I2CCommand* command = this->commands.peek();
    switch (*command) {
    case I2CCommand::START:
        this->start();
        break;
    
    case I2CCommand::REPEATED_START:
        this->repeatedStart();
        break;

    case I2CCommand::SELECT_WRITE:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            uint8_t address = *this->data.pop();
            this->select(address, TW_WRITE);
        }
        break;

    case I2CCommand::SELECT_READ:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            uint8_t address = *this->data.pop();
            this->select(address, TW_READ);
        }
        break;

    case I2CCommand::WRITE:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            uint8_t data = *this->data.pop();
            this->write(data);
        }
        break;

    case I2CCommand::READ_ACK:
        this->readAck();
        break;

    case I2CCommand::READ_NACK:
        this->readNack();
        break;

    case I2CCommand::STOP:
        this->stop();
        break;
    }

    // When the command is executed, check when the I2C process is ready!
    this->state = I2CState::CHECK;
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

uint8_t Atmega324PBI2C0::cmdStart() {
    this->commands.add(I2CCommand::START);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdRepeatedStart() {
    this->commands.add(I2CCommand::REPEATED_START);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdSelectWrite(uint8_t address) {
    this->commands.add(I2CCommand::SELECT_WRITE);
    this->data.add(address);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdSelectRead(uint8_t address) {
    this->commands.add(I2CCommand::SELECT_READ);
    this->data.add(address);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdWrite(uint8_t byte) {
    this->commands.add(I2CCommand::WRITE);
    this->data.add(byte);
    return 0;

}

uint8_t Atmega324PBI2C0::cmdReadAck(I2CReadEvent* cbReadEvent, uint8_t index) {
    this->commands.add(I2CCommand::READ_ACK);
    this->cbReadEvents.add(cbReadEvent);
    this->data.add(index);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdReadNack(I2CReadEvent* cbReadEvent, uint8_t index) {
    this->commands.add(I2CCommand::READ_NACK);
    this->cbReadEvents.add(cbReadEvent);
    this->data.add(index);
    return 0;
}

uint8_t Atmega324PBI2C0::cmdStop() {
    this->commands.add(I2CCommand::STOP);
    return 0;
}

uint8_t Atmega324PBI2C0::isAvailable() {
    return ( this->commands.size() == 0 && this->state == I2CState::WAITING );
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
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void Atmega324PBI2C0::start() {
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void Atmega324PBI2C0::select(uint8_t address, uint8_t mode) {
    TWDR0 = address + mode;
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

void Atmega324PBI2C0::write(uint8_t data) {
    TWDR0 = data;
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

void Atmega324PBI2C0::readAck() {
    TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
}

void Atmega324PBI2C0::readNack() {
    TWCR0 = (1<<TWINT) | (1<<TWEN);
}

uint8_t Atmega324PBI2C0::getData() {
    return TWDR0;
}

void Atmega324PBI2C0::stop() {
    TWCR0 = (1<<TWINT) | (1<<TWEN)|(1<<TWSTO);
}

bool Atmega324PBI2C0::isConnected(uint8_t address) {
    if ( this->state != I2CState::WAITING ) return false; // Do nothing when already busy for another function!

    bool result = true;

    this->start();
    result = result & this->wait(TW_START);
    this->select(address, TW_WRITE);
    result = result & this->wait(TW_MT_SLA_ACK);
    this->stop();
    
    return result;
}
