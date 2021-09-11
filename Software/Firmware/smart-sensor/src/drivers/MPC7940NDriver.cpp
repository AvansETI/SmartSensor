#include "drivers/MCP7940NDriver.h"


/* for the setup
bit 4 PWRFAIL: Power Failure Status bit(1,2)
1 = Primary power was lost and the power-fail time-stamp registers have been loaded (must be
cleared in software). Clearing this bit resets the power-fail time-stamp registers to ‘0’.
0 = Primary power has not been lost
bit 3 VBATEN: External Battery Backup Supply (VBAT) Enable bit
1 = VBAT input is enabled
0 = VBAT input is disabled
*/
int MCP7940NDriver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the chip
    }

    // TODO: Finish the setup! Read the date

    return 0;
}

int MCP7940NDriver::loop() {
    // TODO
    return 0;
}

int MCP7940NDriver::reset() {
    // TODO
    return 0;
}

int MCP7940NDriver::sleep() {
    // TODO
    return 0;
}

int MCP7940NDriver::wakeup() {
    // TODO
    return 0;
}

bool MCP7940NDriver::isConnected() {
  TWI2_0.enable();
  TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
  const bool able_to_select = TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.stop();
  TWI2_0.disable();
  return able_to_select;
}

 RTCTime MCP7940NDriver::getPowerDownTimestamp() {
    // TODO
    return RTCTime("20110101T10:10:10");
 }

// TODO: To be tested
RTCTime MCP7940NDriver::getTime() {
    constexpr uint8_t masks[7] = {0b0111'1111, 0b0111'1111, 0b0001'1111, 0b0000'0011, 0b0011'1111, 0b0001'1111, 0b1111'1111};
    uint8_t raw[7];

    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_RTC_ADDRESS).wait().get(); // MS: Blocking!
    TWI2_0.write(0x00).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
    for (uint8_t i = 0; i < 7; ++i)
        raw[i] = convertFromBcd(*(i != 6 ? TWI2_0.read_ack() : TWI2_0.read_nack()).wait().get() & masks[i]);
    TWI2_0.stop();
    TWI2_0.disable();

    RTCTime time(raw[0], raw[1], raw[2], raw[3], raw[4], raw[5], raw[6]);

    return time;
}

void MCP7940NDriver::setTime(const RTCTime &t) {
    // TODO
}

void MCP7940NDriver::setTime(const char* iso8601) {
    RTCTime time(iso8601);
    this->setTime(time);
}

uint8_t MCP7940NDriver::convertToBcd(uint8_t byteDecimal) {
  return (byteDecimal / 10) << 4 | (byteDecimal % 10);
}

uint8_t MCP7940NDriver::convertFromBcd(uint8_t byteBCD) {
  uint8_t byteMSB = 0;
  uint8_t byteLSB = 0;

  byteMSB = (byteBCD & 0b1111'0000) >> 4;
  byteLSB = (byteBCD & 0b0000'1111);

  return ((byteMSB * 10) + byteLSB);
}
