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

void SmartSensorBoardV1_2::setup()
{
    BOARDV1_2_ADAPTER_IN_USE_DDR = BOARDV1_2_ADAPTER_IN_USE_DDR & ~(1 << BOARDV1_2_ADAPTER_IN_USE_PIN); // Set pin for adapter in use as input.

    this->timing = Timing::getInstance(); // TODO: We could calibrate the timer loop using the RTC!
    this->timing->setup();

    this->serial0 = Atmega324PBSerial0::getInstance();
    this->addTask(this->serial0, PSTR("Serial0"));

    this->serial1 = Atmega324PBSerial1::getInstance();
    this->addTask(this->serial1, PSTR("Serial1"));

    this->debugf_P(PSTR("Reset cause: %d\n"), this->resetCause);

    this->i2c0 = Atmega324PBI2C0::getInstance();
    this->addTask(this->i2c0, PSTR("I2C0"));

    this->ledDriver = LedDriver::getInstance();
    this->addTask(this->ledDriver, PSTR("LedDriver"));

    this->shtc3Driver = SHTC3Driver::getInstance(this);
    this->addTask(this->shtc3Driver, PSTR("SHTC3Driver"));

    this->mcp7940nDriver = MCP7940NDriver::getInstance(this);
    this->addTask(this->mcp7940nDriver, PSTR("MCP7940NDriver"));

    this->vml7700Driver = VEML7700Driver::getInstance(this);
    this->addTask(this->vml7700Driver, PSTR("VEML7700Driver"));

    this->ccs811Driver = CCS811Driver::getInstance(this); // When enabled, the sensor starts twice, something goes wrong? Watchdog?
    this->addTask(this->ccs811Driver, PSTR("CCS811Driver"));

    this->xbeeProS2CDriver = XBeeProS2C::getInstance(this);
    if (this->adapterInUse())
    {                                                // The test has the node at the power and the coordinator to the computer.
        SmartSensorBoard::getBoard()->debug_P(PSTR("coordinator\n"));
        this->xbeeProS2CDriver->enableCoordinator(); // TODO: Must be switched on when adapter is in use and wemos is connected. Print it to the serial
    }
    this->addTask(this->xbeeProS2CDriver, PSTR("XbeeProS2CDriver"));

    this->max4466Driver = MAX4466Driver::getInstance(this, this);
    this->addTask(this->max4466Driver, PSTR("MAX4466Driver"));

    SmartSensorBoard::setup(); // Base class setup() when everything is loaded.

    this->debug_P(PSTR("Adapter: "));
    if (this->adapterInUse())
    {
        this->debug_P(PSTR("Yes\n"));
    }
    else
    {
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

    if (this->isGateway())
    {
        this->ledDriver->led1Flash(5'000, 2'500);
    }
    else
    {
        this->ledDriver->led1Flash(5'000, 100);
    }

    sei(); // Enable the interrupts!

    this->serial0->setCallback(this);
}

bool SmartSensorBoardV1_2::adapterInUse()
{
    return ((BOARDV1_2_ADAPTER_IN_USE_PORT & (1 << BOARDV1_2_ADAPTER_IN_USE_PIN)) != 0);
}

// TODO: When the
bool SmartSensorBoardV1_2::isGateway()
{
    return false;
}

uint32_t SmartSensorBoardV1_2::millis()
{
    return this->timing->millis();
}

void SmartSensorBoardV1_2::debug(const char *message)
{
    this->serial0->print(message);
}

void SmartSensorBoardV1_2::debug_P(const char *message)
{
    this->serial0->print_P(message);
}

const char *SmartSensorBoardV1_2::getID()
{
    // Get the Atmege unique serial number
    for (uint8_t i = 0; i < 20; i = i + 2)
    {
        uint8_t b = boot_signature_byte_get(0x0E + i); // 0x0E => SER0

        uint8_t h1 = (b & 0b0000'1111);
        uint8_t h2 = (b >> 4);

        // Convert to HEX
        this->id[20 - i - 1] = (char)(h1 < 10 ? h1 + '0' : h1 - 10 + 'A');
        this->id[20 - i - 2] = (char)(h2 < 10 ? h2 + '0' : h2 - 10 + 'A');
    }

    this->id[20] = '\0';

    return this->id;
}

void SmartSensorBoardV1_2::getActualTimestamp()
{
    this->mcp7940nDriver->requestTime();
}

void SmartSensorBoardV1_2::setActualTimestamp(const RTCTime &time)
{
    this->mcp7940nDriver->setTime(time);
}

uint8_t SmartSensorBoardV1_2::sendDataString(const char *data)
{
    return this->serial0->printAsync(data);
}

uint8_t SmartSensorBoardV1_2::sendDataString_P(const char *data)
{
    return this->serial0->printAsync_P(data);
}

uint8_t SmartSensorBoardV1_2::sendDataStringAvailable()
{
    return !this->serial0->isBusy();
}

uint8_t SmartSensorBoardV1_2::waitOnSendDataStringAvailable() {
    while (this->serial0->isBusy()) {}
    
    return 0;
}

uint8_t SmartSensorBoardV1_2::processCommand(const char *data)
{
    // Process the command!
    return 0;
}

void SmartSensorBoardV1_2::recievedCharacter(char c)
{
    if (c != '\n')
    {
        this->serialBuffer.add(c);
    }
    else
    {
        this->addMessage(Message(MessageType::COMMAND, this->serialBuffer.get()));
        this->serialBuffer.reset();
    }
}

void SmartSensorBoardV1_2::sendInitMessage()
{
    /* This board is capable of the following:
    - Mode 0, but capable of mode 1 (development)
    - Measurements: Temperature, Humidity, Light, CO2, GPIO_STATUS, ANALOG_INPUT, RS232_RECEIVED
    - Actuators: BOOT_MODE, GPIO_SETUP, GPIO_OUTPUT, RS232_SEND

    Init message looks like:
    - INIT:<ID>:<NAME>\n
    - MEASUREMENTS:loop_time (lt), temperature (te), humidity (hu), ligth (li), co2 (c2), GPIO_STATUS (gi), ANALOG_INPUT (ai), RS232_REC (rs)\n
    - ACTUATORS:BOOT_MODE(bm), GPIO_SETUP (gs), GPIO_OUTPUT (go), RS232_SEND (rs)

    Note: Select the correct channel to send the data!
    */

    char message[MESSAGE_LENGTH + 20];

    sprintf_P(message, PSTR("INIT:%s:smartnode-v1-2\n"), this->getID());
    this->serial0->print(message);

    sprintf_P(message, PSTR("MEA:%s:lt:te:hu:li:c2:gi:ai:rs\n"), this->getID());
    this->serial0->print(message);

    sprintf_P(message, PSTR("ACT:%s:bm:gs:go:rs\n"), this->getID());
    this->serial0->print(message);

    sprintf_P(message, PSTR("END:%s\n"), this->getID());
    this->serial0->print(message);
}

void SmartSensorBoardV1_2::addXBeeMessage(Message message)
{
    this->xbeeProS2CDriver->addMessageForTransfer(message);
#if BOARDV1_2_XBEE_DEBUG_LED == 1
    this->ledDriver->led1On();
    _delay_ms(100);
    this->ledDriver->led1Off();
#endif
}

void SmartSensorBoardV1_2::addMessage(Message message)
{
#if BOARDV1_2_XBEE_SEND_ALL_MSGS == 1
    this->addXBeeMessage(message);
#endif
    this->queueMessages.add(message);
}
