#pragma once
/**
 * @file       : util/Serial0.h
 * @description: -
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : Most probably this is not a driver but more an hardware related function.
 * @updates
 * 
 */
#include <stdint.h>
#include <avr/pgmspace.h>

#define SERIAL0_BAUD 9600
#define SERIAL0_UBRR F_CPU/16/SERIAL0_BAUD-1

class Serial0 {
private:
    //uint8_t busy;
    //char buffer[30];

protected:
    Serial0() {}; // singleton!

public:
    static Serial0* getInstance() {
        static Serial0 _serial0;
        return &_serial0;
    }

    uint8_t setup();
    // loop => send in the loop the characters away, it is possible to work with a MessageBuffer.
    //uint8_t isBusy() { return this->busy; }
    uint8_t print(const char* message); // Still blocking, this can be solved by buffer or an MessageBuffer and using busy that others can wait.

private:
    void transmitChar(char data);
};
