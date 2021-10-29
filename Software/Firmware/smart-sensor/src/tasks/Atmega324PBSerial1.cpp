/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <tasks/Atmega324PBSerial1.h>
#include <tasks/Atmega324PBSerial0.h>

#include <string.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <avr/interrupt.h>

static SerialRecievedCharacter* cbAtmega324PBSerial1 = NULL;

//static char buffer[50];
//static uint16_t length;
//static uint8_t state = 0;
//static uint16_t counter = 0;

/* When a character is received on the serial bus, this interrupt is called. */
ISR(USART1_RX_vect) {
    char c = UDR1;
/*
    switch (state) {
    case 1:// length H
        length = c << 8;
        state = 2;
        break;
    case 2: // length L
        length = length | c;
        counter = 0;
        state = 3;
        break;
    case 3: // data!
        if ( length == counter ) { // ready
            buffer[counter] = c;
            state = 0;
            for (uint8_t i=0; i <= length; i++ ) {
                uint8_t h2 = (buffer[i] & 0b11110000) >>4;
                uint8_t h1 = buffer[i] & 0b00001111;
                Atmega324PBSerial0::getInstance()->transmitChar((h2 < 10 ? h2+'0' : h2-10+'A'));
                Atmega324PBSerial0::getInstance()->transmitChar((h1 < 10 ? h1+'0' : h1-10+'A'));
                Atmega324PBSerial0::getInstance()->transmitChar(' ');

            }
            Atmega324PBSerial0::getInstance()->transmitChar('\n');

        } else { // read frame
            buffer[counter] = c;
            counter++;
        }
        break;
    }

    if ( state == 0 && c == 0x7E ) {
        state = 1;

    } else {*/
        if ( cbAtmega324PBSerial1 != NULL ) {
            cbAtmega324PBSerial1->recievedCharacter(c);
        }
    //}
}

void Atmega324PBSerial1::setCallback( SerialRecievedCharacter* callback ) {
    cbAtmega324PBSerial1 = callback;
}

uint8_t Atmega324PBSerial1::setup() {
    //#define FOSC 1843200 // Clock Speed
    //#define BAUD 9600
    //#define MYUBRR FOSC/16/BAUD-1

    uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600-1;//((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR1H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR1L = (unsigned char) ubrr;
    UCSR1A = 0x00;
    UCSR1B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // Enable TX and RX and recieve interrupt
    UCSR1C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop

    return 0;
}

uint8_t Atmega324PBSerial1::loop(uint32_t millis) {
    if ( this->busy ) { // If busy is true, we are sending characters
        if ( UCSR1A & (1<<UDRE) )  { // Check if the transmit buffer is empty, before sending the next character
            if ( this->buffer[this->pointer] != '\0' ) { 
                UDR1 = this->buffer[this->pointer]; // Send the character
                this->pointer++;
            
            } else {
                this->busy = false;
                this->pointer = 0;
            }
        }
    }

    return 0;
}

uint8_t Atmega324PBSerial1::reset() {
    this->pointer = 0;
    this->busy    = false;
    return 0;
}

uint8_t Atmega324PBSerial1::sleep() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

uint8_t Atmega324PBSerial1::wakeup() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

uint8_t Atmega324PBSerial1::print(const char* message) {
    if ( !this->busy ) {
        while (*message) {
            this->transmitChar(*message++);
        }
        return 0;
    }

    return 1; // Serial port is busy
}

uint8_t Atmega324PBSerial1::print_P(const char* message) {
    if ( !this->busy ) {
        while(pgm_read_byte(message) != 0x00) {
        this->transmitChar(pgm_read_byte(message++));
        }

        return 0;
    }

    return 1; // Serial port is busy
}

uint8_t Atmega324PBSerial1::printAsync(const char* message) {
    if ( !this->busy ) {
        strcpy(this->buffer, message);
        this->busy = true;
        this->pointer = 0;

        return 0;
    }

    return 1;
}

uint8_t Atmega324PBSerial1::printAsync_P(const char* message) {
    if ( !this->busy ) {
        strcpy_P(this->buffer, message);
        this->busy = true;
        this->pointer = 0;

        return 0;
    }

    return 1;
}

void Atmega324PBSerial1::transmitChar(char data) {
    while ( !( UCSR1A & (1<<UDRE)) ); // Wait for empty transmit buffer
    UDR1 = data;
}

uint8_t Atmega324PBSerial1::isBusy() {
    return this->busy;
}

bool Atmega324PBSerial1::isCharacterReceieved() {
    return UCSR1A & (1<<RXC);
}

char Atmega324PBSerial1::readCharacter() {
    return UDR1;
}
