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

#include <boards/SmartSensorMeasurement.h>

/* IDriver
 * The interface that implements the main methods required for a driver.
 */
class IDriver {

public:
    /* The setup method initializes the driver and the hardware that is driven. This method
       shoul be called once at the startup of the board. When the setup is successfull, the
       method returns 0, otherwise it returns an error number.
    */
    virtual int setup() = 0;    // "= 0" part makes this method pure virtual, and also makes this class abstract.

    /* The loop method handles the main functionality. This loop method shall not contain any blocking function
       calls. If you require delays, please use timing variables like millis(). So it is possible to
       maximize the CPU utilization! If successfull the method returns 0, otherwise it returns an error number.
    */
    virtual int loop(uint32_t millis) = 0;

    /* The reset method resets the driver and the underlying hardware. If successfull the
       method returns 0, otherwise it returns an error number.
    */
    virtual int reset() = 0;

    /* Put the hardware in low power consumption mode. */
    virtual int sleep() = 0;

    /* Wake the hardware from low power consumption mode. */
    virtual int wakeup() = 0;
};

/* Driver
 * The abstract class that implements base functionality of the driver.
 */
class Driver: public IDriver {
private:
    /* This flag indicates that the data from the hardware is valid and can be used. */
    bool dataValid;

    /* When a measurement becomes available, this information can be given to the responsible class. */
    SmartSensorMeasurement* cbMeasurement PROGMEM;

protected:
    /* Helper function to flag the data as invalid, so it should not be used by the main application. */
    void setDataInvalid();

    /* Helper function to flag the data as valid, so it can be used by the main application. */
    void setDataValid();

    ~Driver() {}

public:
    /* For drivers that do not contain any measurements this driver can be used. */
    Driver(): dataValid(false), cbMeasurement(NULL) {};

    /* For drivers that generate measurement, this constructor can be used. */
    Driver(SmartSensorMeasurement* cbMeasurement): dataValid(false), cbMeasurement(cbMeasurement) {};

    /* Returns wheter the data of this driver is valid. */
    bool isDataValid();

    SmartSensorMeasurement* getMeasurementCallback();
};
