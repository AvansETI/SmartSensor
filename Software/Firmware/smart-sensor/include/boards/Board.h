#pragma once
/*
 * @file       : boards/Board.h
 * @description: This file contains the specific boards that have been created. It makes sure, the software
 *               is able to handel different hardware versions. In this file the interface and abstract class
 *               is available to be used. For every board, this abstract class should be inherited.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : -
 * @changes
 *  24-10-2021: MS: Added documentation. Added reset flags handling and reset cause for watchdog handling.
 *                  Added loop timing running average to get some filtering on the loop timing.
 */
#include <stdint.h>
#include <stdio.h>

#include <avr/pgmspace.h>

#include <tasks/Task.h>
#include <util/MessageBuffer.h>
#include <util/RTC.h>

/* Define the maximum tasks the board is able to run. */
#define SMARTSENSOR_MAX_TASKS 20

/* Define the amount of running average samples of the main loop timing calculation. */
#define SMARTSENSOR_RUNNING_AVERAGE_LOOP_TIME 5

/* The class SmartSensorBoard is the base class that is extended by the actual board class.
 * Within the main.c application, this base class is used, so no board specific aspects are
 * required by any main application functionality. It implements two interfaces. The first
 * interface is the SmartSensorMeasurement that is used to get measurement results from the
 * sensors. The RTCReadTimestampEvent is used to get the timestamp from the RTC chip.
 */
class SmartSensorBoard: public SmartSensorMeasurement, public RTCReadTimestampEvent {

protected:
    /* The id of the board that is used for identification with the back-end */
    char id[21];

    /* Reset cause is hold by this variable. */
    uint8_t resetCause;

    /* Total drivers that have been added to the board. */
    uint8_t totalDrivers;

    /* Drivers that have been added to the board. 20 drivers maximum */
    ITask* drivers[SMARTSENSOR_MAX_TASKS]; // Maybe later having a split in resources? Or a resources class that can.

    /* Holds the measurements that come back from the sensors. */
    MeasurementBuffer buffer;

    /* Holds the timestampe of the loop, so the total loop time can be calculated. */
    uint32_t loopTimstamp;

    /* Holds the total loop time in milliseconds. It shows how long the loop is taking. */
    uint16_t loopTime;

    /* Interface: RTCReadTimestampEvent
     * When the time has been read, this method is used to get the real time.
     */
    void rtcReadTimestampEvent(RTCTime& time, RTCEventMode mode);

    /* Protected constructor in order to create an singleton. */
    SmartSensorBoard(): totalDrivers(0) {}

public:
    /* Returns the board that has been compiled. It returns the single instance of this class. */
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

    /* These methods print messages to the serial port. */
    virtual void debug( const char* message) = 0;
    virtual void debugf( const char* message, ...);

    /* These method are able to use strings that are stored on flash in stead of memory. */
    virtual void debug_P( const char* message) = 0;
    virtual void debugf_P( const char* message, ...);

    /* Interface: SmartSensorMeasurement
     * Callback to provide measurement data from the sensors.
     */
    virtual void addMeasurement(const char* measurment) = 0;

    /* Returns the pointer to the char id of the SmartSensor. */
    virtual const char* getID() { return this->id; };

    /* Request a timestamp from the RTC. This method will be implemented by the concrete board. When
       the timestamp is retrieved the callback rtcReadTimestampEvent is called. */
    virtual void getActualTimestamp() = 0;

    /* Returns true when the reset cause is due a watch dog timeout. */
    bool resetCauseWatchdog ();
    
    /* Returns true when the reset cause is due an external reset. */
    bool resetCauseExternalReset ();
    
};
