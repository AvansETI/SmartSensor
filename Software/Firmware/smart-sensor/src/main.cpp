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
#include <stdio.h>
#include <avr/pgmspace.h>

#include "boards/Board.h"

constexpr const char* FIRMWARE_VERSION PROGMEM = "v0.9";

int main() {
    SmartSensorBoard board = SmartSensorBoard::getBoard();
    board.setup();

    //board.debug(FIRMWARE_VERSION); // using the board

    while (true) {
        board.loop();
    }
}
