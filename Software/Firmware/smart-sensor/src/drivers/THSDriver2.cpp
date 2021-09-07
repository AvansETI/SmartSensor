#include "drivers/THSDriver2.h"

#include <math.h>

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

THSDriver2 THS;

bool THSDriver2::check_checksum(const uint16_t data, const uint8_t checksum) {
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

bool THSDriver2::isConnected() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    const bool able_to_select = TWI2_0.select(TWI_THS_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();

    return able_to_select;
}

optional<THSDriver2::measurement> THSDriver2::takeMeasurement() {
    // @TODO handle errors

    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_THS_ADDRESS).wait().get();
    TWI2_0.write(0x35).wait().get();
    TWI2_0.write(0x17).wait().get();

    _delay_us(240);

    constexpr auto num_samples = 16;
    uint32_t avg_humidity = 0;
    uint32_t avg_temperature = 0;
    bool checksum_mismatch = false;

    for (int i = 0; i < num_samples; ++i) {
        TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
        TWI2_0.select(TWI_THS_ADDRESS).wait().get();
        TWI2_0.write(0x5C).wait().get();
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

        checksum_mismatch |= !check_checksum(raw_humidity, raw_humidity_checksum) || !check_checksum(raw_temperature, raw_temperature_checksum);
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

    const auto relative_humidity = 100 * float(avg_humidity/num_samples) / 65536.0f;
    const auto tempature = 175 * float(avg_temperature/num_samples) / 65536.0f - 45.0f;

    //SerialLogger0.printf("relative_humidity := %f, tempature := %f\n", relative_humidity, tempature);

    return {{tempature, relative_humidity}};
}