#include "unittest_transport.h"
#include "board-support/drivers/UsartDriver.h"

void unittest_uart_begin() {

}

void unittest_uart_putchar(char c) {
    Usart0.transmitChar(c);
}

void unittest_uart_flush() {
    Usart0.flush();
}

void unittest_uart_end() {
    // TODO: End stuffs
}
