#include "drivers/AnalogDriver.h"

uint8_t AnalogDriver::setup()
{
    this->sleeping = false;
    this->samplingAmount = 1;
    this->samplingInterval = 0;
    this->samplingTimestamp = 0;

    /* init ADC */
    if (this->analog_pin > MAX_ANALOG_PIN || this->analog_pin < 0)
    {
        SmartSensorBoard::getBoard()->debug_P("[AnalogDriver] ERROR! : selected pin invalid!");
        return -1;
    }
    DDRA &= ~(1 << this->analog_pin);
    ADCSRA |= 1 << ADEN; /* enable ADC */

    // /* prescaler of 128, Datasheet ATmega324PB page 306 */
    // ADCSRA |= 1 << ADPS2;
    ADCSRA |= 1 << ADPS1;
    ADCSRA |= 1 << ADPS0;

    PRR0 &= ~(1 << PRADC); /* write 0 to power reduction ADC bit, datasheet Atmega324P page 305 */

    ADMUX |= 1 << this->analog_pin;
    ADMUX |= 1 << REFS0;

    SmartSensorBoard::getBoard()->debug_P("[AnalogDriver] done init");

    return this->initialize();
}

uint32_t AnalogDriver::measure_analog_value()
{
    ADMUX &= ~(1 << this->analog_pin); /* set channel to selected pin */
    ADCSRA |= (1 << ADSC);             /* Start conversion */

    while ((ADCSRA & (1 << ADIF)) == 0)
        ; /* wait for conversion to complete */

    return ADC;
}

uint8_t AnalogDriver::loop(uint32_t millis)
{

    if (!this->sleeping)
    {
        if (millis - this->samplingTimestamp > this->samplingInterval)
        {
            this->samplingTimestamp = millis;
            return this->late_loop(millis);
        }
        return 0;
    }
    return 0;
    
}

uint8_t AnalogDriver::sleep()
{
    ADCSRA &= ~(1 << ADEN); /* disable ADC */

    this->sleeping = true;
    return this->late_sleep();
}

uint8_t AnalogDriver::reset()
{
    this->sleeping = false;
    ADCSRA |= 1 << ADEN; /* enable ADC */

    return this->late_reset();
}

uint8_t AnalogDriver::wakeup()
{
    ADCSRA |= 1 << ADEN; /* enable ADC */

    this->sleeping = false;
    return this->late_wakeup();
}