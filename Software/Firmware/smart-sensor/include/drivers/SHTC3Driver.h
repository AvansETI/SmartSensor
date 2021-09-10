#pragma once
/**
 * @file       : SHT3Driver.h
 * @description: This driver handles all the aspects of the SHT3 chip from Sensiron that is connected to the I2C(0) bus. The
 *               chip is able to measure the temperature and humidity. 
 *               https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensor-shtc3-our-new-standard-for-consumer-electronics/
 * @date       : 10-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @updates
 * 
 */
#include <drivers/Driver.h>

#include <math.h>

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

/* Address of the SHTC3 chip on the I2C bus */
//constexpr int SHTC3_I2C_ADDRESS = 0xE0;

/* The concreate SHTC3Driver that handles the hardware SHTC3 chip. */
class SHTC3Driver: public Driver {
private:
    float temperature;
    float humidity;

public:
    SHTC3Driver(): temperature(0.0), humidity(0.0) {};

    int setup();
    int loop();
    int reset();

    static bool checkChecksum(uint16_t data, uint8_t checksum);
    bool isConnected();
    uint8_t sample();
    float getTemperature();
    float getHumidity();
};
