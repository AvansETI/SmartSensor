#include "board-support/drivers/UsartDriver.h"

UsartDriver::UsartDriver(Instance instance) {
    m_instance = instance;

    switch (m_instance) {
        case USART0:
            init(USART0_BAUD_RATE, Mode(USART0_TX_RX));
            break;
        case USART1:
            init(USART1_BAUD_RATE, Mode(USART1_TX_RX));
            break;
        case USART2:
            init(USART2_BAUD_RATE, Mode(USART2_TX_RX));
            break;
    }
}

void UsartDriver::init(uint32_t baudrate, Mode mode) {
    uint16_t ubrr = ((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL));

    switch (m_instance) {
        case USART0:
            UBRR0H = (unsigned char) (ubrr >> 8); // This will be 0
            UBRR0L = (unsigned char) ubrr; // This will be whatever comes out of the macro in the default config it will be 11

            UCSR0A = 0x00;
            UCSR0B = mode_to_register(mode);
            UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1);
            break;

        case USART1:
            UBRR1H = (unsigned char) (ubrr >> 8); // This will be 0
            UBRR1L = (unsigned char) ubrr; // This will be whatever comes out of the macro in the default config it will be 11

            UCSR1A = 0x00;
            UCSR1B = mode_to_register(mode);
            UCSR1C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1);
            break;

        case USART2:
            UBRR2H = (unsigned char) (ubrr >> 8); // This will be 0
            UBRR2L = (unsigned char) ubrr; // This will be whatever comes out of the macro in the default config it will be 11

            UCSR2A = 0x00;
            UCSR2B = mode_to_register(mode);
            UCSR2C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1);
            break;
    }
}


void UsartDriver::transmitChar(unsigned char data) {
    switch (m_instance) {
        case USART0:
            /* Wait for empty transmitChar buffer */
            while ( !( UCSR0A & (1<<UDRE)) );

            /* Put data into buffer, sends the data */
            UDR0 = data;
            break;
        case USART1:
            /* Wait for empty transmitChar buffer */
            while ( !( UCSR1A & (1<<UDRE)) );

            /* Put data into buffer, sends the data */
            UDR1 = data;
            break;

        case USART2:
            /* Wait for empty transmitChar buffer */
            while ( !( UCSR2A & (1<<UDRE)) );

            /* Put data into buffer, sends the data */
            UDR2 = data;
            break;
    }
}

void UsartDriver::transmitNumber(UsartDriver::NumberRadix radix, uint32_t number, uint8_t numberOfDigits) {
    uint8_t i=0,a[10];

    if(NumberRadix::BINARY == radix)
    {
        while(numberOfDigits != 0)
        {
            /* Start Extracting the bits from the specified bit positions.
             Get the Acsii values of the bits and transmit */
            i = util_GetBitStatus(number,(numberOfDigits-1));
            transmitChar(util_Dec2Ascii(i));
            numberOfDigits--;
        }
    }
    else if(number == 0)
    {
        /* If the number is zero then update the array with the same for transmitting */
        for(i = 0; i < numberOfDigits && i < 10u; i++)
            transmitChar('0');
    }
    else
    {
        for(i = 0; i < numberOfDigits; i++)
        {
            /* Continue extracting the digits from right side
               till the Specified v_numOfDigitsToTransmit_u8 */
            if(number != 0)
            {
                /* Extract the digits from the number till it becomes zero.
                First get the remainder and divide the number by 10 each time.

                example for Decimal number:
                If v_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
                The process continues till it becomes zero or max digits reached*/
                a[i] = util_GetMod32(number, radix);
                number = number / radix;
            }
            else if(numberOfDigits > 10u)
            {
                /* Stop the iteration if the Max number of digits are reached or
                 the user expects exact(Default) digits in the number to be transmitted */
                break;
            }
            else
            {
                /*In case user expects more digits to be transmitted than the actual digits in number,
                  then update the remaining digits with zero.
                Ex: v_number_u32 is 123 and user wants five digits then 00123 has to be transmitted */
                a[i]=0;
            }
        }

        while(i)
        {
            /* Finally get the ascii values of the digits and transmit*/
            transmitChar(util_Hex2Ascii(a[i-1]));
            i--;
        }
    }
}

void UsartDriver::transmitFloat(float number) {
    uint32_t tempNumber = (uint32_t) number;
    transmitNumber(NumberRadix::DECIMAL, tempNumber, 0xffu);

    transmitChar('.');

    number = number - tempNumber;
    tempNumber = number * 1000000;
    transmitNumber(NumberRadix::DECIMAL, tempNumber, 0xffu);
}

unsigned char UsartDriver::receiveChar() {
    switch (m_instance) {
        case USART0:
            /* Wait for data to be received */
            while ( !(UCSR0A & (1<<RXC)) );

            /* Get and return received data from buffer */
            return UDR0;
        case USART1:
            /* Wait for data to be received */
            while ( !(UCSR1A & (1<<RXC)) );

            /* Get and return received data from buffer */
            return UDR1;

        case USART2:
            /* Wait for data to be received */
            while ( !(UCSR2A & (1<<RXC)) );

            /* Get and return received data from buffer */
            return UDR2;
    }

    return 0;
}

void UsartDriver::flush() {
    switch (m_instance) {
        case USART0:
            while (UCSR0A & (1 <<RXC));
            break;
        case USART1:
            while (UCSR1A & (1 <<RXC));
            break;
        case USART2:
            while (UCSR2A & (1 <<RXC));
            break;
    }
}

uint8_t UsartDriver::mode_to_register(UsartDriver::Mode mode) {
    switch (mode) {
        case ReadWrite:
            return (1u << RXEN) | (1u << TXEN);
        case Read:
            return (1u << RXEN);
        case Write:
            return (1u << TXEN);
    }
    return 0;
}