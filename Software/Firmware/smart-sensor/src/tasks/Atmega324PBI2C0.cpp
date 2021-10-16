#include <tasks/Atmega324PBI2C0.h>

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <util/delay.h>

ISR(TWI0_vect) {
    if ( cbInterruptEvent != NULL ) {
        cbInterruptEvent->i2cInterrupt();
    }
}

uint8_t Atmega324PBI2C0::setup() {
    TWSR0 = 0x00;
    TWBR0 = ((F_CPU/I2C_SCL_CLOCK)-16)/2;
    
    this->state = I2CState::WAITING;
    cbInterruptEvent = this;

    return 0;
}

uint8_t Atmega324PBI2C0::loop(uint32_t millis) {
    SmartSensorBoard* board = SmartSensorBoard::getBoard();
    board->debugf("LOOP I2C State: %d", this->state);

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

    case I2CState::CHECK: // TODO: This is interrupt driven, so nothing to do here! We could check after a while that things go wrong?!
    //    if ( this->ready() ) { // When the I2C operation has finished, proceed to check the status.
    //        this->state = I2CState::STATUS;
    //    }
        break;

    case I2CState::STATUS:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            I2CCommand* command = this->commands.pop();
            if ( *command != I2CCommand::STOP ) {
                uint8_t status = I2CCommandResultStatus[*command];
                if ( this->status(status) ) { // The status is correct, we are finished!
                    if ( *command == I2CCommand::READ_ACK || *command == I2CCommand::READ_NACK ) { // Get the data!
                        I2CReadEvent** readEvent = this->cbReadEvents.pop();
                        uint8_t index = *this->data.pop();
                        readEvent[0]->i2cReadEvent(this->getData(), index);
                    }

                } else { // The status is not correct, pop all commands until the stop command!
                    // TODO: Not yet implemented!
                }

            }
            this->state = I2CState::WAITING;
        }
        break;
    }

    return 0;
}

void Atmega324PBI2C0::i2cInterrupt() {
    if ( this->state != I2CState::CHECK ) {
        // TODO: Error!!!
    }

    this->state = I2CState::STATUS; // The state is check because the command has been given! I2C finished.
}

void Atmega324PBI2C0::executeCommand() {
    SmartSensorBoard* board = SmartSensorBoard::getBoard();

    I2CCommand* command = this->commands.peek();
    board->debugf("EXECUTE I2C: %d", *command);
    switch (*command) {
    case I2CCommand::START:
        this->start();
        break;
    
    case I2CCommand::REPEATED_START:
        this->repeatedStart();
        break;

    case I2CCommand::SELECT:
        { // Variable used inside a switch are known to all cases, so limiting the scope here.
            uint8_t address = *this->data.pop();
            uint8_t mode    = *this->data.pop();
            this->select(address, mode);
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

uint8_t Atmega324PBI2C0::cmdSelect(uint8_t address, uint8_t mode) {
    this->commands.add(I2CCommand::SELECT);
    this->data.add(address);
    this->data.add(mode);
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

bool Atmega324PBI2C0::claim(I2CInterruptEvent* event) {
    if ( this->state != I2CState::WAITING ) return false;

    cbInterruptEvent = event;
    //this->busy = true;
    return true;
}

bool Atmega324PBI2C0::release(I2CInterruptEvent* event) {
    if ( this->state != I2CState::WAITING ) return false;
    if ( event != cbInterruptEvent ) return false;

    cbInterruptEvent = NULL;
    //this->busy = false;

    return true;
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


// Kan ook weg na de test!!
void Atmega324PBI2C0::i2cReadEvent(uint8_t data, uint8_t index) {
    SmartSensorBoard* board = SmartSensorBoard::getBoard();
    board->debugf("READ I2C: [%d] => %d", index, data);
}

void Atmega324PBI2C0::test() {
    this->cmdStart();
    this->cmdSelect(0xE0, TW_WRITE);
    this->cmdWrite(0xEF);
    this->cmdWrite(0xC8);
    this->cmdRepeatedStart();
    this->cmdSelect(0xE0, TW_READ);
    this->cmdReadAck(this, 0);
    this->cmdReadAck(this, 1);
    this->cmdReadAck(this, 2);
    this->stop();    
}