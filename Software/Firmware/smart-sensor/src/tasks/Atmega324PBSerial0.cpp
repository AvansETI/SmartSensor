/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <tasks/Atmega324PBSerial0.h>

#include <string.h>

#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

static SerialRecievedCharacter* cbAtmega324PBSerial0 = NULL;

ISR(USART0_RX_vect) {
    char c = UDR0;
    if ( cbAtmega324PBSerial0 != NULL ) {
        cbAtmega324PBSerial0->recievedCharacter(c);
    }
}

void Atmega324PBSerial0::setCallback( SerialRecievedCharacter* callback ) {
    cbAtmega324PBSerial0 = callback;
}

uint8_t Atmega324PBSerial0::setup() {
    //uint32_t baudrate = 9600;
    //uint16_t ubrr = ((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL));

    uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600-1;//((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char) ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // Enable TX and RX and recieve interrupt
    UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop

    return 0;
}

uint8_t Atmega324PBSerial0::loop(uint32_t millis) {
    if ( this->busy ) { // If busy is true, we are sending characters
        if ( UCSR0A & (1<<UDRE) )  { // Check if the transmit buffer is empty, before sending the next character
            if ( this->buffer[this->pointer] != '\0' ) { 
                UDR0 = this->buffer[this->pointer]; // Send the character
                this->pointer++;
            
            } else {
                this->busy = false;
                this->pointer = 0;
            }
        }
    }

    return 0;
}

uint8_t Atmega324PBSerial0::reset() {
    this->pointer = 0;
    this->busy    = false;
    return 0;
}

uint8_t Atmega324PBSerial0::sleep() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

uint8_t Atmega324PBSerial0::wakeup() {
    // Is not implemented while this hardware cannot sleep.
    return 0;
}

uint8_t Atmega324PBSerial0::print(const char* message) {
    if ( !this->busy ) {
        while (*message) {
            this->transmitChar(*message++);
        }
        return 0;
    }

    return 1; // Serial port is busy
}

uint8_t Atmega324PBSerial0::print_P(const char* message) {
    if ( !this->busy ) {
        while(pgm_read_byte(message) != 0x00) {
        this->transmitChar(pgm_read_byte(message++));
        }

        return 0;
    }

    return 1; // Serial port is busy
}

uint8_t Atmega324PBSerial0::printAsync(const char* message) {
    if ( !this->busy ) {
        strcpy(this->buffer, message);
        this->busy = true;
        this->pointer = 0;

        return 0;
    }

    return 1;
}

uint8_t Atmega324PBSerial0::printAsync_P(const char* message) {
    if ( !this->busy ) {
        strcpy_P(this->buffer, message);
        this->busy = true;
        this->pointer = 0;

        return 0;
    }

    return 1;
}

void Atmega324PBSerial0::transmitChar(char data) {
    while ( !( UCSR0A & (1<<UDRE)) ); // Wait for empty transmit buffer
    UDR0 = data;
}

uint8_t Atmega324PBSerial0::isBusy() {
    return this->busy;
}

bool Atmega324PBSerial0::isCharacterReceieved() {
    return UCSR1A & (1<<RXC);
}

char Atmega324PBSerial0::readCharacter() {
    return UDR1;
}

bool Atmega324PBSerial0::readLine(char* line, uint8_t timeout, uint8_t length) {
    uint8_t counter = 0;
    uint8_t index   = 0;
    
    for (uint8_t i=0; i < timeout; ++i) {
        if ( this->isCharacterReceieved() ) {
            char c = this->readCharacter();
            this->transmitChar(c);
            if ( c == '\n' ) return true;
            line[index] = c;
            line[index+1] = '\0';
            index++;
            
        } else {
            _delay_ms(100);
        }

        if ( index >= length - 1 ) {
            return true;
        }
    }

    return false;
}