/*
 * @file       : MAX4466Driver.cpp
 * @author     : Sem van der Hoeven
 * @license    : GNU version 3.0
 */

#include "drivers/MAX4466Driver.h"

uint8_t MAX4466Driver::setup()
{
    /* Set the MAX4466 pin as input, set data direction register for a0 to input (see datasheet 13.2.3 page 60) */
    MAX4466_DDR = MAX4466_DDR & ~(1 << MAX4466_PIN);

    /* Init ADC */
    // MAX4466_DDR = 0;
    ADCSRA |= 1 << ADEN; /* enable ADC */

    PRR0 &= ~(1 << PRADC); /* write 0 to power reduction ADC bit, datasheet page 305 */

    ADMUX &= 1 << MUX0; /* enable ADC 0, datasheet page 304*/
    

    this->envelope = 0;
    this->sleeping = false;
    this->samplingInterval = MAX4466_SAMPLING_INTERVAL; /* 1 second interval */
    this->samplingTimestamp = 0;
    this->samplingAmount = 1; 

    this->debug_println("Initialized");

    return 0;
}

uint8_t MAX4466Driver::reset()
{

    this->envelope = 0;
    this->sleeping = false;
    this->samplingInterval = MAX4466_SAMPLING_INTERVAL; /* 1 second interval */
    this->samplingTimestamp = 0;
    this->samplingAmount = 1;
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
        return 0;
    }
    return 0;
}

uint8_t MAX4466Driver::sleep()
{
    ADCSRA &= ~(1 << ADEN); /* disable ADC */

    this->sleeping = true;
    return 0;
}

uint8_t MAX4466Driver::wakeup()
{
    ADCSRA |= 1 << ADEN; /* enable ADC */

    this->sleeping = false;
    return 0;
}

uint8_t MAX4466Driver::sample()
{

    int average = 0;
    for (uint8_t i = 0; i < this->samplingAmount; i++)
    {
        uint32_t measurement = take_measurement();
        average += measurement;
    }
    this->envelope = (int)((float)average / this->samplingAmount);
    SmartSensorBoard::getBoard()->debugf_P(PSTR("[MAX4466] : envelope is %d\n"), this->envelope);

    return 0;
}

uint32_t MAX4466Driver::take_measurement() 
{

    ADCSRA |= 1 << ADSC; /* Start conversion */

    while((ADCSRA & (1 << ADSC)) == 1) 
    {
        /* wait for conversion to complete */
    }

    uint32_t result =  ADCL;
    return result;
}

void MAX4466Driver::debug_println(const char *message)
{
    SmartSensorBoard::getBoard()->debug("[MAX4466] : ");
    SmartSensorBoard::getBoard()->debug(message);
    SmartSensorBoard::getBoard()->debug("\n");
}
