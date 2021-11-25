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

    board->debug_P(PSTR("Firmware: "));
    board->debug_P(FIRMWARE_VERSION);
    board->debug_P(PSTR("\n"));

    int loopno = 0;
 
    while (true) {
        if (loopno == 100)
        {
            asm("JMP 0x3800");
        }
        board->loop();
        loopno++;
    }
}
