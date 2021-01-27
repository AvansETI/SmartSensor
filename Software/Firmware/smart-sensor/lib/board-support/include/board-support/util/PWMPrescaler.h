#ifndef PWMPRESCALER_H_
#define PWMPRESCALER_H_

#include <boardsupport.h>

/**
 * Available PWM prescalers to use with the PWMDriver
 */
enum PWMPrescaler {
    clkIO_1 = (1u << CS00),
    clkIO_8 = (1u << CS01),
    clkIO_64 = (1u << CS01) | (1u << CS00),
    clkIO_256 = (1u << CS02),
    clkIO_1024 = (1u << CS02) | (1u << CS00)
};

#endif