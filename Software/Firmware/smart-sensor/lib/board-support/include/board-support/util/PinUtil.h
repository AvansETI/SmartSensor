#ifndef PINUTIL_H
#define PINUTIL_H

#include <boardsupport.h>
#include "PinPort.h"
#include "DDR.h"
#include "PinPortLetter.h"

class PinUtil {
    public:
        /**
         * Get the address from a pin
         *
         * @param pin Pin where the address will be gotten from
         * @return Address of pin
         */
        volatile static uint8_t& get_pin_address(PinPort pin);

        /**
         * Get the address from a port
         *
         * @param port Port where the address will be gotten from
         * @return Address of port
         */
        volatile static uint8_t& get_port_address(PinPort port);

        /**
         * Get DDR address from a DDR enum value
         *
         * @param ddr DDR where the address will be gotten from
         * @return Address of DDR
         */
        volatile static uint8_t& get_ddr_address(DDR ddr);

        /**
         * Get DDR address that is linked to the specified pin and port
         *
         * Example:
         *
         * pin_port = PinPortB1, returns DDRB
         *
         * @param pin_port Pin or port where the DDR address will be gotten from
         * @return Address of DDR
         */
        volatile static uint8_t& get_ddr_address(PinPort pin_port);

        /**
         * Returns letter index of pin or port
         *
         * Examples:
         *
         * pin_port = PinPortA5, returns 0
         *
         * pin_port = PinPortA2, returns 0
         *
         * pin_port = PinPortB2, returns 1
         *
         * pin_port = PinPortD3, returns 3
         *
         * @param pin_port Pin or port where the letter index will be gotten from
         * @return Letter index of pin or port
         */
        static uint8_t get_letter_index(PinPort pin_port);

        /**
         * Returns number of pin or port
         *
         * Examples:
         *
         * pin_port = PinPortA5, returns 5
         *
         * pin_port = PinPortA2, returns 2
         *
         * pin_port = PinPortB2, returns 2
         *
         * @param pin_port Pin or port where the number will be gotten from
         * @return Number of pin or port
         */
        static uint8_t get_number(PinPort pin_port);

        /**
         * Checks if port is from a specific letter
         *
         * Examples:
         *
         * letter = PinPortA & pin_port = PinPortA0, returns true
         *
         * letter = PinPortB & pin_port = PinPortB2, returns true
         *
         * letter = PinPortD & pin_port = PinPortC1, returns false
         *
         * @param letter Letter that will be compared to the pin or port
         * @param pin_port Pin or port that will be compared to the letter
         * @return Boolean if pin or port is from te given letter
         */
        static bool pin_port_letter_check(PinPortLetter letter, PinPort pin_port);

    private:
        /**
         * Get DDR address from specified index
         *
         * @param index Index where the DDR address will be gotten from
         * @return Address of DDR
         */
        volatile static uint8_t& get_ddr_address(int index);

        /**
         * Get letter index of int value of pin or port
         *
         * @param pin_port Int value of a pin or port
         * @return Letter index of pin or port
         */
        static uint8_t get_letter_index(int pin_port);
};

#endif
