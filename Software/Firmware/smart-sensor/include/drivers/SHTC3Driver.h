#pragma once
/**
 * @file       : SHT3Driver.h
 * @description: This driver handles all the aspects of the SHT3 chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to measure the temperature and humidity. 
 *               https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensor-shtc3-our-new-standard-for-consumer-electronics/
 * @date       : 10-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : The loop contains blocking function calls!
 * @updates
 * 
 */
#include <drivers/Driver.h>

#include <math.h>

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

/* Address of the SHTC3 chip on the I2C bus */
constexpr int SHTC3_I2C_ADDRESS = 0xE0;

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class SHTC3Driver: public Driver {
private:
    float temperature;
    float humidity;
    uint16_t id;

public:
    SHTC3Driver(): temperature(0.0), humidity(0.0), id(0) {};

    int setup();
    int loop();
    int reset();
    int sleep();
    int wakeup();

    static bool checkChecksum(uint16_t data, uint8_t checksum);
    bool isConnected();
    uint8_t sample();
    float getTemperature();
    float getHumidity();

    /* Returns the unique ID of the SHTC3 chip. Note that bit 15L12 and 10:6 contain unspecified info
       that vary from sensor to sensor. Bits 11 and 5:0 contain the SHTC3 specific product code.
    */
    uint16_t getID();

    /* Returns the specific product code of the sensor. */
    uint16_t getProductCode();
};
