#pragma once
/**
 * @file       : Timing.h
 * @description: This Timing class implements the millis() using the hardware Timer1.
 * @date       : 03-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @todo       : -
 * @updates    : -
 * 
 */
#include <stdint.h>

/* The variabele _millis will be used to hold the total microseconds that have been passed
   since the controller has been started.
*/
static uint32_t _millis;

/* Class: Timing
   The class timing implements the millis() method for this board to create timing of the board.
*/
class Timing {
protected:
    /* Constructor Timing is protected to create a singleton of this Timing class.
    */
    Timing() { _millis = 0; }; // Singleton

public:
    /* The method getInstance() returns the pointer to the singleton class.
    */ 
    static Timing* getInstance() {
        static Timing _timer1;
        return &_timer1;
    }

    /* The method setup is called once to setup the Timing class.
    */
    uint8_t setup();

    /* After the object has been setted up, the method millis() returns the amount of milliseconds
       has been passed.
    */
    uint32_t millis();
};
