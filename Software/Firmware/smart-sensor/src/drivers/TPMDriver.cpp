#include "drivers/TPMDriver.h"

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h> // HELP: Here also 2?

bool TPMDriver::isConnected() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    const bool able_to_select = TWI2_0.select(TWI_TPM_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();
    return able_to_select;
}

void TPMDriver::setup() {
    /*
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
    */
}

TPMDriver TPM;