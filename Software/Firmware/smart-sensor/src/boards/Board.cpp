#include <boards/Board.h>

#include <stdlib.h>

#include <util/delay.h>
#include <avr/pgmspace.h>

/* Define in the main.c which board you would like to compile to. In the future
   it is possible that the software detects the version itself. */
#if defined(SMARTSENSOR_BOARD_1_2)
    #pragma message "SmartSensor v1.2 has been selected to be compiled."
    #include "boards/BoardV1_2.h"
    SmartSensorBoardV1_2 board;
#else
    #pragma message "SMARTSENSOR_BOARD_X_X has not been defined, using the newest SmartBoard version v1.2."
    #include "boards/BoardV1_2.h"
    SmartSensorBoardV1_2 board;
#endif

SmartSensorBoard* SmartSensorBoard::getBoard() {
    return &board;
}

void SmartSensorBoard::addDriver(IDriver *driver, const char* driverName) {
    this->debug_P(PSTR("Adding driver: "));
    this->debug_P(driverName);

    if ( this->totalDrivers < SMARTSENSOR_MAX_DRIVERS) {
        uint8_t result = driver->setup();

        if ( result == 0 ) {
            this->drivers[this->totalDrivers] = driver;
            this->totalDrivers++;
            this->debug_P(PSTR(": Succesfully!\n"));
        
        } else {
            this->debugf_P(PSTR(": Could not be loaded: %d\n"), result);
        }
    
    } else {
        this->debugf_P(PSTR(": Maximum drivers reached, not added to the system.\n"), driverName);
    }
}

void SmartSensorBoard::setup() {
    this->loopTiming = this->millis();
}

void SmartSensorBoard::loop() {
    for ( uint8_t i=0; i < this->totalDrivers; ++i ) { // Loop through all the drivers
        this->drivers[i]->loop(this->millis());
    }

    this->loopTime = ( this->millis() - this->loopTiming );
    this->debugf_P(PSTR("Loop time %d ms\n"), this->loopTime);
    this->loopTiming = this->millis();
}

// http://www.cplusplus.com/reference/cstdio/vsprintf/
void SmartSensorBoard::debugf( const char* message, ...) {
    char buffer[50];
    va_list args;
    va_start(args, message);
    vsprintf (buffer, message, args);
    va_end (args);

    this->debug(buffer);
}

void SmartSensorBoard::debugf_P( const char* message, ...) {
    char buffer[50];
    va_list args;
    va_start(args, message);
    vsprintf_P(buffer, message, args);
    va_end (args);

    this->debug(buffer);
}
