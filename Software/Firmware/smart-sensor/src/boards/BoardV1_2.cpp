#include <boards/BoardV1_2.h>

#include <avr/io.h>
#include <util/delay.h>

void SmartSensorBoardV1_2::setup() {
    BOARDV1_2_ADAPTER_IN_USE_DDR = BOARDV1_2_ADAPTER_IN_USE_DDR & ~(1 << BOARDV1_2_ADAPTER_IN_USE_PIN); // Set pin for adapter in use as input.

    this->addDriver(&this->ledDriver, "LedDriver");
    this->addDriver(&this->shtc3Driver, "SHTC3Driver");
    this->addDriver(&this->mcp7940nDriver, "MCP7940NDriver");

    /* Show the user that we have started up, by one-second led on and then flash led. */
    this->ledDriver.led1On();
    _delay_ms(1000);
    this->ledDriver.led1Off();
    _delay_ms(1000);
    this->ledDriver.led1On();
    _delay_ms(100);
    this->ledDriver.led1Off();
}

// When millis is correctly implemented remove this!
void SmartSensorBoardV1_2::loop() {
    this->_millis++;
    SmartSensorBoard::loop(); // call the parent
}

bool SmartSensorBoardV1_2::adapterInUse() {
    return ( ( BOARDV1_2_ADAPTER_IN_USE_PORT & (1 << BOARDV1_2_ADAPTER_IN_USE_PIN) ) != 0 );
}

uint32_t SmartSensorBoardV1_2::millis() {
    return this->_millis;
}

void SmartSensorBoardV1_2::debug( const char* message) {

}

void SmartSensorBoardV1_2::addMeasurement(const char* measurement, ...) {
    char buffer[MEASUREMENT_TOTAL_CHARS];
    va_list args;
    va_start(args, measurement);
    vsprintf (buffer, measurement, args);
    va_end (args);

    this->debugf("MEASUREMENT: %s", buffer); // Save this measurement in some array
    this->buffer.addMeasurement(buffer);
}
