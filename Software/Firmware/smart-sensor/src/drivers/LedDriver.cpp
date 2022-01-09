/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include "drivers/LedDriver.h"

#include "avr/io.h"
#include <util/delay.h>

uint8_t LedDriver::setup() {
    LED_1_DDR = LED_1_DDR | (1 << LED_1_PIN); // Set the led pins as output!
    LED_2_DDR = LED_2_DDR | (1 << LED_2_PIN);

    this->led1Off();
    this->led2Off();

    return 0;
}

uint8_t LedDriver::loop(uint32_t millis) {
    /* Flashing of led 1 when period is non zero without blocking the main loop. */
    if ( this->ledState1.period != 0 ) {
        if ( this->ledState1.timestampedStarted == 0 || // Not started yet! 
             millis > (this->ledState1.timestampedStarted + this->ledState1.period)) { // Reset the counting after period!
            this->ledState1.timestampedStarted = millis;
            LED_1_PORT = LED_1_PORT & ~(1 << LED_1_PIN); // Switch led 1 on!

        } else { // Flashing of the led!
            if ( millis > (this->ledState1.timestampedStarted + this->ledState1.length) ) {
                LED_1_PORT = LED_1_PORT | (1 << LED_1_PIN); // Switch led 1 off!
            } 
        }
    }

    /* Flashing of led 2 when period is non zero without blocking the main loop. */
    if ( this->ledState2.period != 0 ) {
        if ( this->ledState2.timestampedStarted == 0 || // Not started yet! 
             millis > (this->ledState2.timestampedStarted + this->ledState2.period)) { // Reset the counting after period!
            this->ledState2.timestampedStarted = millis;
            LED_2_PORT = LED_2_PORT & ~(1 << LED_2_PIN); // Switch led 2 on!

        } else { // Flashing of the led!
            if ( millis > (this->ledState1.timestampedStarted + this->ledState1.length) ) {
                LED_2_PORT = LED_2_PORT | (1 << LED_2_PIN); // Switch led 2 off!
            } 
        }
    }

    return 0;
}

void LedDriver::resetLed1Flash() {
    this->ledState1 = {0, 0, 0};
}

void LedDriver::resetLed2Flash() {
    this->ledState2 = {0, 0, 0};
}

uint8_t LedDriver::reset() {
    this->setup();

    return 0;
}

uint8_t LedDriver::sleep() {
    this->led1Off(); // Switch of the leds to reduce the power consumption
    this->led2Off();

    return 0;
}

uint8_t LedDriver::wakeup() {
    return 0;
}

void LedDriver::led1On() {
    this->resetLed1Flash();
    LED_1_PORT = LED_1_PORT & ~(1 << LED_1_PIN); // Note that led is on when bit is low!
}

void LedDriver::led1Off() {
    this->resetLed1Flash();
    LED_1_PORT = LED_1_PORT | (1 << LED_1_PIN);
}

void LedDriver::led2On() {
    this->resetLed2Flash();
    LED_2_PORT = LED_2_PORT & ~(1 << LED_2_PIN);
}

void LedDriver::led2Off() {
    this->resetLed2Flash();
    LED_2_PORT = LED_2_PORT | (1 << LED_2_PIN);
}

void LedDriver::led1Flash(uint16_t period, uint16_t length) {
    if ( length <= period ) {
        this->ledState1 = {period, length, 0};
    }
}

void LedDriver::led2Flash(uint16_t period, uint16_t length) {
    if ( length <= period ) {
        this->ledState2 = {period, length, 0};
    }
}
