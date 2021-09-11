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

#include <drivers/Driver.h>

/* Define how the MFP pin is connected to the Atmega. */
#define LED_1_PIN  PD4
#define LED_1_PORT PORTD
#define LED_1_DDR  DDRD
#define LED_2_PIN  PD5
#define LED_2_DDR  DDRD
#define LED_2_PORT PORTD

/* The class LedDriver handles the two leds that are on the board. */
class LedDriver: public Driver {
public:
    int setup();
    int loop();
    int reset();
    int sleep();
    int wakeup();

    void led1On();
    void led1Off();
    void led2On();
    void led2Off();
};

