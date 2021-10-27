#include <drivers/XBeeProS2C.h>

#include <stdlib.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <tasks/Atmega324PBSerial1.h>
#include <tasks/Atmega324PBSerial0.h>

#include <boards/Board.h>
uint8_t XBeeProS2C::setup() {
    XBEEPROS2C_SLEEP_DDR = XBEEPROS2C_SLEEP_DDR | (1 << XBEEPROS2C_SLEEP_PIN); // Set the pin as output to drive the sleep pin
    this->wakeup();

    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();

    x->setCallback(this); // Recieve all characters on serial 1 to me.

    return 0;
}

uint8_t XBeeProS2C::loop(uint32_t millis) {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();

    // Check timeout when it is not in a waiting state!

    //s->print("State: "); s->transmitChar('0' + this->state); s->print("\n");

    switch (this->state) {
    case 0: // Start
        this->atStart();
        this->state++;
        this->timestamp = millis;
        break;

    case 1: // Start recieve
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            if ( this->recieveBuffer[0] == 'O' && this->recieveBuffer[1] == 'K' ) {
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBeeProS2C: Found\n"));
                this->state++;

            } else {
                this->state = 0; // Start over!
            }

        } else { // Not processing yet!
            if ( millis - this->timestamp > XBEEPROS2C_TIMEOUT_TIME_S ) { 
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBeeProS2C: Not found\n"));
                this->state = XBEEPROS2C_STATE_NOTFOUND;
            }
        }
        break;

    case 2: // Get PAN ID
        this->atGetPanId();
        this->state++;
        break;

    case 3:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C PAN ID: %s\n"), this->recieveBuffer);
            this->state++;
        }
        break;

    case 4:
        this->atGetSerialNumberHigh();
        this->state++;
        break;
    
    case 5:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C SERIAL: %s"), this->recieveBuffer);
            this->state++;
        }
        break;

    case 6:
        this->atGetSerialNumberLow();
        this->state++;
        break;
    
    case 7:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            SmartSensorBoard::getBoard()->debugf_P(PSTR("%s\n"), this->recieveBuffer);
            this->state++;
        }
        break;

    case 8:
        this->atGetCoordinatorEnable();
        this->state++;
        break;
    
    case 9:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            SmartSensorBoard::getBoard()->debugf_P(PSTR("Coordinator enabled: %s\n"), this->recieveBuffer);
            this->state++;
        }
        break;

    }

    return 0;
}

uint8_t XBeeProS2C::reset() {
    return 0;
}

uint8_t XBeeProS2C::sleep() {
    XBEEPROS2C_SLEEP_PORT = XBEEPROS2C_SLEEP_PORT | (1 << XBEEPROS2C_SLEEP_PIN); // Sleep 
    return 0;
}

uint8_t XBeeProS2C::wakeup() {
    XBEEPROS2C_SLEEP_PORT = XBEEPROS2C_SLEEP_PORT & ~(1 << XBEEPROS2C_SLEEP_PIN); // Wake 
    return 0;
}

void XBeeProS2C::recievedCharacter(char c) {

    switch (this->stateReciever) {
    case XBeeProS2CStateReciever::IDLE:
        if ( c != '\r') {
            this->recieveBuffer[0] = c;
            this->recieveBufferPointer = 1;
            this->stateReciever = XBeeProS2CStateReciever::BUSY;
        }
        break;

    case XBeeProS2CStateReciever::BUSY:
        this->recieveBuffer[this->recieveBufferPointer] = c;

        if ( this->recieveBufferPointer > XBEEPROS2C_RECIEVE_BUFFER_AMOUNT - 1 ) { // Error, beyond the buffer!
            Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();
            s->print_P(PSTR("XBEE: Buffer overflow!\n"));
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
        }

        if ( c == '\r' ) { // Ready!
            this->recieveBuffer[this->recieveBufferPointer] = '\0'; // replace \r with \0 end character
            this->stateReciever = XBeeProS2CStateReciever::PROCESSING;
        }

        this->recieveBufferPointer++;

        break;

    case XBeeProS2CStateReciever::PROCESSING: // Help, the previous data has not been processed yet!
        {
            Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();
            s->print_P(PSTR("Recieved character while it has not bee processed yet!\n"));
        }
        break;

    }

}

void XBeeProS2C::enableCoordinator() {
    this->isCoordinator = true;
}

void XBeeProS2C::atStart() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("+++"));
}

void XBeeProS2C::atGetPanId() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATID\r"));
}

void XBeeProS2C::atGetCoordinatorEnable() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATCE\r"));
}

void XBeeProS2C::atGetSerialNumberHigh() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATSH\r"));
}

void XBeeProS2C::atGetSerialNumberLow() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATSL\r"));
}

void XBeeProS2C::test() {
    Atmega324PBSerial1* s = Atmega324PBSerial1::getInstance();
    Atmega324PBSerial0* d = Atmega324PBSerial0::getInstance();

    char c = 0x00;

    d->print("XBEE SEND\n");
    // Perform a first setup of the XBee Module
    s->print("+++"); // COMMAND MODE AT
    _delay_ms(500);
    s->print("AT\r");
    _delay_ms(100);
    s->print("ATAP\r"); // Enable API mode
    _delay_ms(100);
    s->print("ATAO\r"); // Enable API Explicit mode
    _delay_ms(100);
    s->print("ATAP 1\r"); // Enable API mode
    _delay_ms(100);
    s->print("ATAO 0\r"); // Enable API Explicit mode
    _delay_ms(100);
    d->print("END\n");

/*
    s->transmitChar(0x7E);
    s->transmitChar(0x00);
    s->transmitChar(0x04);
    s->transmitChar(0x08); // AT Command
    s->transmitChar(0x01);
    s->transmitChar(0x56); // VR
    s->transmitChar(0x52);
    s->transmitChar(0xFF-(0x08+0x01+0x56+0x52));
*/
}
