#pragma once
/**
 * @file       : MCP7940NDriver.h
 * @description: This driver handles all the aspects of the MCP7940N chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to hold the real date and time. When the power is shut down, this chip maintains the real date for
 *               about 5 days (calculated) using an 1F super cap. Furthermore, the MFP pin (interrupt) of the chip is connected
 *               to PB2 pin of the Atmega.
                 http://ww1.microchip.com/downloads/en/devicedoc/20005010f.pdf
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : Test, while it does not work at this moment!
 * @changes
 *  24-10-2021: MS: This class does not require a sampling interval. It should be queried when a timestamp is needed.
 *                  Some SRAM has been freed because of this.
 */
#include <stdint.h>

#include <avr/pgmspace.h>

#include <util/RTC.h>
#include <util/Util.h>
#include <tasks/Atmega324PBI2C0.h>
#include <drivers/Driver.h>

/* Define how the MFP pin is connected to the Atmega. */
#define MCP7940_MFP_PIN PB2
#define MCP7940_MFP_DDR DDRB
#define MCP7940_MFP_PORT PORTB

/* Address of the MCP7940N chip on the I2C bus */
constexpr uint8_t MCP7940_I2C_ADDRESS PROGMEM = 0xDE;

/* The organization of the data that comes from the I2C bus. */
enum MCP7940NData {
    SECONDS,
    MINUTES,
    HOURS,
    WEEKDAY,
    DAY,
    MONTH,
    YEAR,
};

enum MCP7940NFlags {
    TIME_GET_REQUESTED,
    TIME_SET_REQUESTED,
};

/* This class implements the driver for the MCP7940 RTC (real-time) chip. It implements the
 * interface I2CReadEvent to get the data from the I2C. 
 */
class MCP7940NDriver: public Driver, public I2CReadEvent {
private:
    /* The callback when a time has been retrieved from the chip. */
    RTCReadTimestampEvent* rtcEvent;

    /* Holds the data that has been retrieved from the I2C bus. */ 
    uint8_t data[7];

    /* The flags hold boolean information that is used by the class, see MCP7940NFlags. */
    uint8_t flags;

    /* Set the time. */
    void setTime();

protected:
    /* Protected constructor to create a singleton. */
    MCP7940NDriver(MessageInterface* messageInterface): Driver(messageInterface) { }

public:
    /* Returns the singleton instance. */
    static MCP7940NDriver* getInstance(MessageInterface* messageInterface) {
        static MCP7940NDriver _mcp7940NDriver(messageInterface);
        return &_mcp7940NDriver;
    }

    /* Interface: Task */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();
    
    /* TODO: Add POWER-DOWN/POWER-UP TIME-STAMP. Do we need this?  */
    // RTCTime getPowerDownTimestamp();

    /* The class is going to ask the RTC chip a new time. When available it calls the callback. */
    void requestTime();

    /* Set the time based on a RTCTimestamp instance of the chip. The I2C is used for this. */
    void setTime(const RTCTime &t);

    /* Set the time based on an ISO8601 string of the chip. */
    void setTime(const char* iso8601);

    /* Check whether the chip reacts on a I2C message. */
    bool isConnected();

    // Interface: I2CReadEvent
    void i2cReadEvent(uint8_t data, uint8_t index);

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

};

