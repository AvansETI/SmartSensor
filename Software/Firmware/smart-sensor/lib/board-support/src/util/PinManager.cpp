#include <boardsupport.h>
#include "board-support/util/PinManager.h"

void PinManager::init_adc() {
    ADMUX = (1u << REFS1);

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1u << ADEN) | (1u << ADPS2) | (1u << ADPS1) | (1u << ADPS0);
}

bool PinManager::is_adc_initialized() {
    return (ADMUX & (1u << REFS1)) > LOW;
}

void PinManager::set_mode(PinPort pin, PinMode mode) {
    uint8_t pin_number = PinUtil::get_number(pin);

    if (mode == OUTPUT) {
        PinUtil::get_ddr_address(pin) |= (1u << pin_number);
    } else {
        PinUtil::get_ddr_address(pin) &= ~(1u << pin_number);
    }

    // BUG: set_mode should not write a value to a pin! That should be done by the main application!
    digital_write(pin, LOW);
}

void PinManager::digital_write(PinPort port, DigitalValues value) {
    PWMDriver::stop_writing(port);

    volatile uint8_t& address = PinUtil::get_port_address(port);
    uint8_t port_number = PinUtil::get_number(port);

    if (DigitalValues::HIGH == value) {
        address |= (1u << port_number);

    } else {
        address &= ~(1u << port_number);
    }
}

uint8_t PinManager::digital_read(PinPort pin) {
    PWMDriver::stop_writing(pin);

    volatile uint8_t& address = PinUtil::get_pin_address(pin);
    uint8_t pin_number = PinUtil::get_number(pin);

    uint8_t state = address & (1u << pin_number);
    if (state == DigitalValues::LOW) {
        return DigitalValues::LOW;
    } else {
        return DigitalValues::HIGH;
    }
}

void PinManager::analog_write(PinPort pin, uint8_t value) {
    if (value > PWM_MAX_DUTY_CYCLE) {
        value = PWM_MAX_DUTY_CYCLE;
    }

    if (DigitalValues::LOW == value) {
        digital_write(pin, DigitalValues::LOW);
    } else if (PWM_MAX_DUTY_CYCLE == value) {
        digital_write(pin, DigitalValues::HIGH);
    } else {
        PWMDriver::write(pin, value);
    }
}

uint16_t PinManager::analog_read(PinPort pin) {
    if (!PinUtil::pin_port_letter_check(PinPortA, pin)) // Analog ports are on the A pins
        return LOW;

    if (!is_adc_initialized())
        init_adc();

    ADMUX &= ~(0b11111u); // Clear MUX
    ADMUX |= PinUtil::get_number(pin);

    ADCSRA |= 1u << ADSC; // Begin ADC

    #ifndef UNIT_TEST
    while (ADCSRA & (1u << ADSC)); // Wait till ADSC bit has been cleared
    #endif

    return ADCL | (ADCH << 8u); // Combine high and low bits of ADC
}