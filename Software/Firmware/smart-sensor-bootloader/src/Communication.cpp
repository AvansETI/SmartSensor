// class for handling Serial communication
// currently hardcoded for port 0, will fix when going over Serial

#include <Communication.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// char receivedChars[128];
// int charpos;

// method to handle the recieving of chars, received chars are added to array and can be retrieved to be handled
// Interrupt appears to be necessary for funtion even when empty
// ISR(USART0_RX_vect)
// {
//     // char c = UDR0;
//     // receivedChars[charpos] = c;
//     // charpos++;

//     // test for checking if function worked
//     //  sendChar(c);
// }

// method for initializing the serial connection
// TODO: Remove reliance on hardcoded data
void initSerial()
{
    uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600 - 1;
    // uint32_t ubrr = ((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char)(ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1 << RXEN) | (1 << TXEN);   // Enable TX and RX and recieve interrupt
    UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
    sei();

    // for (int i = 0; i < 128; i++)
    // {
    //     receivedChars[i] = 'Z';
    // }

    // charpos = 0;
}

// method for sending individual chars, if more chars are required use sendstring instead
void sendChar(char c)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = c;
}

// method for sending multiple chars
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

// // method for retrieving received chars, Z should mean empty
// char *getreceived()
// {
//     // char *retrieval;

//     // for (int i = 0; i < 128; i++)
//     // {
//     //     retrieval[i] = receivedChars[i];
//     //     receivedChars[i] = 'Z';
//     // }
//     // charpos = 0;

//     return receivedChars;
// }

// // dirty fix, feels like this should be able to be done better
// void resetArray()
// {
//     for (int i = 0; i < 128; i++)
//     {
//         receivedChars[i] = 'Z';
//     }
//     charpos = 0;
// }

// method to check if there is a char recieved
bool isCharReceived()
{
    return UCSR0A & (1 << RXC);
}

// method to read a char
char readChar()
{
    return UDR0;
}

// method for checking if the line is valid
// Line structure should be for 1 line [:][00][0000][00][DATA][00][\n]
// representing [start of record][number of bytes][starting address][type][the actual data][checksum][end of line]
bool isValidLine(char *line)
{
    //check if the first character is a :
    if (line[0] == ':')
    {
        
    } else {
        //error with line, please resend
        sendChar('W');
        return false;
    }

    // for now dirty to check
    for (int i = 0; i < 50; i++)
    {
        if (line[i] == '\n')
        {
            return true;
        }
    }

    return false;
}

// method for reading a line, input: Array, int for the timeout in 100ms and int for the length of the array
bool readLine(char *line, uint8_t timeout, uint8_t length)
{
    uint8_t linepos = 0;

    for (uint8_t i = 0; i < timeout; i++)
    {
        if (isCharReceived())
        {
            char c = readChar();
            line[linepos] = c;
            line[linepos + 1] = '\0';
            linepos++;
            if (c == '\n')
            {
                return true;
            }
        }
        else
        {
            _delay_ms(100);
        }

        // because of length issues, when end is reached end the method, -1 is there so there is still a NULL character terminating the array
        if (linepos >= (length - 1))
        {
            return true;
        }
    }
    //timeout error, W is sent here because it is not a general timeout error but specifically one within writing
    sendChar('W');
    return false;
}