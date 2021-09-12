#pragma once
/**
 * @file       : LedDriver.h
 * @description: This driver handles the leds on the board.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
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

struct LedState {
    uint16_t period;
    uint16_t length;
    uint32_t timestampedStarted;
};

/* The class LedDriver handles the two leds that are on the board. */
class LedDriver: public Driver {
private:
    LedState ledState1 PROGMEM;
    LedState ledState2 PROGMEM;

public:
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    void led1On();
    void led1Off();
    void led2On();
    void led2Off();
    void led1Flash(uint16_t period, uint16_t length);
    void led2Flash(uint16_t period, uint16_t length);

private:
    void resetLed1Flash();
    void resetLed2Flash();
};

