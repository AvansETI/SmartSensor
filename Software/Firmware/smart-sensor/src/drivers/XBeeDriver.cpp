#include "drivers/XBeeDriver.h"

void XBeeDriver::setup() {
    
}

bool XBeeDriver::send(IXBeeData& data) {
    SerialLogger0.print(data.get_packet());
    return true;
}

