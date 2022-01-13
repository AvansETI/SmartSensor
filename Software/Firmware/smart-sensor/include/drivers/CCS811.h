#pragma once
/**
 * @file       : VEML7700.h
 * @description: This driver handles all the aspects of the CCS811 chip.
 *               https://www.sciosense.com/wp-content/uploads/documents/SC-001232-DS-3-CCS811B-Datasheet-Revision-2.pdf
 * @date       : 09-01-2022
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 */
#include <drivers/Driver.h>

#include <math.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include <util/I2C.h>
#include <tasks/Atmega324PBI2C0.h>

#define CCS811_NWAKE_PIN  PD6
#define CCS811_NWAKE_DDR  DDRD
#define CCS811_NWAKE_PORT PORTD
#define CCS811_INT_PIN    PA7
#define CCS811_INT_DDR    DDRA
#define CCS811_INT_PORT   PORTA

/* Address of the SHTC3 chip on the I2C bus */
constexpr uint8_t CCS811_I2C_ADDRESS = 0xB4;

/* The enumeration that is used for the data array. */
enum CCS811Data {
    CO2_MSB,
    CO2_LSB,
    TVOC_MSB,
    TVOC_LSB,
    STATUS,
    ERROR_ID,
    RAW_MSB,
    RAW_LSB
};

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class CCS811Driver: public Driver, public I2CReadEvent {
private:
    /* The id of the SHTC3 chip. */
    uint16_t id;

    /* The data that is read from the I2C bus. */
    uint8_t data[8];

    /* Set the sampling interval of the sensor in seconds. */
    uint16_t samplingInterval;

    /* Busy indicates that sample process has been started and need to wait until the next cycle. */
    uint8_t busy;

    /* When the sampling could not occur due to a busy I2C bus, this flag becomes true. */
    bool waitingOnI2C; 

protected:
    /* Protected constructor to create a singleton. */
    CCS811Driver(MessageInterface* messageInterface): Driver(messageInterface), id(0), waitingOnI2C(false) {};

    /* Check whether the SHTC3 is connected to the I2C bus on the specific address. */
    bool isConnected();

    uint8_t setMode(uint8_t mode);


public:
    /* Get the instance of the singleton. */
    static CCS811Driver* getInstance(MessageInterface* messageInterface) {
        static CCS811Driver _ccs811Driver(messageInterface);
        return &_ccs811Driver;
    }

    /* Interface: Task */
    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    /* Check the checksum of the returned values to determine the correctness of data transfer. */
    static bool checkChecksum(uint16_t data, uint8_t checksum);

    /* Execute a sample from the SHTC3. In this case the I2C is used. */
    uint8_t sample();

    /* Set the required sampling interval in seconds that this sensor needs to be sampled. */
    void setSamplingInterval(uint16_t samplingInterval) { this->samplingInterval = samplingInterval; }

    /* Interface: I2CReadEvent */
    void i2cReadEvent(uint8_t data, uint8_t index);

    void lowWakePin();
    void highWakePin();

    uint16_t getCO2Data();
    uint16_t getTVOCData();

    uint8_t appStart();

};
