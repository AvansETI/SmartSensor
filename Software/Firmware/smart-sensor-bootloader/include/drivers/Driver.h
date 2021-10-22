#pragma once
/**
 * @file       : Driver.h
 * @description: The abstract base class for the drivers used by the SmartSensor. All drivers should use this class. This file
 *               uses the design approach that starts with interfaces that will be implemented by abstract and concrete classes.
 *               This method provides the interface IDriver and the base class Driver. A driver in this case almost looks like a
 *               task or thread.
 * @date       : 10-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @updates
 * 
 */
#include <stddef.h>
#include <avr/pgmspace.h>

#include <util/MessageBuffer.h>
#include <tasks/Task.h>

/* Driver
 * The abstract class that implements base functionality of the driver.
 */
class Driver: public Task {
private:
    /* This flag indicates that the data from the hardware is valid and can be used. */
    bool dataValid;

    /* When a measurement becomes available, this information can be given to the responsible class. */
    SmartSensorMeasurement* cbMeasurement;

protected:
    /* Helper function to flag the data as invalid, so it should not be used by the main application. */
    void setDataInvalid();

    /* Helper function to flag the data as valid, so it can be used by the main application. */
    void setDataValid();

public:
    /* For drivers that do not contain any measurements this driver can be used. */
    Driver(): dataValid(false), cbMeasurement(NULL) {};

    /* For drivers that generate measurement, this constructor can be used. */
    Driver(SmartSensorMeasurement* cbMeasurement): dataValid(false), cbMeasurement(cbMeasurement) {};

    /* Returns wheter the data of this driver is valid. */
    bool isDataValid();

    SmartSensorMeasurement* getMeasurementCallback();
};
