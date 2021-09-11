#include <boards/Board.h>

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

