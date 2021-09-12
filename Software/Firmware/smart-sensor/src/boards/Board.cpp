#include <boards/Board.h>

#include <stdlib.h>

/* Define in the main.c which board you would like to compile to. In the future
   it is possible that the software detects the version itself. */
#if defined(SMARTSENSOR_BOARD_1_2)
    #pragma message "SmartSensor v1.2 has been selected to be compiled."
    #include "boards/BoardV1_2.h"
#else
    #pragma message "SMARTSENSOR_BOARD_X_X has not been defined, using the newest SmartBoard version v1.2."
    #include "boards/BoardV1_2.h"
#endif

SmartSensorBoard SmartSensorBoard::getBoard() {
    #if defined(SMARTSENSOR_BOARD_1_2)
        SmartSensorBoardV1_2 board;
        
    #else
        SmartSensorBoardV1_2 board;
    #endif

    return board;
}

void SmartSensorBoard::addDriver(IDriver *driver) {
    if ( this->totalDrivers < SMARTSENSOR_MAX_DRIVERS) {
        this->drivers[this->totalDrivers] = driver;
        this->totalDrivers++;
    
    } else {
        // Cannot add more drivers to the board, please enlarge the number of drivers!
    }
}

void SmartSensorBoard::setup() {
    for ( uint8_t i=0; i < this->totalDrivers; i++ ) { // Setup all the drivers
        this->drivers[i]->setup();
    }
}

void SmartSensorBoard::loop() {
    for ( uint8_t i=0; i < this->totalDrivers; i++ ) { // Loop through all the drivers
        this->drivers[i]->loop();
    }
}

uint32_t SmartSensorBoard::millis() {
    return 0; // TODO
}
