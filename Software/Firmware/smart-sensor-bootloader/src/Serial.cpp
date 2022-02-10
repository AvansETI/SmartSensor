// class for handling Serial communication
// currently hardcoded for port 0, will fix when going over Serial

#include <Serial.h>
#include <avr/interrupt.h>

void initSerial()
{
    uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600 - 1;
    // uint32_t ubrr = ((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char)(ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);   // Enable TX and RX and recieve interrupt
    UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
    sei();
}

void sendChar(unsigned char c)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = c;
}

void sendString(unsigned char input[])
{
    for (int i = 0; i < sizeof(input); i++)
    {
        sendChar(input[i]);
    }
    
}