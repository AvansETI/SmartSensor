// class for handling Serial communication
// currently hardcoded for port 0, will fix when going over Serial

#include <Communication.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Converter.h>


bool isEnd = false;

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
    UCSR0B = (1 << RXEN) | (1 << TXEN);                  // Enable TX and RX
    UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
    sei();
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

bool isDone() {
    return isEnd;
}

// method for checking if the line is valid
// Line structure should be for 1 line [:][00][0000][00][DATA][00][\n]
// representing [start of record][number of bytes][starting address][type][the actual data][checksum][end of line]
// TODO: Check the checksum
bool isValidLine(char *line, uint8_t *data, uint16_t *address, uint8_t *bytesInData)
{
    // check if the first character is a :
    if (line[0] == ':')
    {
        // check the amount of bytes and store to check later
        uint8_t byteAmount = convertHexToByte(line[1], line[2]);
        // check address
        // TODO: Get address back to write
        uint16_t addressCheck = ((uint16_t)convertHexToByte(line[3], line[4]) << 8) + (uint16_t)convertHexToByte(line[5], line[6]);
        // check if its data
        if (line[7] == '0' && line[8] == '0')
        {
            // add the data to the array
            int b = 9;
            for (int i = 0; i < byteAmount; i++)
            {
                data[i] = convertHexToByte(line[b], line[b + 1]);
                b = b + 2;
            }

            if (line[b + 2] == '\n')
            {
                *address = addressCheck;
                *bytesInData = byteAmount;
                return true;
            }
        //it can also be this, in which case it is the last line
        } 
        else if (line[7] == '0' && line[8] == '1')
        {
            //For now just say you're finished with it
            //TODO: Get version to go to write state
            // sendChar('X');
            isEnd = true;
            return false;
        }
        
    }
    else
    {
        // error with line, please resend
        sendChar('W');
        return false;
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
    // timeout error, W is sent here because it is not a general timeout error but specifically one within writing
    sendChar('W');
    return false;
}