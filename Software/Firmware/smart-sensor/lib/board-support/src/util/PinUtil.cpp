#include "board-support/util/PinUtil.h"

volatile uint8_t& PinUtil::get_pin_address(PinPort pin) {
    int letter_index = get_letter_index(pin);
    switch (letter_index) {
        case PinPortB:
            return PINB;
        case PinPortC:
            return PINC;
        case PinPortD:
            return PIND;
        case PinPortE:
            return PINE;
        default: // also case PinPortA:
            return PINA;
    }
}

volatile uint8_t& PinUtil::get_port_address(PinPort port) {
    int letter_index = get_letter_index(port);
    switch (letter_index) {
        case PinPortB:
            return PORTB;
        case PinPortC:
            return PORTC;
        case PinPortD:
            return PORTD;
        case PinPortE:
            return PORTE;
        default: // also case PinPortA:
            return PORTA;
    }
}

volatile uint8_t& PinUtil::get_ddr_address(DDR ddr) {
    return PinUtil::get_ddr_address(static_cast<int>(ddr));
}

volatile uint8_t& PinUtil::get_ddr_address(PinPort pin_port) {
    return PinUtil::get_ddr_address(get_letter_index(pin_port));
}

volatile uint8_t& PinUtil::get_ddr_address(int index) {
    switch (index) {
        case DB:
            return DDRB;
        case DC:
            return DDRC;
        case DD:
            return DDRD;
        case DE:
            return DDRE;
        default: // also case DA:
            return DDRA;
    }
}

uint8_t PinUtil::get_letter_index(PinPort pin_port) {
    return get_letter_index(static_cast<int>(pin_port));
}

uint8_t PinUtil::get_letter_index(int pin_port) {
    return pin_port / 10;
}

uint8_t PinUtil::get_number(PinPort pin_port) {
    return pin_port % 10;
}

bool PinUtil::pin_port_letter_check(PinPortLetter letter, PinPort pin_port) {
    return letter == get_letter_index(pin_port);
}