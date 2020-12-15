#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_

#include <boardsupport.h>

class UsartDriver {

	public:
        enum Mode { ReadWrite = 0, Read = 1, Write = 2 };
        enum Instance { USART0, USART1, USART2 };
        enum NumberRadix { BINARY = 2u, DECIMAL = 10, HEX = 16u };

        /**
         * Initialize UsartDriver
         * @param instance which usart instance to use
         */
        UsartDriver(Instance instance);

        /**
        * Transmits a char through the USART interface.
        * @param data the ASCII value of the char to be transmitted
        */
        void transmitChar(unsigned char data);

        /**
         * Transmits a max of 10digit decimal number through the USART interface.
         * The output for the input combinations is as below
         *
         *  Binary:     1.(10,4) then 4-LSB will be transmitted ie. 1010
         *              2.(10,8) then 8-LSB will be transmitted ie. 00001010
         *              3.(10,2) then 2-LSB will be transmitted ie. 10
         *
         *  Decimal
         *              4.(12345,4) then 4-digits ie. 2345 will be transmitted
         *              5.(12345,6) then 6-digits ie. 012345 will be transmitted
         *              6.(12345) then 12345 will be transmitted.
         *
         *  Hex:
         *              7.(0x12AB,3) then 3-digits ie. 2AB will be transmitted
         *              8.(0x12AB,6) then 6-digits ie. 0012AB will be transmitted
         *              9.(0x12AB) then 12AB will be transmitted.
         *
         *
         * @param radix             specifies the number radix
         * @param number            number to be transmitted over USART
         * @param numberOfDigits    number of digits to be transmitted
         */
        void transmitNumber(NumberRadix radix, uint32_t number, uint8_t numberOfDigits = 10u);

        /**
         * Transmits a floating point number over the USART interface.
         * @param number number to be trasmitted over USART
         */
        void transmitFloat(float number);

        /**
        * Receiving with 5-8 bit data from Data Register that you specified in the init
        * UBRR0H/L uses UDR0
        * @return the data from the register
        */
        unsigned char receiveChar();

        /**
         * Flushes the USART buffer
         */
        void flush();
    private:
        Instance m_instance;

        /**
         * Initializing all of the register for USART.
         * This must be ran first before you are able to use the other functions.
         * In the file
         * @param baudrate the baudrate
         * @param mode     the mode to use
         */
        void init(uint32_t baudrate, Mode mode);

        /**
         * Converts {@link Mode} to the proper register value
         * @param mode the mode to convert
         * @return binary value with the {@link RXEN} and/or {@link TXEN} bits enabled
         */
        uint8_t mode_to_register(Mode mode);
};

#if USART0_ENABLED
static UsartDriver Usart0 = UsartDriver(UsartDriver::USART0);
#endif

#if USART1_ENABLED
static UsartDriver Usart1 = UsartDriver(UsartDriver::USART1);
#endif

#if USART2_ENABLED
static UsartDriver Usart2 = UsartDriver(UsartDriver::USART2);
#endif

#endif