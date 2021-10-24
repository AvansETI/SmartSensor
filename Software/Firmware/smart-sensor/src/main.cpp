/**
 * @file       : main.cpp
 * @description: The start of the embedded application of the SmartSensor. 
 * @date       : 23 October 2021
 * @author     : Maurice Snoeren (MS)
 * @students   : Patrick de Jong, Paul Hobbel, Sergen Peker, Carlos Cadel, Floris Bob van Elzelingen, Tom Kaasenbrood (TK)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Implement the avr functions directly in stead of abstracting it like Ardiuno.
 * @changes    :
 * 10-09-2021: MS: Updating the code to a mature version.
 * 23-11-2021: MS: Create a first worksing first version. 
 */
#define FOSC 20000000 // Clock Speed

#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include "boards/Board.h"

/* Change here the firmware version of the SmartSensor. */
static const char FIRMWARE_VERSION[] PROGMEM = "v1.0";

/* The main function that is started at startup. This main function creates an instance to the specific board
   and initialize it. Eventually an infinite while loop calls the loop of the board. The main method implements
   the watchdog timer in case the software stops running normally. The board itself should figure our how it was
   started. In case of a watchdog timeout it is wise to send this as message back to the back-end systems.
 */
int main() {
    wdt_enable(WDTO_8S);

    SmartSensorBoard* board = SmartSensorBoard::getBoard();

    board->setup();

    board->debug_P(PSTR("Firmware: "));
    board->debug_P(FIRMWARE_VERSION);
    board->debug_P(PSTR("\n"));
    
    while (true) {
        //wdt_reset();
        board->loop();
    }
}