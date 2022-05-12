/**
 * @file       : PotMeterDriver.cpp
 * @date       : 28-4-2022
 * @author     : Sebastiaan Colijn
 * @description: This driver handles the measuring of data from a standard 10 k slide potentiometer
 * @version    : 0.1
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 */

#include "drivers/PotMeterDriver.h"

uint8_t PotMeterDriver::setup()
{
    //Enable ADC
    ADCSRA = ADCSRA | 1 << ADEN;
    this->samplingInterval = 10; //time in seconds
    this->samplingTimestamp = 0;

//
    return 0;
}
uint8_t PotMeterDriver::loop(uint32_t millis)
{
    //if timer has passed, start conversion
    //if conversion is ongoing, do nothing
    //if conversion has finished, retrieve results

    if ( this->samplingTimestamp == 0 ) {
        this->samplingTimestamp = millis/1000;
    }

    if (!isMeasuring && (millis/1000) - this->samplingTimestamp > this->samplingInterval ) {
        this->samplingTimestamp = millis/1000;
        this->measure(); 
    }

    if(isMeasuring && (ADCSRA & 1 << ADSC == 1 << ADSC))
    {
        isMeasuring = false;
        // TODO disable interrupt for safety while reading 2 registers in sequence

        //read adcl
        uint8_t low = ADCL;
        //read adch
        uint8_t high = ADCH;

        //TODO reenable interrupt   

        //combine bytes into 16-bit value
        uint16_t result = ADCH << 8;
        result = result | ADCL;
        //send message with result in it

        char m[30];

        sprintf_P(m, PSTR("pot:%d"), result);

        this->getMessageInterface()->addMessage(Message(MessageType::MEASUREMENT, m));

    }



    return 0;

}
uint8_t PotMeterDriver::reset() 
{
    return 0;

}
uint8_t PotMeterDriver::sleep()
{
    return 0;

}
uint8_t PotMeterDriver::wakeup()
{
    return 0;

}

void PotMeterDriver::measure()
{
    ADMUX = 1 << MUX0;    //set ADC channel to 0, Ref = AREF, Internal Vref turned off, Results is Right Adjusted
    PRR0 = PRR0 | 1 << PRADC; //set Power Reduction bit
    ADCSRA = ADCSRA | 1 << ADSC; // set Start Conversion bit
    isMeasuring = true;
}

