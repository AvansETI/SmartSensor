#pragma once
/**
 * @file       : VEML7700.h
 * @description: This driver handles the ambient light sensor, able to measure changes in the brightness of light. 
 *               https://www.vishay.com/docs/84286/veml7700.pdf
 * @date       : 21-09-2021
 * @author     : Tom Kaasenbrood
 * @version    : 0.2
 * @todo       : 
 * @updates
 * 
 */
#include "drivers/Driver.h"

#include <util/I2C0.h>

#define VEML7700_CONFIG 0x00        ///< Light configuration register
#define VEML7700_THREHOLD_HIGH 0x01 ///< Light high threshold for irq
#define VEML7700_THREHOLD_LOW 0x02  ///< Light low threshold for irq
#define VEML7700_POWER_SAVE 0x03    ///< Power save regiester
#define VEML7700_DATA 0x04          ///< The light data output
#define VEML7700_WHITE_DATA 0x05        ///< The white light data output
#define VEML7700_INTERRUPTSTATUS 0x06   ///< What IRQ (if any)

#define VEML7700_INTERRUPT_HIGH 0x4000 ///< Interrupt status for high threshold
#define VEML7700_INTERRUPT_LOW 0x8000  ///< Interrupt status for low threshold

#define VEML7700_GAIN_1 0x00   ///< ALS gain 1x
#define VEML7700_GAIN_2 0x01   ///< ALS gain 2x
#define VEML7700_GAIN_1_8 0x02 ///< ALS gain 1/8x
#define VEML7700_GAIN_1_4 0x03 ///< ALS gain 1/4x

#define VEML7700_IT_100MS 0x00 ///< ALS intetgration time 100ms
#define VEML7700_IT_200MS 0x01 ///< ALS intetgration time 200ms
#define VEML7700_IT_400MS 0x02 ///< ALS intetgration time 400ms
#define VEML7700_IT_800MS 0x03 ///< ALS intetgration time 800ms
#define VEML7700_IT_50MS 0x08  ///< ALS intetgration time 50ms
#define VEML7700_IT_25MS 0x0C  ///< ALS intetgration time 25ms

#define VEML7700_PERS_1 0x00 ///< ALS irq persisance 1 sample
#define VEML7700_PERS_2 0x01 ///< ALS irq persisance 2 samples
#define VEML7700_PERS_4 0x02 ///< ALS irq persisance 4 samples
#define VEML7700_PERS_8 0x03 ///< ALS irq persisance 8 samples

#define VEML7700_POWERSAVE_MODE1 0x00 ///< Power saving mode 1
#define VEML7700_POWERSAVE_MODE2 0x01 ///< Power saving mode 2
#define VEML7700_POWERSAVE_MODE3 0x02 ///< Power saving mode 3
#define VEML7700_POWERSAVE_MODE4 0x03 ///< Power saving mode 4

// Address of the VEML7700 sensor
constexpr uint8_t VEML7700_I2C_ADDRESS PROGMEM = 0x20;

// The concrete driver to handle the sensor
class VEML7700Driver: public Driver, public I2C0InterruptEvent {
private:
    uint16_t id;
    uint8_t state;
    uint16_t lightValue;
    uint16_t whiteLightValue;

    uint32_t samplingInterval;
    uint32_t loopTiming;

    uint8_t testloop;
    uint8_t CHANGEGAIN(uint8_t gain);
    uint8_t writeGain(uint8_t gain);
protected:
    VEML7700Driver(SmartSensorMeasurement* luMeasurement): Driver(luMeasurement), state(0), testloop(0) {};

    bool isConnected();    
public:
    static VEML7700Driver* getInstance(SmartSensorMeasurement* luMeasurement) {
        static VEML7700Driver _veml7700Driver(luMeasurement);
        return &_veml7700Driver;
    }

    uint8_t setup();
    uint8_t loop(uint32_t millis);
    uint8_t reset();
    uint8_t sleep();
    uint8_t wakeup();

    uint8_t sampleLoop();

    // When using the I2C module, this event is issued when an I2C is ready!
    void i2c0Interrupt();

    void setSamplingInterval(uint32_t samplingInterval) { this->samplingInterval = samplingInterval; }

};