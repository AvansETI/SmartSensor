#include <boards/BoardV1_2.h>

#include <avr/io.h>
#include <util/delay.h>

void SmartSensorBoardV1_2::setup() {
    this->addDriver(&this->ledDriver);
    this->addDriver(&this->shtc3Driver);

    SmartSensorBoard::setup(); // Call the derived class to perform the rest of the setup.

    /* Show the user that we have started up, by one-second led on and then flash led. */
    this->ledDriver.led1On();
    _delay_ms(1000);
    this->ledDriver.led1Off();
    _delay_ms(1000);
    this->ledDriver.led1On();
    _delay_ms(100);
    this->ledDriver.led1Off();
}
