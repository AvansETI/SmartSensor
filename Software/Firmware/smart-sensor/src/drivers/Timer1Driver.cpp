#include "drivers/Timer1Driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Interrupt each 1ms, interrupt take 4 cycles, so it can be tuned!
ISR(TIMER1_COMPA_vect) {
    _millis++; // update _millis
}

uint8_t Timer1Driver::setup() {
    // No prescaler F_CPU/1
    OCR1A  = (uint16_t) F_CPU/1000; // Number that represents 1ms
    TCCR1A = 0b00'00'00'00;         // OC1A/OC1B disabled, CTC-mode
    TCCR1B = 0b00'0'01'001;         // CTC-mode, clk_io/1 prescaler
    TCCR1C = 0b00'00'00'00;         // Disable force
    TIMSK1 = 0b00'1'00'010;         // Timer1 interrupt enabled, interrupt on compare OCR1A, Overflow interrupt disabled!
    // TIFR1 => interrupt flags, cleared when function is executed.
    return 0;
}

uint32_t Timer1Driver::millis() {
    return _millis;
}

uint16_t Timer1Driver::getCounterValue() {
    uint16_t counterValue;

    cli(); 
    counterValue = TCNT1;
    sei();

    return counterValue;
}