#ifndef BOARD_SUPPORT_PWMDRIVERTESTS_HPP
#define BOARD_SUPPORT_PWMDRIVERTESTS_HPP

#include <board-support/drivers/PWMDriver.h>

namespace test_drivers_PWMDriversTests {
    void test_PWMDriver_write_16_bit_coma() {
        // write_using_16_bit_timer(PinPortD5, TCCR1A, ICR1, OCR1A, TCCR1B, duty_cycle, prescaler, PWMCom::COMA);
        const PinPort port = PinPortD5;
        const uint8_t duty_cycle = 50;
        const PWMPrescaler prescaler = PWMPrescaler::clkIO_256;

        bool write_successful = PWMDriver::write(port, duty_cycle, prescaler);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << COM1A1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << COM1A0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1A & (1u << WGM11));

        // check icr
        TEST_ASSERT_EQUAL(UINT16_MAX, ICR1);

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT16_MAX, OCR1A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & prescaler);
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & (1u << WGM13));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR1B & (1u << WGM12));
    }

    void test_PWMDriver_write_16_bit_comb() {
        // write_using_16_bit_timer(PinPortB7, TCCR3A, ICR3, OCR3A, TCCR3B, duty_cycle, prescaler, PWMCom::COMB);
        const PinPort port = PinPortB7;
        const uint8_t duty_cycle = 35;
        const PWMPrescaler prescaler = PWMPrescaler::clkIO_8;

        bool write_successful = PWMDriver::write(port, duty_cycle, prescaler);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3A & (1u << COM1B1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3A & (1u << COM1B0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3A & (1u << WGM11));

        // check icr
        TEST_ASSERT_EQUAL(UINT16_MAX, ICR3);

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT16_MAX, OCR3A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3B & prescaler);
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3B & (1u << WGM13));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR3B & (1u << WGM12));
    }

    void test_PWMDriver_write_8_bit_coma() {
        // write_using_8_bit_timer(PinPortB3, TCCR0A, OCR0A, TCCR0B, duty_cycle, prescaler, PWMCom::COMA);
        const PinPort port = PinPortB3;
        const uint8_t duty_cycle = 75;
        const PWMPrescaler prescaler = PWMPrescaler::clkIO_1024;

        bool write_successful = PWMDriver::write(port, duty_cycle, prescaler);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << COM0A1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << COM0A0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << WGM01));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << WGM00));

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT8_MAX, OCR0A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0B & prescaler);
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0B & (1u << WGM02));
    }

    void test_PWMDriver_write_8_bit_comb() {
        TCCR0A, OCR0A, TCCR0B = 0;

        // write_using_8_bit_timer(PinPortB4, TCCR0A, OCR0A, TCCR0B, duty_cycle, prescaler, PWMCom::COMA);
        const PinPort port = PinPortB4;
        const uint8_t duty_cycle = 75;
        const PWMPrescaler prescaler = PWMPrescaler::clkIO_1024;

        bool write_successful = PWMDriver::write(port, duty_cycle, prescaler);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << COM0B1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << COM0B0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << WGM01));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0A & (1u << WGM00));

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT8_MAX, OCR0A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0B & prescaler);
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR0B & (1u << WGM02));
    }

    void test_PWMDriver_write_8_bit_async_coma() {
        // write_using_8_bit_async_timer(PinPortD7, TCCR2A, OCR2A, TCCR2B, duty_cycle, prescaler, PWMCom::COMA);
        const PinPort port = PinPortD7;
        const uint8_t duty_cycle = 30;
        const PWMPrescaler prescaler = PWMPrescaler::clkIO_1024;

        bool write_successful = PWMDriver::write(port, duty_cycle, prescaler);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << COM2A1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << COM2A0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << WGM21));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << WGM20));

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT16_MAX, OCR2A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2B & (1u << CS22));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2B & (1u << CS21));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2B & (1u << CS20));
    }

    void test_PWMDriver_write_8_bit_async_comb() {
        TCCR2A, OCR2A, TCCR2B = 0;

        // write_using_8_bit_async_timer(PinPortD6, TCCR2A, OCR2A, TCCR2B, duty_cycle, prescaler, PWMCom::COMB);
        const PinPort port = PinPortD6;
        const uint8_t duty_cycle = 10;

        bool write_successful = PWMDriver::write(port, duty_cycle);

        // check if write was successful
        TEST_ASSERT_EQUAL(true, write_successful);

        // check tccra
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << COM2B1));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << COM2B0));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << WGM21));
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2A & (1u << WGM20));

        // check ocra
        TEST_ASSERT_EQUAL((duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT16_MAX, OCR2A);

        // check tccrb
        TEST_ASSERT_GREATER_OR_EQUAL(HIGH, TCCR2B & (1u << CS20));
    }

    void test_PWMDriver_write_invalid_port() {
        // write not successful
        TEST_ASSERT_EQUAL(false, PWMDriver::write(PinPortB1, 20));
    }

    void test_PWMDriver_stop_writing_8_bit() {
        const PinPort port = PinPortD6;

        bool stop_writing_successful = PWMDriver::stop_writing(port);

        // check if stop writing was successful
        TEST_ASSERT_EQUAL(true, stop_writing_successful);

        // check addresses
        TEST_ASSERT_EQUAL(0, TCCR2A);
        TEST_ASSERT_EQUAL(0, OCR2A);
        TEST_ASSERT_EQUAL(0, TCCR2B);
    }

    void test_PWMDriver_stop_writing_16_bit() {
        const PinPort port = PinPortB7;

        bool stop_writing_successful = PWMDriver::stop_writing(port);

        // check if stop writing was successful
        TEST_ASSERT_EQUAL(true, stop_writing_successful);

        // check addresses
        TEST_ASSERT_EQUAL(0, TCCR3A);
        TEST_ASSERT_EQUAL(0, OCR3A);
        TEST_ASSERT_EQUAL(0, TCCR3B);
        TEST_ASSERT_EQUAL(0, ICR3);
    }

    void run() {
        RUN_TEST(test_PWMDriver_write_16_bit_coma);
        RUN_TEST(test_PWMDriver_write_16_bit_comb);

        RUN_TEST(test_PWMDriver_write_8_bit_coma);
        RUN_TEST(test_PWMDriver_write_8_bit_comb);

        RUN_TEST(test_PWMDriver_write_8_bit_async_coma);
        RUN_TEST(test_PWMDriver_write_8_bit_async_comb);

        RUN_TEST(test_PWMDriver_write_invalid_port);

        RUN_TEST(test_PWMDriver_stop_writing_8_bit);
        RUN_TEST(test_PWMDriver_stop_writing_16_bit);
    }
}

#endif