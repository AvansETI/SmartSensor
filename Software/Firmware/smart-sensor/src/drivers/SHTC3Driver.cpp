#include "drivers/SHTC3Driver.h"

/* If the chip is responding on I2C command, the setup is successfull. */
int SHTC3Driver::setup() {
    return ( this->isConnected() ? 0 : 1 );
}

int SHTC3Driver::loop() {
    this->sample();
    return 0;
}

int SHTC3Driver::reset() {    
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
    const bool able_to_select = TWI2_0.select(TWI_THS_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return able_to_select;
}

uint8_t SHTC3Driver::sample() {
    //this->setDataInvalid();

    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_THS_ADDRESS).wait().get();
    TWI2_0.write(0x35).wait().get();
    TWI2_0.write(0x17).wait().get();

    _delay_us(240);

    // MS: Why filtering the temperature?
    // MS: This can be optimized for embedded!
    // MS: I think filtering is not necessary!
    constexpr auto num_samples = 16;
    uint32_t avg_humidity = 0;
    uint32_t avg_temperature = 0;
    bool checksum_mismatch = false;

    for (int i = 0; i < num_samples; ++i) {
        TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
        TWI2_0.select(TWI_THS_ADDRESS).wait().get();
        TWI2_0.write(0x5C).wait().get(); // MS: Still waiting and blocking?! This is not what we want!
        TWI2_0.write(0x24).wait().get();
        TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
        TWI2_0.select(TWI_THS_ADDRESS).wait().get();
        uint16_t raw_humidity = static_cast<uint16_t>(TWI2_0.read_ack().wait().get().value()) << 8;
        raw_humidity |= TWI2_0.read_ack().wait().get().value();
        uint8_t raw_humidity_checksum = TWI2_0.read_ack().wait().get().value();
        uint16_t raw_temperature = static_cast<uint16_t>(TWI2_0.read_ack().wait().get().value()) << 8;
        raw_temperature |= TWI2_0.read_ack().wait().get().value();
        uint8_t raw_temperature_checksum = TWI2_0.read_nack().wait().get().value();

        avg_humidity += raw_humidity;
        avg_temperature += raw_temperature;

        checksum_mismatch |= !checkChecksum(raw_humidity, raw_humidity_checksum) || !checkChecksum(raw_temperature, raw_temperature_checksum);
    }

    TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_THS_ADDRESS).wait().get();
    TWI2_0.write(0xB0).wait().get();
    TWI2_0.write(0x98).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    if (checksum_mismatch) {
        SerialLogger0.print("THS checksum mismatch\n");
        return {};
    }

    // MS: How is this calculated?
    this->humidity    = 100 * float(avg_humidity/num_samples) / 65536.0f;
    this->temperature = 175 * float(avg_temperature/num_samples) / 65536.0f - 45.0f;

    //this->setDataValid();

    return 0;
}