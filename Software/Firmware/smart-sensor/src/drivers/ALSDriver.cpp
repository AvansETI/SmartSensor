#include "drivers/ALSDriver.h"

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

bool ALSDriver::isConnected() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    const bool able_to_select = TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();
    return able_to_select;
}

void ALSDriver::setupSensor() {
    TWI2_0.enable();


    constexpr uint16_t R0_setting = 0b0001'0000'0000'0000;
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(R0_setting >> 8).wait().get();
    TWI2_0.write(R0_setting & 0xFF).wait().get();

    constexpr uint16_t R3_setting = 0b0000'0000'0000'0000;
    TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(3).wait().get();
    TWI2_0.write(R3_setting >> 8).wait().get();
    TWI2_0.write(R3_setting & 0xFF).wait().get();
    TWI2_0.stop();


    TWI2_0.disable();
}

float raw_to_lux(uint16_t raw) {
    return static_cast<float>(raw) * 0.4608f;
}

optional<float> ALSDriver::takeMeasurement() {
    TWI2_0.enable();

    //@TODO add waking up and shutting down around measurement

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(4).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    // according to the datasheet this should be the other way around but this works
    uint16_t data = static_cast<uint16_t>(*TWI2_0.read_ack().wait().get()); 
    data |= static_cast<uint16_t>(*TWI2_0.read_nack().wait().get()) << 8;
    TWI2_0.stop();

    TWI2_0.disable();

    return raw_to_lux(data);
}

ALSDriver ALS;