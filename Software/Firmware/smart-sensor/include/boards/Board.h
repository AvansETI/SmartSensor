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
#include <string.h>

#include <drivers/Driver.h>

#define SMARTSENSOR_BOARD_1_2 // Define which board needs to be compiled!

#define SMARTSENSOR_MAX_DRIVERS 20

// TODO: Drivers can add measurements to the class, callback using class?
class SmartSensorMeasurement {
private:
    char json[30];

public:
    //SmartSensorMeasurement(char json[30]): json(json) {}
};

struct SmartSensorActuation {
    char* command;
    char* value;
};

/* The class SmartSensorBoard is the base class that is extended by the actual board class.
   Within the main.c application, this base class is used, so no board specific aspects are
   required by any main application functionality. */
class SmartSensorBoard {
protected:
    /* Total drivers that have been added to the board. */
    uint8_t totalDrivers;

    /* Drivers that have been added to the board. 20 drivers maximum */
    IDriver* drivers[SMARTSENSOR_MAX_DRIVERS]; // Maybe later having a split in resources? Or a resources class that can.

    uint8_t totalMeasurements;


public:
    SmartSensorBoard(): totalDrivers(0) {}

    /* Setup the board's hardware. */
    virtual void setup();

    /* Providing the main functionality of the board in a main loop. */
    virtual void loop();

    /* Providing a millis function that contains a counter counting the milliseconds 
     * after the platform has been started. Maybe do this in a utility thing, so it is
     * available for each other function. */
    static uint32_t millis();

    void addDriver(IDriver *driver);

    /* Returns the actual board that belongs to the current hardware. */
    static SmartSensorBoard getBoard();
};

