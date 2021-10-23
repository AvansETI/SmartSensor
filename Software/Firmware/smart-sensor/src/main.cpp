/**
 * @file       : main.cpp
 * @description: The start of the embedded application of the SmartSensor. 
 * @date       : 23 October 2021
 * @author     : Patrick de Jong, Paul Hobbel, Sergen Peker, Carlos Cadel, Floris Bob van Elzelingen, Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Implement the avr functions directly in stead of abstracting it like Ardiuno.
 * @changes    :
 * 10-09-2021: MS: Updating the code to a mature version.
 * 23-11-2021: MS: Create a first worksing first version. 
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
 
    while (true) {
        board->loop();
    }
    
}