#include <boards/BoardV1_2.h>

#include <avr/boot.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>

void SmartSensorBoardV1_2::setup() {
    BOARDV1_2_ADAPTER_IN_USE_DDR = BOARDV1_2_ADAPTER_IN_USE_DDR & ~(1 << BOARDV1_2_ADAPTER_IN_USE_PIN); // Set pin for adapter in use as input.

    this->timer1 = Timer1::getInstance(); // TODO: Calibrate the timer loop using the RTC!
    this->timer1->setup();
    
    this->serial0 = Serial0::getInstance();
    this->serial0->setup();

    this->i2c0 = I2C0::getInstance();
    this->i2c0->setup();

    this->shtc3Driver    = SHTC3Driver::getInstance(this);
    this->ledDriver      = LedDriver::getInstance();
    this->mcp7940nDriver = MCP7940NDriver::getInstance(this);

    this->addDriver(this->mcp7940nDriver, PSTR("MCP7940NDriver"));
    this->addDriver(this->ledDriver, PSTR("LedDriver"));
    this->addDriver(this->shtc3Driver, PSTR("SHTC3Driver"));

    SmartSensorBoard::setup(); // Base class setup() when everything is loaded.

    if ( this->adapterInUse() ) {
        this->debug_P(PSTR("Adapter is in use.\n"));
    } else {
        this->debug_P(PSTR("Adapter is not in use.\n"));
    }

    //RTCTime r = RTCTime(21, 9, 16, 4, 0, 24, 0);
    //this->mcp7940nDriver->setTime(r);
    //_delay_ms(1000);

    char iso8601[25];
    RTCTime time = this->mcp7940nDriver->getRTCTime();
    time.getIso8601String(iso8601);
    this->debugf_P(PSTR("ID: %s\n"), this->getID());
    this->debugf_P(PSTR("Timestamp: %s\n"), iso8601 );

    /* Show the user that we have started up, by one-second led on and then flash led. */
    this->ledDriver->led1On();
    _delay_ms(1000);
    this->ledDriver->led1Off();
    _delay_ms(1000);
    this->ledDriver->led1On();
    _delay_ms(100);
    this->ledDriver->led1Off();

    this->ledDriver->led1Flash(5'000, 100);

    sei(); // Enable the interrupts!
}

bool SmartSensorBoardV1_2::adapterInUse() {
    return ( ( BOARDV1_2_ADAPTER_IN_USE_PORT & (1 << BOARDV1_2_ADAPTER_IN_USE_PIN) ) != 0 );
}

uint32_t SmartSensorBoardV1_2::millis() {
    return this->timer1->millis();
}

void SmartSensorBoardV1_2::debug( const char* message) {
    this->serial0->print(message);
}

void SmartSensorBoardV1_2::debug_P( const char* message) {
    this->serial0->print_P(message);
}

void SmartSensorBoardV1_2::addMeasurement(const char* measurement) {
    this->buffer.addMeasurement(measurement);
}

char* SmartSensorBoardV1_2::getID() {
    // Get the Atmege unique serial number
    for ( uint8_t i=0; i < 20; i=i+2 ) {
        uint8_t b = boot_signature_byte_get(0x0E + i); // 0x0E => SER0
        
        uint8_t h1 = (b & 0b0000'1111);
        uint8_t h2 = (b >> 4);

        // Convert to HEX
        this->id[20-i-1]   = (char) (h1 < 10 ? h1+'0' : h1-10+'A');
        this->id[20-i-2] = (char) (h2 < 10 ? h2+'0' : h2-10+'A');
    }

    this->id[20] = '\0';

    return this->id;
}

