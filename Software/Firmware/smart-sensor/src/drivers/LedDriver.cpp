#include "drivers/LedDriver.h"
#include "avr/io.h"
#include <util/delay.h>

int LedDriver::setup() {
    LED_1_DDR = LED_1_DDR | (1 << LED_1_PIN); // Set the led pins as output!
    LED_2_DDR = LED_2_DDR | (1 << LED_2_PIN);

    return 0;
}

int LedDriver::loop() {
    // WISH: Nothing to do here, or we could implement flashing of the leds here!
    // WISH: For example, flash(every x seconds, y length) and oneTimeFlash(y length)
    // WISH: this is only possible when a millis is available to know some timestamp.

    this->led1On(); // Just for testing!
    _delay_ms(1000);
    this->led1Off();
    _delay_ms(1000);

    return 0;
}

int LedDriver::reset() {
    this->setup();

    return 0;
}

int LedDriver::sleep() {
    this->led1Off(); // Switch of the leds to reduce the power consumption
    this->led2Off();

    return 0;
}

int LedDriver::wakeup() {
    return 0;
}

void LedDriver::led1On() {
    LED_1_PORT = LED_1_PORT & ~(1 << LED_1_PIN); // Note that led is on when bit is low!
}

void LedDriver::led1Off() {
    LED_1_PORT = LED_1_PORT | (1 << LED_1_PIN);
}

void LedDriver::led2On() {
    LED_2_PORT = LED_2_PORT & ~(1 << LED_2_PIN);
}

void LedDriver::led2Off() {
    LED_2_PORT = LED_2_PORT | (1 << LED_2_PIN);
}
