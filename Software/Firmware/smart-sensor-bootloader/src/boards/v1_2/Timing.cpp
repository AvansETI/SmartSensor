#include <boards/v1_2/Timing.h>

#include <avr/interrupt.h>

// Interrupt timed each 1ms, interrupt take 4 cycles!
ISR(TIMER1_COMPA_vect) { //      => 4 cycles
    _millis++; // update _millis => 2 cycles
    TCNT1 = (uint16_t) 0x0000; //=> 4 cycles reset the timer
}

uint8_t Timing::setup() {
    // No prescaler F_CPU/1
    OCR1A  = (uint16_t) (F_CPU/1000)-10; // Number that represents 1ms, maybe minus extra cycles 10=4+4+2
    TCCR1A = 0b00'00'00'00;              // OC1A/OC1B disabled, CTC-mode
    TCCR1B = 0b00'0'01'001;              // CTC-mode, clk_io/1 prescaler
    TCCR1C = 0b00'00'00'00;              // Disable force
    TIMSK1 = 0b00'1'00'010;              // Timer1 interrupt enabled, interrupt on compare OCR1A, Overflow interrupt disabled!
    // TIFR1 => interrupt flags, cleared when function is executed.

    return 0;
}

uint32_t Timing::millis() {
    return _millis;
}
