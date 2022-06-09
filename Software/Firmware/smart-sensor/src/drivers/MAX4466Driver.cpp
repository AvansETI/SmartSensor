/*
 * @file       : MAX4466Driver.cpp
 * @author     : Sem van der Hoeven
 * @license    : GNU version 3.0
 */

#include "drivers/MAX4466Driver.h"

uint8_t MAX4466Driver::initialize()
{
    /* enable ADC 0, datasheet Atmega324P page 304*/
    this->analog_pin = 0;
    this->envelope = 0;
    this->samplingInterval = MAX4466_SAMPLING_INTERVAL; /* 5 seconds interval */
    this->samplingTimestamp = 0;
    this->samplingAmount = MAX4466_SAMPLING_AMOUNT;

    this->debug_println("Initialized");

    return 0;
}

uint8_t MAX4466Driver::late_reset()
{

    this->envelope = 0;
    this->samplingInterval = MAX4466_SAMPLING_INTERVAL; /* 1 second interval */
    this->samplingTimestamp = 0;
    this->samplingAmount = MAX4466_SAMPLING_AMOUNT;
    return 0;
}

uint8_t MAX4466Driver::late_loop(uint32_t millis)
{

    int average = 0;
    for (uint8_t i = 0; i < this->samplingAmount; i++)
    {
        uint32_t measurement = this->measure_analog_value();
        average += measurement;
    }
    this->envelope = (int)((float)average / this->samplingAmount);

    // send the message over zigbee
    char message[15];
    sprintf_P(message, PSTR("so:%d"), this->envelope);
    this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, message));
    this->debug_println("add xbee msg");

    return 0;
}

uint8_t MAX4466Driver::late_sleep()
{
    return 0;
}

uint8_t MAX4466Driver::late_wakeup()
{
    return 0;
}

void MAX4466Driver::debug_println(const char *message)
{
#if DEBUG_MODE == 1
    SmartSensorBoard::getBoard()->debug("[MAX4466] : ");
    SmartSensorBoard::getBoard()->debug(message);
    SmartSensorBoard::getBoard()->debug("\n");
#endif
}
