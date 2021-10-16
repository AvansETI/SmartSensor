#include <tasks/Atmega324PBSerial0.h>

#include <string.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

uint8_t Atmega324PBSerial0::setup() {
    uint32_t baudrate = 9600;
    uint16_t ubrr = ((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char) ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1<<RXEN)|(1<<TXEN); // Enable TX and RX
    UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop

    return 0;
}

uint8_t Atmega324PBSerial0::loop(uint32_t millis) {
    if ( this->busy ) { // Yes we can try to send the next character!
        if ( UCSR0A & (1<<UDRE) )  { // If the transmit buffer is empty, we can send the next character
            if ( this->buffer[this->pointer] != '\0' ) { 
                UDR0 = this->buffer[this->pointer]; // send the byte!
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
