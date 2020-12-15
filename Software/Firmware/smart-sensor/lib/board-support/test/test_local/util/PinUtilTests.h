#ifndef PUTIL_TESTS_H_
#define PUTIL_TESTS_H_

#include <unity.h>
#include <board-support/util/PinUtil.h>

namespace test_util_PinUtil {
    void test_PinUtil_get_pin_address() {
        PinPort pina0 = PinPortA0;
        PinPort pinb5 = PinPortB5;
        PinPort pinc2 = PinPortC2;
        PinPort pind4 = PinPortD4;
        PinPort pine6 = PinPortE6;

        PINA |= 0b10001u;
        PINB |= 0b01010u;
        PINC |= 0b10101u;
        PIND |= 0b01010u;
        PINE |= 0b10110u;

        TEST_ASSERT_EQUAL(PINA, PinUtil::get_pin_address(pina0));
        TEST_ASSERT_EQUAL(PINB, PinUtil::get_pin_address(pinb5));
        TEST_ASSERT_EQUAL(PINC, PinUtil::get_pin_address(pinc2));
        TEST_ASSERT_EQUAL(PIND, PinUtil::get_pin_address(pind4));
        TEST_ASSERT_EQUAL(PINE, PinUtil::get_pin_address(pine6));
    }

    void test_PinUtil_get_port_address() {
        PinPort porta0 = PinPortA0;
        PinPort portb5 = PinPortB5;
        PinPort portc2 = PinPortC2;
        PinPort portd4 = PinPortD4;
        PinPort porte6 = PinPortE6;


        PORTA |= 0b11011u;
        PORTB |= 0b01110u;
        PORTC |= 0b10011u;
        PORTD |= 0b11000u;
        PORTE |= 0b00111u;
        
        TEST_ASSERT_EQUAL(PORTA, PinUtil::get_port_address(porta0));
        TEST_ASSERT_EQUAL(PORTB, PinUtil::get_port_address(portb5));
        TEST_ASSERT_EQUAL(PORTC, PinUtil::get_port_address(portc2));
        TEST_ASSERT_EQUAL(PORTD, PinUtil::get_port_address(portd4));
        TEST_ASSERT_EQUAL(PORTE, PinUtil::get_port_address(porte6));
    }

    void test_PinUtil_get_ddr_address() {
        PinPort porta0 = PinPortA0;
        PinPort pina0 = PinPortA0;
        DDR ddra = DDR::DA;

        PinPort portb1 = PinPortB1;
        PinPort pinb1 = PinPortB1;
        DDR ddrb = DDR::DB;
        
        PinPort portc3 = PinPortC3;
        PinPort pinc3 = PinPortC3;
        DDR ddrc = DDR::DC;
        
        PinPort portd6 = PinPortD6;
        PinPort pind6 = PinPortD6;
        DDR ddrd = DDR::DD;

        PinPort porte2 = PinPortE2;
        PinPort pine2 = PinPortE2;
        DDR ddre = DDR::DE;
        
        DDRA |= 0b10101u;
        DDRB |= 0b10001u;
        DDRC |= 0b11100u;
        DDRD |= 0b00111u;
        DDRE |= 0b11111u;

        TEST_ASSERT_EQUAL(DDRA, PinUtil::get_ddr_address(porta0));
        TEST_ASSERT_EQUAL(DDRA, PinUtil::get_ddr_address(pina0));
        TEST_ASSERT_EQUAL(DDRA, PinUtil::get_ddr_address(ddra));

        TEST_ASSERT_EQUAL(DDRB, PinUtil::get_ddr_address(portb1));
        TEST_ASSERT_EQUAL(DDRB, PinUtil::get_ddr_address(pinb1));
        TEST_ASSERT_EQUAL(DDRB, PinUtil::get_ddr_address(ddrb));

        TEST_ASSERT_EQUAL(DDRC, PinUtil::get_ddr_address(portc3));
        TEST_ASSERT_EQUAL(DDRC, PinUtil::get_ddr_address(pinc3));
        TEST_ASSERT_EQUAL(DDRC, PinUtil::get_ddr_address(ddrc));

        TEST_ASSERT_EQUAL(DDRD, PinUtil::get_ddr_address(portd6));
        TEST_ASSERT_EQUAL(DDRD, PinUtil::get_ddr_address(pind6));
        TEST_ASSERT_EQUAL(DDRD, PinUtil::get_ddr_address(ddrd));

        TEST_ASSERT_EQUAL(DDRE, PinUtil::get_ddr_address(porte2));
        TEST_ASSERT_EQUAL(DDRE, PinUtil::get_ddr_address(pine2));
        TEST_ASSERT_EQUAL(DDRE, PinUtil::get_ddr_address(ddre));
    }

    void test_PinUtil_get_letter_index() {
        PinPort porta0 = PinPortA0;
        PinPort portb2 = PinPortB2;
        PinPort porte6 = PinPortE6;

        PinPort pina0 = PinPortA0;
        PinPort pinc4 = PinPortC4;
        PinPort pine6 = PinPortE6;

        TEST_ASSERT_EQUAL(0, PinUtil::get_letter_index(porta0));
        TEST_ASSERT_EQUAL(1, PinUtil::get_letter_index(portb2));
        TEST_ASSERT_EQUAL(4, PinUtil::get_letter_index(porte6));

        TEST_ASSERT_EQUAL(0, PinUtil::get_letter_index(pina0));
        TEST_ASSERT_EQUAL(2, PinUtil::get_letter_index(pinc4));
        TEST_ASSERT_EQUAL(4, PinUtil::get_letter_index(pine6));
    }

    void test_PinUtil_get_number() {
        PinPort porta0 = PinPortA0;
        PinPort portb2 = PinPortB2;
        PinPort porte6 = PinPortE6;

        PinPort pina0 = PinPortA0;
        PinPort pinc4 = PinPortC4;
        PinPort pine6 = PinPortE6;

        TEST_ASSERT_EQUAL(0, PinUtil::get_number(porta0));
        TEST_ASSERT_EQUAL(2, PinUtil::get_number(portb2));
        TEST_ASSERT_EQUAL(6, PinUtil::get_number(porte6));

        TEST_ASSERT_EQUAL(0, PinUtil::get_number(pina0));
        TEST_ASSERT_EQUAL(4, PinUtil::get_number(pinc4));
        TEST_ASSERT_EQUAL(6, PinUtil::get_number(pine6));
    }

    void test_PinUtil_pin_port_letter_check() {
        PinPort porta0 = PinPortA0;
        PinPort portb2 = PinPortB2;
        PinPort porte6 = PinPortE6;

        TEST_ASSERT_EQUAL(true, PinUtil::pin_port_letter_check(PinPortA, porta0));
        TEST_ASSERT_EQUAL(true, PinUtil::pin_port_letter_check(PinPortB, portb2));
        TEST_ASSERT_EQUAL(true, PinUtil::pin_port_letter_check(PinPortE, porte6));
        TEST_ASSERT_EQUAL(false, PinUtil::pin_port_letter_check(PinPortB, porta0));
        TEST_ASSERT_EQUAL(false, PinUtil::pin_port_letter_check(PinPortA, portb2));
        TEST_ASSERT_EQUAL(false, PinUtil::pin_port_letter_check(PinPortC, porte6));
    }

    void run() {
        RUN_TEST(test_PinUtil_get_pin_address);
        RUN_TEST(test_PinUtil_get_port_address);
        RUN_TEST(test_PinUtil_get_ddr_address);
        RUN_TEST(test_PinUtil_get_letter_index);
        RUN_TEST(test_PinUtil_get_number);
        RUN_TEST(test_PinUtil_pin_port_letter_check);
    }
}

#endif