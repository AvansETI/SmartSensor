#pragma once
/**
 * @file       : SHT3Driver.h
 * @description: This driver handles all the aspects of the SHT3 chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to measure the temperature and humidity. 
 *               https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensor-shtc3-our-new-standard-for-consumer-electronics/
 * @date       : 24-10-2021
 * @author     : Floris Bob van Elzelingen, Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : The loop contains blocking function calls!
 *               Idea is to create a class for I2C that contains some mutex to get the resource for yourself. 
 *               each driver that requires the I2C need to wait until it gets the unique access and use it until is releases it.
 * @changes
 *  24-10-2021: MS: Improved the memory with 2 bytes.
 */
#include <drivers/Driver.h>

#include <math.h>
#include <avr/pgmspace.h>

#include <util/I2C.h>
#include <tasks/Atmega324PBI2C0.h>

/* Address of the SHTC3 chip on the I2C bus */
constexpr uint8_t SHTC3_I2C_ADDRESS = 0xE0;

/* The enumeration that is used for the data array. */
enum SHTC3Data {
    HUMIDITY_0,
    HUMIDITY_1,
    HUMIDITY_CHECKSUM,
    TEMPERATURE_0,
    TEMPERATURE_1,
    TEMPERATURE_CHECKSUM
};

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class SHTC3Driver: public Driver, public I2CReadEvent {
private:
    /* The id of the SHTC3 chip. */
    uint16_t id;

    /* The data that is read from the I2C bus. */
    uint8_t data[6];

    /* Set the sampling interval of the sensor in seconds. */
    uint16_t samplingInterval;

    /* Hold the timestamp in seconds where we have started the sampling. */
    uint16_t samplingTimestamp;

    /* When the sampling could not occur due to a busy I2C bus, this flag becomes true. */
    bool waitingOnI2C; 

protected:
    /* Protected constructor to create a singleton. */
    SHTC3Driver(MessageInterface* messageInterface): Driver(messageInterface), id(0), waitingOnI2C(false) {};

    /* Check whether the SHTC3 is connected to the I2C bus on the specific address. */
    bool isConnected();

public:
    /* Get the instance of the singleton. */
    static SHTC3Driver* getInstance(MessageInterface* messageInterface) {
        static SHTC3Driver _shtc3Driver(messageInterface);
        return &_shtc3Driver;
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

    /* Returns the unique ID of the SHTC3 chip. Note that bit 15L12 and 10:6 contain unspecified info
       that vary from sensor to sensor. Bits 11 and 5:0 contain the SHTC3 specific product code.
    */
    uint16_t getID();

    /* Returns the specific product code of the sensor, see datasheet. */
    uint16_t getProductCode();

    /* Set the required sampling interval in seconds that this sensor needs to be sampled. */
    void setSamplingInterval(uint16_t samplingInterval) { this->samplingInterval = samplingInterval; }

    /* Interface: I2CReadEvent */
    void i2cReadEvent(uint8_t data, uint8_t index);

    /* Read the temperature from the data that has been send from the I2C. */
    uint16_t getTemperatureData();

    /* Read the humidity from the data that has been send from the I2C. */
    uint16_t getHumidityData();

    /* Read the real temperature from the data that has been send from the I2C. */
    float getTemperature();

    /* Read the real humidity from the data that has been send from the I2C. */
    float getHumidity();

    /* Returns true when the checksum of the temperature is correct, otherwise false. */ 
    bool isTemperatureValid();

    /* Returns true when the checksum of the humidity is correct, otherwise false. */ 
    bool isHumidityValid();

};
