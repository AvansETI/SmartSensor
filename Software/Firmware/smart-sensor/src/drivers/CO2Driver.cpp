#include "drivers/CO2Driver.h"

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

CO2Driver CO2;

bool CO2Driver::isConnected() {
    TWI2_0.enable();
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    const bool able_to_select = TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.stop();
    TWI2_0.disable();
    return able_to_select;
}

void CO2Driver::setupSensor() {
    TWI2_0.enable();

    //set R01 to 0b0001'0000

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(0xFF).wait().get();
    TWI2_0.write(0x11).wait().get();
    TWI2_0.write(0xE5).wait().get();
    TWI2_0.write(0x72).wait().get();
    TWI2_0.write(0x8A).wait().get();
    TWI2_0.stop();

    _delay_ms(50); //overkill

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(0xF4).wait().get();
    TWI2_0.stop();

    constexpr uint16_t R1_setting = 0b0001'0000;
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(1).wait().get();
    TWI2_0.write(R1_setting >> 8).wait().get();
    TWI2_0.write(R1_setting & 0xFF).wait().get();
    TWI2_0.stop();

    TWI2_0.disable();
}

void CO2Driver::takeMeasurement() {
    TWI2_0.enable();

    //read R02 CO2-H, CO2-L, TVOC-H, TVOC-L
    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(0).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    const uint8_t status = TWI2_0.read_nack().wait().get();
    TWI2_0.stop();

    SerialLogger0.printf("status := %b\n", status);

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(0xE0).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    const uint8_t error = TWI2_0.read_nack().wait().get();
    TWI2_0.stop();

    SerialLogger0.printf("error := %b\n", error);

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(0x24).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    const uint8_t firmware_version = TWI2_0.read_nack().wait().get();
    TWI2_0.stop();

    SerialLogger0.printf("firmware_version := %b\n", firmware_version);

    TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    TWI2_0.write(2).wait().get();
    TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
    TWI2_0.select(TWI_CO2_ADDRESS).wait().get();
    const uint16_t co2 = static_cast<uint16_t>(*TWI2_0.read_ack().wait().get()) | *TWI2_0.read_ack().wait().get();
    const uint16_t tvoc = static_cast<uint16_t>(*TWI2_0.read_ack().wait().get()) | TWI2_0.read_nack().wait().get();
    TWI2_0.stop();

    TWI2_0.disable();

    SerialLogger0.printf("co2 := 0x%x%x, tvoc := 0x%x%x\n", co2 >> 8, co2 & 0xFF, tvoc >> 8, tvoc & 0xFF);
}