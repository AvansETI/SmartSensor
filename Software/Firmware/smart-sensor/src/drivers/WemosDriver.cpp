#include "drivers/WemosDriver.h"
#include <board-support/drivers/TWIDriver2.h>

WemosDriver Wemos;

bool WemosDriver::isConnected() {
  /*TWI2_1.enable();
  TWI2_1.start(TWIMode::MasterTransmitter).wait().get();
  const bool res = TWI2_1.select(0b1010).wait().get();
  TWI2_1.stop();
  TWI2_1.disable();*/

  return false;
}