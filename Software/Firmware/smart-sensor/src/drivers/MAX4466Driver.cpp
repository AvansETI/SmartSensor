/*
 * @file       : MAX4466Driver.cpp
 * @author     : Sem van der Hoeven
 * @license    : GNU version 3.0
 */

#include "drivers/MAX4466Driver.h"

uint8_t MAX4466Driver::setup()
{
    /* Set the MAX4466 pin as input, set data direction register for a0 to input (see datasheet 13.2.3 page 60) */
    // MAX4466_ENVELOPE_DDR = MAX4466_ENVELOPE_DDR & ~(1 << MAX4466_ENVELOPE_PIN);

    this->envelope = 0;
    this->sleeping = false;
    this->samplingInterval = 1000 * 1; /* 1 second interval */
    this->samplingTimestamp = 0;
    this->samplingAmount = 10; /*Take 10 measurements*/

    this->debug_println("Initialized");

    return 0;
}

uint8_t MAX4466Driver::reset()
{
    this->envelope = 0;
    this->sleeping = false;
    this->samplingInterval = 1000 * 1; /* 1 second interval */
    this->samplingTimestamp = 0;

    return 0;
}

uint8_t MAX4466Driver::loop(uint32_t millis)
{

    if (!this->sleeping)
    {
        if (millis - this->samplingTimestamp > this->samplingInterval)
        {
            this->samplingTimestamp = millis;

            this->sample();
        }
    }
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

uint8_t MAX4466Driver::sample()
{

    int average = 0;
    for (int i = 0; i < this->samplingAmount; i++)
    {
        this->debug_println("sampling! (not doing anything yet but eh)");
    }

    return 0;
}

void MAX4466Driver::debug_println(const char *message)
{
    SmartSensorBoard::getBoard()->debug("[MAX4466] : ");
    SmartSensorBoard::getBoard()->debug(message);
    SmartSensorBoard::getBoard()->debug("\n");
}
