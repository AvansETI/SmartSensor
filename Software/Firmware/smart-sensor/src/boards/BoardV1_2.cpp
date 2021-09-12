#include <boards/BoardV1_2.h>

#include <avr/boot.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

void SmartSensorBoardV1_2::setup() {
    BOARDV1_2_ADAPTER_IN_USE_DDR = BOARDV1_2_ADAPTER_IN_USE_DDR & ~(1 << BOARDV1_2_ADAPTER_IN_USE_PIN); // Set pin for adapter in use as input.

    this->timer1.setup();

    this->addDriver(&this->ledDriver, PSTR("LedDriver"));
    this->addDriver(&this->shtc3Driver, PSTR("SHTC3Driver"));
    this->addDriver(&this->mcp7940nDriver, PSTR("MCP7940NDriver"));

    /* Show the user that we have started up, by one-second led on and then flash led. */
    this->ledDriver.led1On();
    _delay_ms(1000);
    this->ledDriver.led1Off();
    _delay_ms(1000);
    this->ledDriver.led1On();
    _delay_ms(100);
    this->ledDriver.led1Off();

    this->ledDriver.led1Flash(1000, 100);

    if ( this->adapterInUse() ) {
        this->debug(PSTR("Adapter is in use."));
    } else {
        this->debug(PSTR("Adapter is not in use"));
    }

    this->debugf(PSTR("SERIAL: %s"), this->getID() );

    sei(); // Enable the interrupts!
}

bool SmartSensorBoardV1_2::adapterInUse() {
    return ( ( BOARDV1_2_ADAPTER_IN_USE_PORT & (1 << BOARDV1_2_ADAPTER_IN_USE_PIN) ) != 0 );
}

uint32_t SmartSensorBoardV1_2::millis() {
    return this->timer1.millis();
}

void SmartSensorBoardV1_2::debug( const char* message) {

}

void SmartSensorBoardV1_2::addMeasurement(const char* measurement, ...) {
    char buffer[MEASUREMENT_TOTAL_CHARS];
    va_list args;
    va_start(args, measurement);
    vsprintf (buffer, measurement, args);
    va_end (args);

    this->debugf(PSTR("MEASUREMENT: %s"), buffer);
    this->buffer.addMeasurement(buffer);
}

char* SmartSensorBoardV1_2::getID() {


    //sprintf(id, PSTR("SHTC3-%04X"), this->shtc3Driver.getID()); // ID from the SHTC3 chip
    
    // Get the Atmege unique serial number
    for ( uint8_t i=0; i < 10; ++i ) {
        uint16_t value = boot_signature_byte_get(0x0E + i); // 0x0E => SER0 
        value          = (boot_signature_byte_get(0x0E + i + 1) << 4);
        
        char valueStr[2];
        sprintf(valueStr, PSTR("%02X"), value);

        id[(10-i)*2-1] = valueStr[1];
        id[(10-i)*2-2] = valueStr[0];
    }

    return id;
}

