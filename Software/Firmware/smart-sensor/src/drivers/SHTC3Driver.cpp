#include "drivers/SHTC3Driver.h"

#include <stdio.h>
#include <string.h>

int SHTC3Driver::setup() {
    if ( !this->isConnected() ) {
        return 1; // Cannot select the SHTC3 chip
    }

    if ( this->getID() == 0 ) {
        return 2; // The given ID is not correct!
    }

    return 0;
}

int SHTC3Driver::loop(uint32_t millis) {
    this->sample();
    return 0;
}

// Software reset 0x805D 1000’0000’0101’1101 => page 8: https://taoic.oss-cn-hangzhou.aliyuncs.com/sku/pdf/d16078ca630c4b401c5bec25674afc26833e7455.pdf
int SHTC3Driver::reset() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.write(0x80).wait().get(); // Soft reset command
    TWI2_0.write(0x5D).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return 0;
}

int SHTC3Driver::sleep() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.write(0xB0).wait().get(); // Sleep command
    TWI2_0.write(0x98).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return 0;
}

int SHTC3Driver::wakeup() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.write(0x35).wait().get(); // Wake up command
    TWI2_0.write(0x17).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return 0;
}

float SHTC3Driver::getTemperature() {
    return this->temperature;
}

float SHTC3Driver::getHumidity() {
    return this->humidity;
}

// Where is the source of this calculation?
bool SHTC3Driver::checkChecksum(const uint16_t data, const uint8_t checksum) {
    constexpr auto polynomial = 0x131; // P(x) = x^8 + x^5 + x^4 + 1 = 100110001

    uint8_t bit;        // bit mask
    uint8_t crc = 0xFF; // calculated checksum
    uint8_t byteCtr;    // byte counter

     // calculates 8-Bit checksum with given polynomial
    for(byteCtr = 0; byteCtr < 2; byteCtr++) {
        crc ^= static_cast<uint8_t>(data >> ((1-byteCtr)*8));
        for(bit = 8; bit > 0; --bit) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc = (crc << 1);
            }
        }
    }

    return crc == checksum;
}

bool SHTC3Driver::isConnected() {    
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    const bool able_to_select = TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return able_to_select;
}

uint16_t SHTC3Driver::getProductCode() {
    return this->getID() & 0b0000'1000'0011'1111;
}

uint16_t SHTC3Driver::getID() {
    if ( this->id != 0 ) {
        return this->id;
    }

    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.write(0xEF).wait().get();
    TWI2_0.write(0xC8).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get(); // Is clock stretching?!
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    uint16_t id = static_cast<uint16_t>(TWI2_0.read_ack().wait().get().value()) << 8;
    id |= TWI2_0.read_ack().wait().get().value();
    uint8_t checksum = TWI2_0.read_ack().wait().get().value();
    TWI2_0.stop();
    TWI2_0.disable();

    if ( this->checkChecksum(id, checksum) ) {
        this->id = id;
    }

    return id;
}

uint8_t SHTC3Driver::sample() {
    this->setDataInvalid();

    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    TWI2_0.write(0x5C).wait().get(); // MS: Measurement command // MS: Still waiting and blocking?! This is not what we want!
    TWI2_0.write(0x24).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get(); // Is clock stretching?!
    TWI2_0.select(SHTC3_I2C_ADDRESS).wait().get();
    uint16_t raw_humidity = static_cast<uint16_t>(TWI2_0.read_ack().wait().get().value()) << 8;
    raw_humidity |= TWI2_0.read_ack().wait().get().value();
    uint8_t raw_humidity_checksum = TWI2_0.read_ack().wait().get().value();
    uint16_t raw_temperature = static_cast<uint16_t>(TWI2_0.read_ack().wait().get().value()) << 8;
    raw_temperature |= TWI2_0.read_ack().wait().get().value();
    uint8_t raw_temperature_checksum = TWI2_0.read_nack().wait().get().value();
    TWI2_0.stop();
    TWI2_0.disable();

    if ( !this->checkChecksum(raw_humidity, raw_humidity_checksum) || !this->checkChecksum(raw_temperature, raw_temperature_checksum) ) {
        return 1; // Checksum mismatch!
    }

    // See datasheet page 9 for the details of the calculation
    this->humidity    = 100 * float(raw_humidity) / 65536.0f;
    this->temperature = 175 * float(raw_temperature) / 65536.0f - 45.0f;

    if ( this->getMeasurementCallback() != NULL ) {
        this->getMeasurementCallback()->addMeasurement("humidity:%0.1f", this->humidity);
        this->getMeasurementCallback()->addMeasurement("temperature:%0.1f", this->temperature);
    }

    this->setDataValid();

    return 0;
}