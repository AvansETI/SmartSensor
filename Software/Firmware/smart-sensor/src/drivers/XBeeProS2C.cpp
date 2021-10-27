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

    Atmega324PBSerial1::getInstance()->setCallback(this); // Recieve all characters on serial 1 to me.

    return 0;
}

uint8_t XBeeProS2C::loop(uint32_t millis) {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();

    if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) { // Process the recieved line!
        s->print("XBEE Recieved: "); s->print(this->recieveBuffer); s->print("\n");
        this->stateReciever = XBeeProS2CStateReciever::IDLE;
        this->state = 0;
    }

    if ( this->state == 0 ) {
        s->print("XBEE SEND\n");
        x->printAsync("+++");
        this->state++;
    }

    //this->test();
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
        this->recieveBufferPointer++;

        if ( this->recieveBufferPointer > XBEEPROS2C_RECIEVE_BUFFER_AMOUNT - 1 ) { // Error, beyond the buffer!
            Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();
            s->print_P(PSTR("XBEE: Buffer overflow!\n"));
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
        }

        if ( c == '\r' ) { // Ready!        
            this->stateReciever = XBeeProS2CStateReciever::PROCESSING;
        }
        break;

    case XBeeProS2CStateReciever::PROCESSING: // Help, the previous data has not been processed yet!
        {
            Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();
            s->print_P(PSTR("Recieved character while it has not bee processed yet!\n"));
        }
        break;

    }

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
