#include <boards/v1_2/Timing.h>

#include <avr/interrupt.h>

// Interrupt timed each 1ms, interrupt take 4 cycles!
ISR(TIMER4_COMPA_vect) { //      => 4 cycles
    _millis++; // update _millis => 2 cycles
    TCNT4 = (uint16_t) 0x0000; //=> 4 cycles reset the timer
}

uint8_t Timing::setup() {
    // No prescaler F_CPU/1
    OCR4A  = (uint16_t) (F_CPU/1000)-10; // Number that represents 1ms, maybe minus extra cycles 10=4+4+2
    TCCR4A = 0b00'00'00'00;              // OC4A/OC4B disabled, CTC-mode
    TCCR4B = 0b00'0'01'001;              // CTC-mode, clk_io/1 prescaler
    TCCR4C = 0b00'00'00'00;              // Disable force
    TIMSK4 = 0b00'1'00'010;              // Timer4 interrupt enabled, interrupt on compare OCR1A, Overflow interrupt disabled!

    return 0;
}

uint32_t Timing::millis() {
    return _millis;
}
