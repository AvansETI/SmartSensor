#include <util/Serial0.h>

#include <avr/io.h>

uint8_t Serial0::setup() {
    UBRR0H = (unsigned char)((SERIAL0_UBRR) >> 8); // Set baud rate!
    UBRR0L = (unsigned char)SERIAL0_UBRR;
    UCSR0B = (1<<RXEN)|(1<<TXEN); // Enable TX and RX
    UCSR0C = (3<<UCSZ0); // 8 data and 1 stop

    return 0;
}

uint8_t Serial0::print(const char* message) {
    while (*message) {
        this->transmitChar(*message++);
    }

    return 0;
}

void Serial0::transmitChar(char data) {
    while ( !( UCSR0A & (1<<UDRE)) ); // Wait for empty transmit buffer
    UDR0 = data;
}
