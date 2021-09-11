#pragma once
/**
 * @file       : MCP7940NDriver.h
 * @description: This driver handles all the aspects of the MCP7940N chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to hold the real date and time. When the power is shut down, this chip maintains the real date for
 *               about 5 days (calculated) using an 1F super cap. Furthermore, the MFP pin (interrupt) of the chip is connected
 *               to PB2 pin of the Atmega.
                 http://ww1.microchip.com/downloads/en/devicedoc/20005010f.pdf
 * @date       : 10-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : The loop contains blocking function calls!
 * @updates
 * 
 */
#include <stdint.h>

#include <drivers/Driver.h>
#include <util/RTC.h>

#include <board-support/drivers/TWIDriver2.h>

/* Define how the MFP pin is connected to the Atmega. */
#define MCP7940_MFP_PIN PB2;
#define MCP7940_MFP_PORT PORTB;

/* Address of the MCP7940N chip on the I2C bus */
constexpr uint8_t MCP7940_I2C_ADDRESS = 0xDE;

class MCP7940NDriver: public Driver {
public:
    int setup();
    int loop();
    int reset();
    int sleep();
    int wakeup();
    
    /* Add POWER-DOWN/POWER-UP TIME-STAMP */
    RTCTime getPowerDownTimestamp();

    /* Returns the current time from the chip. */
    RTCTime getTime();

    /* Set the time based on a RTCTimestamp instance of the chip. */
    void setTime(const RTCTime &t);

    /* Set the time based on an ISO8601 string of the chip. */
    void setTime(const char* iso8601);

    /* Check whether the chip reacts on a I2C message. */
    bool isConnected();

    // TODO: Design and implement how the alarm should work?!

    // Add enableAlarm function to set the alarm and interrupt
    // Add disableAlarm function to unset the alarm and interrupt
    // Set callback eventAlarm function using an interface class RTCAlarmEvent(), it is called when the alarm flag is enable
    //   => Set the option to use interrupts of callback function.
    
    // TODO: Design and implement how the SRAM could be used?!

    /*The MCP7940N has 64 bytes of SRAM for general purpose usage. It is retained when the primary power
supply is removed if a backup supply is present and
enabled.
Although the SRAM is a separate block from the RTCC
registers, they are accessed using the same control
byte, ‘1101111X’.*/
    // Add setByte, getByte to use the SRAM of the chip, storing things to remember?

private:
    
};

