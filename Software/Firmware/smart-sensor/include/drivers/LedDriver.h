#pragma once
/**
 * @file       : LedDriver.h
 * @description: This driver handles the leds on the board.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Create SRAM space to push the led state variables to PROGMEM is required.
 * @updates
 * 
 */
#include <stdint.h>

#include <avr/pgmspace.h>

#include <drivers/Driver.h>

/* Define how the MFP pin is connected to the Atmega. */
#define LED_1_PIN  PD4
#define LED_1_PORT PORTD
#define LED_1_DDR  DDRD
#define LED_2_PIN  PD5
#define LED_2_DDR  DDRD
#define LED_2_PORT PORTD

/* Hold the state variable of a led in order to provide complex flashing of the led. */
struct LedState {
    uint16_t period;             // The amount of time in ms of one period.
    uint16_t length;             // The amount of time in ms that within this period the led is switched one (length < period).
    uint32_t timestampedStarted; // Holds the timestamp that the period was started to calculate on and off state. 
};

/* The class LedDriver handles the two leds that are on the board. */
class LedDriver: public Driver {
private:
    /* Holds the led state of led 1. */
    LedState ledState1;

    /* Holds the led state of led 2. */
    LedState ledState2;

protected:
    /* Protected constructor in order to create a singleton class. */
    LedDriver() {}

public:
    /* Returns the singleton instance to this class. */
    static LedDriver* getInstance() {
        static LedDriver _ledDriver;
        return &_ledDriver;
    }

public:
    /* Interface Task methods. */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    /* Switch led 1 on. */
    void led1On();

    /* Switch led 1 off. */
    void led1Off();

    /* Switch led 2 on. */
    void led2On();

    /* Switch led 2 off. */
    void led2Off();

    /* Flash led 1 with a certian periode and on length time in ms. */
    void led1Flash(uint16_t period, uint16_t length);

    /* Flash led 2 with a certian periode and on length time in ms. */
    void led2Flash(uint16_t period, uint16_t length);

private:
    /* Reset the state of led 1. */
    void resetLed1Flash();

    /* Reset the state of led 2. */
    void resetLed2Flash();
};
