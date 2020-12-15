#include "drivers/XBeeDriver.h"

bool XBeeDriver::send(IXBeeData& data) {
    SerialLogger::print(data.get_packet());
    return true;
}

