#include <boardsupport.h>
#include "board-support/drivers/PWMDriver.h"

bool PWMDriver::write(const PinPort pin_port, uint8_t duty_cycle, const PWMPrescaler prescaler) {
    if (0 == duty_cycle) {
        return stop_writing(pin_port);
    } else if (PWM_MAX_DUTY_CYCLE < duty_cycle) { // duty_cycle greater than 100
        duty_cycle = PWM_MAX_DUTY_CYCLE;
    }

    PWMCom pwm_com = PWMCom::COMA;
    switch (pin_port) {
        case PinPortB4: // 8-bit timer (0B)
            pwm_com = PWMCom::COMB;
        case PinPortB3: // 8-bit timer (0A)
            PinManager::set_mode(pin_port, OUTPUT);
            return write_using_8_bit_timer(pin_port, TCCR0A, OCR0A, TCCR0B, duty_cycle, prescaler, pwm_com);

        case PinPortD4: // 16-bit timer (1B)
            pwm_com = PWMCom::COMB;
        case PinPortD5: // 16-bit timer (1A)
            PinManager::set_mode(pin_port, OUTPUT);
            return write_using_16_bit_timer(pin_port, TCCR1A, ICR1, OCR1A, TCCR1B, duty_cycle, prescaler, pwm_com);

        case PinPortD6: // 8-bit timer with async operation (2B)
            pwm_com = PWMCom::COMB;
        case PinPortD7: // 8-bit timer with async operation (2A)
            PinManager::set_mode(pin_port, OUTPUT);
            return write_using_8_bit_async_timer(pin_port, TCCR2A, OCR2A, TCCR2B, duty_cycle, prescaler, pwm_com);

        case PinPortB7: // 16-bit timer (3B) (PinPortB7 is also 4B, but is using 3B)
            pwm_com = PWMCom::COMB;
        case PinPortB6: // 16-bit timer (3A)
            PinManager::set_mode(pin_port, OUTPUT);
            return write_using_16_bit_timer(pin_port, TCCR3A, ICR3, OCR3A, TCCR3B, duty_cycle, prescaler, pwm_com);

        case PinPortC4: // 16-bit timer (4A)
            PinManager::set_mode(pin_port, OUTPUT);
            return write_using_16_bit_timer(pin_port, TCCR4A, ICR4, OCR4A, TCCR4B, duty_cycle, prescaler, pwm_com);

        default: // not a valid port
            return false;
    }
}

bool PWMDriver::stop_writing(PinPort pin_port) {
    switch (pin_port) {
        case PinPortB4: // 8-bit timer (0B)
        case PinPortB3: // 8-bit timer (0A)
            return stop_writing_using_8_bit_timer(pin_port, TCCR0A, OCR0A, TCCR0B);

        case PinPortD4: // 16-bit timer (1B)
        case PinPortD5: // 16-bit timer (1A)
            return stop_writing_using_16_bit_timer(pin_port, TCCR1A, ICR1, OCR1A, TCCR1B);

        case PinPortD6: // 8-bit timer with async operation (2B)
        case PinPortD7: // 8-bit timer with async operation (2A)
            return stop_writing_using_8_bit_timer(pin_port, TCCR2A, OCR2A, TCCR2B);

        case PinPortB7: // 16-bit timer (3B) (PinPortB7 is also 4B, but is using 3B)
        case PinPortB6: // 16-bit timer (3A)
            return stop_writing_using_16_bit_timer(pin_port, TCCR3A, ICR3, OCR3A, TCCR3B);

        case PinPortC4: // 16-bit timer (4A)
            return stop_writing_using_16_bit_timer(pin_port, TCCR4A, ICR4, OCR4A, TCCR4B);

        default: // not a valid port
            return false;
    }
}

uint32_t PWMDriver::read(PinPort pin_port) {
    // TODO: implement read method
    return 0;
}

bool PWMDriver::write_using_16_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint16_t& icr,
                                         volatile uint16_t& ocra, volatile uint8_t& tccrb, uint8_t duty_cycle,
                                         PWMPrescaler prescaler, PWMCom com) {
    if (!contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_16_BIT, USABLE_PWM_WRITE_PIN_PORTS_16_BIT_COUNT))
        return false;

    // Specify output port and set PWM in inverting mode
    switch (com) {
        case PWMCom::COMA:
            tccra = (1u << COM1A1) | (1u << COM1A0);
            break;
        case PWMCom::COMB:
            tccra = (1u << COM1B1) | (1u << COM1B0);
            break;
        default:
            return false;
    }

    tccra |= (1u << WGM11);

    // Set top value to MAX
    icr = UINT16_MAX;

    // Set OCR (trigger value)
    ocra = (duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT16_MAX;

    // Setting prescaler and start to write
    tccrb = prescaler | (1u << WGM13) | (1u << WGM12);

    return true;
}

bool PWMDriver::write_using_8_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                        volatile uint8_t& tccrb, uint8_t duty_cycle, PWMPrescaler prescaler,
                                        PWMCom com) {
    if (!contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_8_BIT, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_COUNT))
        return false;

    // Specify output port and set PWM in inverting mode
    switch (com) {
        case PWMCom::COMA:
            tccra = (1u << COM0A1) | (1u << COM0A0);
            break;
        case PWMCom::COMB:
            tccra = (1u << COM0B1) | (1u << COM0B0);
            break;
        default:
            return false;
    }

    tccra |= (1u << WGM01) | (1u << WGM00);

    // Set OCR (trigger value)
    ocra = (duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT8_MAX;

    // Setting prescaler and start to write
    tccrb = prescaler | (1u << WGM02);

    return true;
}

bool PWMDriver::write_using_8_bit_async_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                              volatile uint8_t& tccrb, uint8_t duty_cycle, PWMPrescaler prescaler,
                                              PWMCom com) {
    if (!contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC_COUNT))
        return false;

    // Specify output port and set PWM in inverting mode
    switch (com) {
        case PWMCom::COMA:
            tccra = (1u << COM2A1) | (1u << COM2A0);
            break;
        case PWMCom::COMB:
            tccra = (1u << COM2B1) | (1u << COM2B0);
            break;
        default:
            return false;
    }

    tccra |= (1u << WGM21) | (1u << WGM20);

    // Set OCR (trigger value)
    ocra = (duty_cycle / PWM_MAX_DUTY_CYCLE) * UINT8_MAX;

    // Setting prescaler and start to write (Skipping clkIO_32 & clkIO_128 because they are only available in the specific 8-bit async timers)
    switch (prescaler) {
        case PWMPrescaler::clkIO_8:
            tccrb = (1u << CS21);
            break;
        case PWMPrescaler::clkIO_64:
            tccrb = (1u << CS22);
            break;
        case PWMPrescaler::clkIO_256:
            tccrb = (1u << CS22) | (1u << CS21);
            break;
        case PWMPrescaler::clkIO_1024:
            tccrb = (1u << CS22) | (1u << CS21) | (1u << CS20);
            break;
        default: // also case PWMPrescaler::clkIO_1:
            tccrb = (1u << CS20);
            break;
    }

    return true;
}

bool PWMDriver::stop_writing_using_8_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                               volatile uint8_t& tccrb) {
    if (!contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_8_BIT, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_COUNT)
        && !contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC, USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC_COUNT))
        return false;

    tccra = 0;
    ocra = 0;
    tccrb = 0;

    return true;
}

bool PWMDriver::stop_writing_using_16_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint16_t& icr,
                                                volatile uint16_t& ocra, volatile uint8_t& tccrb) {
    if (!contains_pin_port(pin_port, USABLE_PWM_WRITE_PIN_PORTS_16_BIT, USABLE_PWM_WRITE_PIN_PORTS_16_BIT_COUNT))
        return false;

    tccra = 0;
    ocra = 0;
    tccrb = 0;
    icr = 0;

    return true;
}

bool PWMDriver::contains_pin_port(const PinPort pin_port, const PinPort pin_ports[], const uint8_t pin_ports_size) {
    for (uint8_t i = 0; i < pin_ports_size; i++) {
        if (pin_ports[i] == pin_port) {
            return true;
        }
    }
    return false;
}