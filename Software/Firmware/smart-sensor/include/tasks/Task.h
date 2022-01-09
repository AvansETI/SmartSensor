#pragma once
/**
 * @file       : Task.h
 * @description: The abstract base class for tasks runned by the SmartSensor board. All tasks should use this class. This file
 *               uses the design approach that starts with interfaces that will be implemented by abstract and concrete classes.
 *               This method provides the interface ITask and the base class Task.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @changes
 */
#include <stddef.h>
#include <avr/pgmspace.h>

/* Interface: ITask
 * The interface that implements the main methods required for a task.
 */
class ITask {

public:
    /* The abstract setup method initializes the task. This method should be called once at the startup of the board.
       When the setup is successfull, the method returns 0, otherwise it returns an error number. The error numbers 
       should be documented in the concrete task that implements this setup.
    */
    virtual uint8_t setup() = 0;

    /* The abstract loop method handles the main functionality. This loop method shall not contain any blocking function
       calls. If you require delays, please use timing variable millis. Using this strategy the CPU performance is
       maximized. If successfull the method returns 0, otherwise it returns an error number. The error numbers should be
       documented in the concrete task that implements this loop.
    */
    virtual uint8_t loop(uint32_t millis) = 0;

    /* The abstract reset function resets the task. If successfull the method returns 0, otherwise it returns an error
       number.
    */
    virtual uint8_t reset() = 0;

    /* Put the task to sleep and if possible in low power consumption mode. */
    virtual uint8_t sleep() = 0;

    /* Awake the task so it runs again. */
    virtual uint8_t wakeup() = 0;
};

/* Class: Task
 * The abstract class that implements base functionality of the driver.
 */
class Task: public ITask {
public:
    /* For drivers that do not contain any measurements this driver can be used. */
    Task() {};
};
