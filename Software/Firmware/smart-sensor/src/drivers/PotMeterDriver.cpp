/**
 * @file       : PotMeterDriver.cpp
 * @date       : 12-5-2022
 * @author     : Sebastiaan Colijn
 * @description: This driver handles the measuring of data from a standard 10 k slide potentiometer
 * @version    : 0.2
 * @license    : GNU version 3.0
 * @todo       : 
 * 
 * @changes
 */

#include "drivers/PotMeterDriver.h"

uint8_t PotMeterDriver::initialize()
{
    this->analog_pin = 1; 
    this->samplingInterval = 300000; // 5 minute delay
    return 0;
}
uint8_t PotMeterDriver::late_loop(uint32_t millis)
{
    sample();
    return 0;
}
uint8_t PotMeterDriver::late_reset() 
{
    return 0;

}
uint8_t PotMeterDriver::late_sleep()
{
    return 0;

}
uint8_t PotMeterDriver::late_wakeup()
{
    return 0;

}

void PotMeterDriver::sample()
{
    this->lastMeasurement = this->measure_analog_value();
    //SmartSensorBoard::getBoard()->debugf_P(PSTR("[PotMeterDriver] : slider is %d of 1024\n"), lastMeasurement); //use for debugging via serial
    
    char message[30];
    sprintf_P(message, PSTR("pot:%u"), lastMeasurement);
    this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, message));
}