#pragma once
/**
 * @file       : boards/Board.h
 * @description: This file contains the specific boards that have been created. It makes sure, the software
 *               is able to handel different hardware versions. In this file the interface and abstract class
 *               is available to be used. For every board, this abstract class should be inherited.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#include <stdint.h>

/* The class SmartSensorBoard is the base class that is extended by the actual board class.
   Within the main.c application, this base class is used, so no board specific aspects are
   required by any main application functionality. */
class SmartSensorBoard {
private:

public:
    SmartSensorBoard() {}

    /* Returns the actual board that belongs to the current hardware. */
    static SmartSensorBoard getBoard();
};

