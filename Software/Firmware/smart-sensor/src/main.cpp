/**
 * Entry point of the application
 * @date   : 12 May 2020
 * @author : Patrick de Jong, Paul Hobbel, Sergen Peker, Carlos Cadel, Floris Bob van Elzelingen, Maurice Snoeren (MS)
 * @version: 0.9 test version
 * #todo   : Implement the avr functions directly in stead of abstracting it like Ardiuno.
 * @updates
 *  10-09-2021: MS: Updating the code to a mature version
 * 
 */
#define FOSC 20000000 // Clock Speed

#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "boards/Board.h"

static const char FIRMWARE_VERSION[] PROGMEM = "v1.0";

int main() {
    SmartSensorBoard* board = SmartSensorBoard::getBoard();

    board->setup();

    board->debugf(PSTR("Firmware: %s"), FIRMWARE_VERSION);

    while (true) {
        board->loop();
        _delay_ms(1); // When millis is correctly implemented remove this one!
    }
}
