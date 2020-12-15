#ifndef SERIALDRIVER_TESTS_H_
#define SERIALDRIVER_TESTS_H_

#include <board-support/drivers/UsartDriver.h>

namespace test_drivers_UsartDriver {

    void test_UsartDriver_init() {
        TEST_ASSERT_EQUAL((1<<RXEN)|(1<<TXEN), UCSR0B);
        TEST_ASSERT_EQUAL((1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1), UCSR0C);
    }

    void test_UsartDriver_transmit() {
        Usart0.transmitChar('5');
        TEST_ASSERT_EQUAL('5', UDR0);

    }

    void test_UsartDriver_receive() {
        Usart0.transmitChar('5');
        unsigned char data;
        data = Usart0.receiveChar();
        TEST_ASSERT_EQUAL('5', data);

    }

    void test_UsartDriver_flush() {
        Usart0.flush();
        TEST_ASSERT_EQUAL(0, UCSR0A);
    }

    void run() {
        RUN_TEST(test_UsartDriver_init);
//        RUN_TEST(test_UsartDriver_transmit);
//        RUN_TEST(test_UsartDriver_receive);
        RUN_TEST(test_UsartDriver_flush);
    }

}
#endif