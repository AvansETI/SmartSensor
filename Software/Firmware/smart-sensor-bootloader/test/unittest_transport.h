#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

void unittest_uart_begin();
void unittest_uart_putchar(char c);
void unittest_uart_flush();
void unittest_uart_end();

#endif // UNITTEST_TRANSPORT_H