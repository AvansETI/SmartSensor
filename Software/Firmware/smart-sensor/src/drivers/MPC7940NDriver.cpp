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
uint8_t MCP7940NDriver::setup() {
    MCP7940_MFP_DDR = MCP7940_MFP_DDR & ~(1 << MCP7940_MFP_PIN); // Set the MFP pin as input.

    if ( !this->isConnected() ) {
        return 1; // Cannot select the chip
    }

    // TODO: Finish the setup! Read the date

    return 0;
}

uint8_t MCP7940NDriver::loop(uint32_t millis) {
    // TODO
    return 0;
}

uint8_t MCP7940NDriver::reset() {
    // TODO
    return 0;
}

uint8_t MCP7940NDriver::sleep() {
    // TODO
    return 0;
}

uint8_t MCP7940NDriver::wakeup() {
    // TODO
    return 0;
}

bool MCP7940NDriver::isConnected() {

}

RTCTime MCP7940NDriver::getPowerDownTimestamp() {
    // TODO
    return RTCTime("20110101T10:10:10");
 }

// TODO: To be tested
RTCTime MCP7940NDriver::getTime() {
    return RTCTime("20110101T10:10:10");
}

void MCP7940NDriver::setTime(const RTCTime &t) {
    // TODO
}

void MCP7940NDriver::setTime(const char* iso8601) {
    RTCTime time(iso8601);
    this->setTime(time);
}
