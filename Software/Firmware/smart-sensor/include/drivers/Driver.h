#pragma once
/**
 * @file       : Driver.h
 * @description: The abstract base class for the drivers used by the SmartSensor. All drivers should use this class. This file
 *               uses the design approach that starts with interfaces that will be implemented by abstract and concrete classes.
 *               This method provides the interface IDriver and the base class Driver. A driver in this case almost looks like a
 *               task or thread.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 * @version    : 1.0
 * @changes
 *  24-10-2021: MS: Removed the data valid flag. Is not required anymore.
 * 
 */
#include <stddef.h>

#include <avr/pgmspace.h>

#include <util/Message.h>
#include <tasks/Task.h>

/* Driver
 * The abstract class that implements base functionality of the driver.
 */
class Driver: public Task {
private:
    /* When a measurement becomes available, this information can be given to the responsible class. */
    MessageInterface* messageInterface;

public:
    /* For drivers that do not contain any message this driver can be used. */
    Driver(): messageInterface(NULL) {};

    /* For drivers that generate measurement, this constructor can be used. */
    Driver(MessageInterface* messageInterface): messageInterface(messageInterface) {};

    MessageInterface* getMessageInterface() {
        return messageInterface;
    }

};
