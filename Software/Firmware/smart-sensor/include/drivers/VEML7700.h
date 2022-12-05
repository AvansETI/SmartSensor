#pragma once
/**
 * @file       : VEML7700.h
 * @description: This driver handles all the aspects of the VEML700 chip.
 *               https://www.vishay.com/docs/84286/veml7700.pdf
 * @date       : 09-01-2022
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 */
#include <drivers/Driver.h>

#include <math.h>
#include <avr/pgmspace.h>

#include <util/I2C.h>
#include <tasks/Atmega324PBI2C0.h>

#define VEML7700_GAIN_1   0x00   // ALS gain 1x
#define VEML7700_GAIN_2   0x01   // ALS gain 2x
#define VEML7700_GAIN_1_8 0x02   // ALS gain 1/8x
#define VEML7700_GAIN_1_4 0x03   // ALS gain 1/4x

/* Address of the SHTC3 chip on the I2C bus */
constexpr uint8_t VEML7700_I2C_ADDRESS = 0x20;

/* The enumeration that is used for the data array. */
enum VEML7700Data {
    ALS_LSB,
    ALS_MSB,
};

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class VEML7700Driver: public Driver, public I2CReadEvent {
private:
    /* The id of the SHTC3 chip. */
    uint16_t id;

    /* The data that is read from the I2C bus. */
    uint8_t data[2];

    /* Set the sampling interval of the sensor in seconds. */
    uint16_t samplingInterval;

    /* Busy indicates that sample process has been started and need to wait until the next cycle. */
    uint8_t busy;

    /* When the sampling could not occur due to a busy I2C bus, this flag becomes true. */
    bool waitingOnI2C; 

protected:
    /* Protected constructor to create a singleton. */
    VEML7700Driver(MessageInterface* messageInterface): Driver(messageInterface), id(0), waitingOnI2C(false) {};

    /* Check whether the SHTC3 is connected to the I2C bus on the specific address. */
    bool isConnected();

public:
    /* Get the instance of the singleton. */
    static VEML7700Driver* getInstance(MessageInterface* messageInterface) {
        static VEML7700Driver _veml7700Driver(messageInterface);
        return &_veml7700Driver;
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

    uint8_t writeGain(uint8_t gain);

    uint16_t getAlsData();

    float getLuminosity();

};
