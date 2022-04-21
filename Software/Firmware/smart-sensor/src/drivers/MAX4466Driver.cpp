/*
 * @file       : MAX4466Driver.cpp
 * @author     : Sem van der Hoeven
 * @license    : GNU version 3.0
 */

#include "drivers/MAX4466Driver.h"
#include <boards/Board.h>


uint8_t MAX4466Driver::setup()
{
    this->envelope = 0;
    this->sleeping = false;

    SmartSensorBoard::getBoard()->debug_P(PSTR("MAX4466 driver initialized!\n"));

    return 0;
}

uint8_t MAX4466Driver::reset()
{
    this->envelope = 0;
    this->sleeping = false;

    return 0;
}

uint8_t MAX4466Driver::loop(uint32_t millis)
{

    return 0;
}

uint8_t MAX4466Driver::sleep()
{
    this->sleeping = true;
    return 0;
}

uint8_t MAX4466Driver::wakeup()
{
    this->sleeping = false;
    return 0;
}