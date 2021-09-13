#include <util/Serial0.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

uint8_t Serial0::setup() {
    uint32_t baudrate = 9600;
    uint16_t ubrr = ((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char) ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1<<RXEN)|(1<<TXEN); // Enable TX and RX
    UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop

    return 0;
}

uint8_t Serial0::print(const char* message) {
    while (*message) {
        this->transmitChar(*message++);
    }

    return 0;
}

uint8_t Serial0::print_P(const char* message) {
     while(pgm_read_byte(message) != 0x00) {
       this->transmitChar(pgm_read_byte(message++));
     }

    return 0;
}

void Serial0::transmitChar(char data) {
    while ( !( UCSR0A & (1<<UDRE)) ); // Wait for empty transmit buffer
    UDR0 = data;
}
