// class for handling Serial communication
// currently hardcoded for port 0, will fix when going over Serial

#include <Communication.h>
#include <avr/interrupt.h>
#include <avr/io.h>

char recievedChars[128];
int charpos;

//method to handle the recieving of chars, recieved chars are added to array and can be retrieved to be handled
ISR(USART0_RX_vect) {
    char c = UDR0;
    recievedChars[charpos] = c;
    charpos++;



    //test for checking if function worked
    // sendChar(c);
}

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

    for (int i = 0; i < 128; i++)
    {
        recievedChars[i] = 'Z';
    }
    

    charpos = 0;
}

void sendChar(char c)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = c;
}

void sendString(const char *input)
{
    // for (int i = 0; i < sizeof(input); i++)
    // {
    //     sendChar(input[i]);
    // }
    while (*input != 0x00)
    {
        sendChar(*input++);
    }   
}

//method for retrieving recieved chars, Z should mean empty
char* getRecieved() {
    // char *retrieval;
    
    // for (int i = 0; i < 128; i++)
    // {
    //     retrieval[i] = recievedChars[i];
    //     recievedChars[i] = 'Z';
    // }
    // charpos = 0;
    
    return recievedChars;
}

//dirty fix, feels like this should be able to be done better
void resetArray() {
    for (int i = 0; i < 128; i++)
    {
        recievedChars[i] = 'Z';
    }
    charpos = 0;
}