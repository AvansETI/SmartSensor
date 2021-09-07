#pragma once

#include <board-support/drivers/TWIDriver2.h>

class TPMDriver {
    public:

    //ADD functionality

    bool isConnected();
    void setup();
};

extern TPMDriver TPM;