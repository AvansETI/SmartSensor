#include "drivers/RTCDriver.h"

#include <boardsupport.h>
#include <board-support/drivers/TWIDriver2.h>

RTCDriver RTC;

uint8_t convertToBcd(uint8_t byteDecimal) {

  return (byteDecimal / 10) << 4 | (byteDecimal % 10);

}

uint8_t convertFromBcd(uint8_t byteBCD) {

  uint8_t byteMSB = 0;
  uint8_t byteLSB = 0;

  byteMSB      = (byteBCD & 0b1111'0000) >> 4;
  byteLSB      = (byteBCD & 0b0000'1111);

  return       ((byteMSB * 10) + byteLSB);
}

bool RTCDriver::isConnected() {
  TWI2_0.enable();
  TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
  const bool able_to_select = TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.stop();
  TWI2_0.disable();
  return able_to_select;
}

optional<RTCDriver::timepoint> RTCDriver::getTime() {
  union {
    timepoint t;
    uint8_t raw[7];
  } data;

  constexpr uint8_t masks[7] = {0b0111'1111, 0b0111'1111, 0b0001'1111, 0b0000'0011, 0b0011'1111, 0b0001'1111, 0b1111'1111};

  TWI2_0.enable();
  TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get(); // Blocking!
  TWI2_0.write(0x00).wait().get();
  TWI2_0.repeated_start(TWIMode::MasterReciever).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  for (uint8_t i = 0; i < 7; ++i)
    data.raw[i] = convertFromBcd(*(i != 6 ? TWI2_0.read_ack() : TWI2_0.read_nack()).wait().get() & masks[i]);
  //auto res = TWI2_0.read_nack().wait().get();

  TWI2_0.stop();
  TWI2_0.disable();

  //SerialLogger0.printf("[00]:%d\n", (int)res);
  //SerialLogger0.printf("time raw: [0]:%d [1]:%d\n", (int)data.raw[1], (int)data.raw[2]);

  return data.t;
}

bool RTCDriver::startClock() { // What is happening here?
  TWI2_0.enable();
  TWI2_0.start(TWIMode::MasterTransmitter).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.write(0x07).wait().get();
  TWI2_0.write(0b0000'0100).wait().get();
  TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.write(0x04).wait().get();
  TWI2_0.write(0b0000'0001).wait().get();
  TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.write(0x06).wait().get();
  TWI2_0.write(convertToBcd(21)).wait().get();
  TWI2_0.repeated_start(TWIMode::MasterTransmitter).wait().get();
  TWI2_0.select(TWI_RTC_ADDRESS).wait().get();
  TWI2_0.write(0x00).wait().get();
  TWI2_0.write(0b1000'0000).wait().get();
  TWI2_0.stop();
  TWI2_0.disable();

  return true;
}

const char* generate_ISO_8601_string(RTCDriver::timepoint t) {
  static char buffer[20] = "20YY-MM-DDThh:mm:ss";
  buffer[2] = '0' + (t.year/10);
  buffer[3] = '0' + (t.year%10);
  
  buffer[5] = '0' + (t.month/10);
  buffer[6] = '0' + (t.month%10);

  buffer[8] = '0' + (t.date/10);
  buffer[9] = '0' + (t.date%10);

  buffer[11] = '0' + (t.hours/10);
  buffer[12] = '0' + (t.hours%10);

  buffer[14] = '0' + (t.minutes/10);
  buffer[15] = '0' + (t.minutes%10);

  buffer[17] = '0' + (t.seconds/10);
  buffer[18] = '0' + (t.seconds%10);

  return buffer;
}