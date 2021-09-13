#pragma once
/**
 * @file       : Timer1.h
 * @description: This driver handles the timer 1 to create the millis functionality.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : Most probably this is not a driver but more an hardware related function.
 * @updates
 * 
 */
#include <stdint.h>
#include <avr/pgmspace.h>

#include <drivers/Driver.h>

static uint32_t _millis;

class Timer1 {
private:

protected:
    Timer1() { _millis = 0; }; // Singleton

public:
    static Timer1* getInstance() {
        static Timer1 _timer1;
        return &_timer1;
    }

    uint8_t setup();
    uint32_t millis();

private:
    uint16_t getCounterValue();
};
