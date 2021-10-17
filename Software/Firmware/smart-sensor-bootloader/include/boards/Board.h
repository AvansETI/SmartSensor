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
#include <stdio.h>
#include <avr/pgmspace.h>

#include <tasks/Task.h>

#include <util/MessageBuffer.h>
#include <util/RTC.h>

#define SMARTSENSOR_MAX_TASKS 20

/* The class SmartSensorBoard is the base class that is extended by the actual board class.
   Within the main.c application, this base class is used, so no board specific aspects are
   required by any main application functionality. */
class SmartSensorBoard: public SmartSensorMeasurement, public RTCReadTimestampEvent {
protected:
    char id[21];

    /* Total drivers that have been added to the board. */
    uint8_t totalDrivers;

    /* Drivers that have been added to the board. 20 drivers maximum */
    ITask* drivers[SMARTSENSOR_MAX_TASKS]; // Maybe later having a split in resources? Or a resources class that can.

    MeasurementBuffer buffer;

    /* Loop timing. */
    uint32_t loopTiming;
    uint16_t loopTime;

    void rtcReadTimestampEvent(RTCTime& time);

    SmartSensorBoard(): totalDrivers(0) {}
public:
    /* Returns the actual board that belongs to the current hardware. */
    static SmartSensorBoard* getBoard();

    /* Setup the board's hardware. */
    virtual void setup();

    /* Providing the main functionality of the board in a main loop. */
    virtual void loop();

    /* Providing a millis function that contains a counter counting the milliseconds 
     * after the platform has been started. Maybe do this in a utility thing, so it is
     * available for each other function. */
    virtual uint32_t millis() = 0;

    /* Add the given driver to the list. When added it will be immediatly used. */
    void addTask(ITask *task, const char* driverName);

    /* When true an adapter has been inserted. */
    virtual bool adapterInUse() = 0;

    virtual void debug( const char* message) = 0;
    virtual void debugf( const char* message, ...);

    virtual void debug_P( const char* message) = 0;
    virtual void debugf_P( const char* message, ...);

    virtual void addMeasurement(const char* measurment) = 0;

    virtual char* getID() { return this->id; };
};

