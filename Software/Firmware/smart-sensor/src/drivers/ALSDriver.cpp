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

void ALSDriver::takeMeasurement() {
    TWI2_0.enable();

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(3).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.stop();

    _delay_ms(1);
    SerialLogger::print("R3 is set\n");

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(4).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    uint16_t data = static_cast<uint16_t>(*TWI2_0.read_ack().wait().get()) << 8;
    data |= *TWI2_0.read_nack().wait().get();
    TWI2_0.stop();

    SerialLogger::printf("data pre := 0x%x%x\n", data >> 8, data & 0x00FF);

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.stop();

    for (int i = 0; i < 100; ++i) {
        TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
        TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
        TWI2_0.write(4).wait().get();
        TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
        TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
        uint16_t data = static_cast<uint16_t>(*TWI2_0.read_ack().wait().get()) << 8;
        data |= *TWI2_0.read_nack().wait().get();
        TWI2_0.stop();

        TWI2_0.disable();

        SerialLogger::printf("data(%d) := 0x%x%x\n", i, data >> 8, data & 0x00FF);
        _delay_ms(10);
        TWI2_0.enable();
    }

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_ALS_ADDRESS).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.write(1).wait().get();
    TWI2_0.stop();

    TWI2_0.disable();
}

ALSDriver ALS;