#ifndef PINMANAGER_TESTS_H_
#define PINMANAGER_TESTS_H_

#include <unity.h>
#include <unity_internals.h>
#include "board-support/util/PinManager.h"

namespace test_util_PinManager {

    void test_PinManager_init_adc() {
        PinManager::analog_read(PinPortA0);
        
        // Check if registers are set correctly:
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, ADMUX & (1u << REFS1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, ADCSRA & (1u << ADEN));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, ADCSRA & (1u << ADPS2));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, ADCSRA & (1u << ADPS1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, ADCSRA & (1u << ADPS0));
    }

    void test_PinManager_set_mode() {
        DDRC = 0x00;
        DDRD = 0x00;

        PinPort test_pin_c2 = PinPortC2;
        PinPort test_pin_c3 = PinPortC3;
        PinPort test_pin_c4 = PinPortC4;
        PinPort test_port_d2 = PinPortD2;
        PinPort test_port_d3 = PinPortD3;
        PinPort test_port_d4 = PinPortD4;

        PinManager::set_mode(test_pin_c2, OUTPUT);
        PinManager::set_mode(test_pin_c3, INPUT);
        PinManager::set_mode(test_port_d2, OUTPUT);
        PinManager::set_mode(test_port_d3, INPUT);

        TEST_ASSERT_GREATER_OR_EQUAL(OUTPUT, PinUtil::get_ddr_address(test_pin_c2) & (1u << PinUtil::get_number(
                test_pin_c2)));
        TEST_ASSERT_EQUAL(INPUT, PinUtil::get_ddr_address(test_pin_c3) & (1u << PinUtil::get_number(
                test_pin_c3)));
        TEST_ASSERT_EQUAL(INPUT, PinUtil::get_ddr_address(test_pin_c4) & (1u << PinUtil::get_number(
                test_pin_c4)));

        TEST_ASSERT_GREATER_OR_EQUAL(OUTPUT, PinUtil::get_ddr_address(test_port_d2) & (1u << PinUtil::get_number(test_port_d2)));
        TEST_ASSERT_EQUAL(INPUT, PinUtil::get_ddr_address(test_port_d3) & (1u << PinUtil::get_number(test_port_d3)));
        TEST_ASSERT_EQUAL(INPUT, PinUtil::get_ddr_address(test_port_d4) & (1u << PinUtil::get_number(test_port_d4)));
    }

    void test_PinManager_digital_write() {
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        PinPort test_port_a0 = PinPortA0;
        PinPort test_port_a1 = PinPortA1;
        PinPort test_port_b2 = PinPortB2;
        PinPort test_port_b3 = PinPortB3;
        PinPort test_port_c4 = PinPortC4;
        PinPort test_port_c5 = PinPortC5;

        PinManager::digital_write(test_port_a0, DigitalValues::LOW);
        PinManager::digital_write(test_port_a1, DigitalValues::HIGH);
        PinManager::digital_write(test_port_b2, DigitalValues::LOW);
        PinManager::digital_write(test_port_b3, DigitalValues::HIGH);
        PinManager::digital_write(test_port_c4, DigitalValues::LOW);
        PinManager::digital_write(test_port_c5, DigitalValues::HIGH);

        TEST_ASSERT_GREATER_OR_EQUAL(1, PinUtil::get_port_address(test_port_a0) & (1u << PinUtil::get_number(test_port_a0)));
        TEST_ASSERT_EQUAL(0, PinUtil::get_port_address(test_port_a1) & (1u << PinUtil::get_number(test_port_a1)));
        TEST_ASSERT_GREATER_OR_EQUAL(1, PinUtil::get_port_address(test_port_b2) & (1u << PinUtil::get_number(test_port_b2)));
        TEST_ASSERT_EQUAL(0, PinUtil::get_port_address(test_port_b3) & (1u << PinUtil::get_number(test_port_b3)));
        TEST_ASSERT_GREATER_OR_EQUAL(1, PinUtil::get_port_address(test_port_c4) & (1u << PinUtil::get_number(test_port_c4)));
        TEST_ASSERT_EQUAL(0, PinUtil::get_port_address(test_port_c5) & (1u << PinUtil::get_number(test_port_c5)));
    }

    void test_PinManager_digital_read() {
        PINC = 0x00;

        PinPort test_pin_c2 = PinPortC2;
        PinPort test_pin_c3 = PinPortC3;
        PinPort test_pin_c4 = PinPortC4;

        PinUtil::get_pin_address(test_pin_c3) |= (1u << PinUtil::get_number(test_pin_c3));

        TEST_ASSERT_EQUAL(DigitalValues::LOW, PinManager::digital_read(test_pin_c2));
        TEST_ASSERT_EQUAL(DigitalValues::HIGH, PinManager::digital_read(test_pin_c3));
        TEST_ASSERT_EQUAL(DigitalValues::LOW, PinManager::digital_read(test_pin_c4));
    }

    void test_PinManager_analog_write() {
        const PinPort port = PinPortD5;
        const uint8_t duty_cycle = 50;

        PinManager::analog_write(port, duty_cycle);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << COM1A1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << COM1A0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << WGM11));

        // check icr
        TEST_ASSERT_EQUAL(UINT16_MAX, ICR1);

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / 100) * UINT16_MAX, OCR1A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & clkIO_1);
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & (1u << WGM13));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & (1u << WGM12));
    }

    void test_PinManager_analog_read() {
        // TODO: only checks incorrect port and checks if ADMUX amd ADCSRA have been set correctly, needs to check value of signal too
        PinPort pinb2 = PinPortB2;
        TEST_ASSERT_EQUAL(0, PinManager::analog_read(pinb2)); // Should be zero because B2 is not an analog pin

        PinPort pina2 = PinPortA2;
        PinManager::analog_read(pina2);
        TEST_ASSERT_GREATER_OR_EQUAL(2, ADMUX & (2u)); // Check if ADMUX has been set correctly (if it doesn't get cleared after reading ???)

        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, (ADCSRA & (1u << ADSC))); // Check is ADCSRA has been set correctly
    }

    void run() {
        RUN_TEST(test_PinManager_init_adc);
        RUN_TEST(test_PinManager_set_mode);
        RUN_TEST(test_PinManager_digital_write);
        RUN_TEST(test_PinManager_digital_read);
        RUN_TEST(test_PinManager_analog_write);
        RUN_TEST(test_PinManager_analog_read);
    }
}

#endif