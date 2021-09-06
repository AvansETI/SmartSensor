#include "drivers/XBeeDriver.h"

bool XBeeDriver::send(IXBeeData& data) {
    SerialLogger0.print(data.get_packet());
    return true;
}

