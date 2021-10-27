/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <boards/v1_2/Board.h>

#include <string.h>

#include <avr/boot.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

void SmartSensorBoardV1_2::setup() {
    BOARDV1_2_ADAPTER_IN_USE_DDR = BOARDV1_2_ADAPTER_IN_USE_DDR & ~(1 << BOARDV1_2_ADAPTER_IN_USE_PIN); // Set pin for adapter in use as input.

    this->timing = Timing::getInstance(); // TODO: We could calibrate the timer loop using the RTC!
    this->timing->setup();
    
    this->serial0 = Atmega324PBSerial0::getInstance();
    this->addTask(this->serial0, PSTR("Serial0"));

    this->serial1 = Atmega324PBSerial1::getInstance();
    this->addTask(this->serial1, PSTR("Serial1"));

    this->i2c0 = Atmega324PBI2C0::getInstance();
    this->addTask(this->i2c0, PSTR("I2C0"));

    this->ledDriver      = LedDriver::getInstance();
    this->addTask(this->ledDriver, PSTR("LedDriver"));

    this->shtc3Driver    = SHTC3Driver::getInstance(this);
    this->addTask(this->shtc3Driver, PSTR("SHTC3Driver"));

    this->mcp7940nDriver = MCP7940NDriver::getInstance(this);
    this->addTask(this->mcp7940nDriver, PSTR("MCP7940NDriver"));

    this->xbeeProS2CDriver = XBeeProS2C::getInstance();
    this->xbeeProS2CDriver->enableCoordinator(); // TODO: Must be switched on when adapter is in use and wemos is connected. Print it to the serial
    this->addTask(this->xbeeProS2CDriver, PSTR("XbeeProS2CDriver"));

    SmartSensorBoard::setup(); // Base class setup() when everything is loaded.

    this->debug_P(PSTR("Adapter: "));
    if ( this->adapterInUse() ) {
         this->debug_P(PSTR("Yes\n"));
    } else {
        this->debug_P(PSTR("No\n"));
    }

    this->debugf_P(PSTR("ID: %s\n"), this->getID());

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

// TODO: When the 
bool SmartSensorBoardV1_2::isGateway() {
    return false;
}

uint32_t SmartSensorBoardV1_2::millis() {
    return this->timing->millis();
}

void SmartSensorBoardV1_2::debug( const char* message) {
    this->serial0->print(message);
}

void SmartSensorBoardV1_2::debug_P( const char* message) {
    this->serial0->print_P(message);
}

void SmartSensorBoardV1_2::addMeasurement(const char* measurement) {
    this->debugf_P(PSTR("Measurement: %s\n"), measurement);
    this->buffer.addMeasurement(measurement);
}

// TODO:!
void SmartSensorBoardV1_2::addMessage(const char* message) {
    this->debugf_P(PSTR("Message: %s\n"), message);
}

const char* SmartSensorBoardV1_2::getID() {
    // Get the Atmege unique serial number
    for ( uint8_t i=0; i < 20; i=i+2 ) {
        uint8_t b = boot_signature_byte_get(0x0E + i); // 0x0E => SER0
        
        uint8_t h1 = (b & 0b0000'1111);
        uint8_t h2 = (b >> 4);

        // Convert to HEX
        this->id[20-i-1] = (char) (h1 < 10 ? h1+'0' : h1-10+'A');
        this->id[20-i-2] = (char) (h2 < 10 ? h2+'0' : h2-10+'A');
    }

    this->id[20] = '\0';

    return this->id;
}

void SmartSensorBoardV1_2::getActualTimestamp() {
    this->mcp7940nDriver->requestTime();
}

