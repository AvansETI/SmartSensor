#include <util/delay.h>

#include "unittest_transport.h"

void unittest_uart_begin() {
    _delay_ms(500);
}

void unittest_uart_putchar(char c) {
    //Usart0.transmitChar(c);
}

void unittest_uart_flush() {
    //Usart0.flush();
}

void unittest_uart_end() {
    // TODO: End stuffs
}
