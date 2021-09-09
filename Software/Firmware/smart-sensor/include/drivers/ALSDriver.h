#pragma once

#include <board-support/drivers/TWIDriver2.h>

class ALSDriver {
    public:

    //ADD settings and proper conversions

    bool isConnected();
    void setupSensor();
    optional<float> takeMeasurement();
};

extern ALSDriver ALS; // MS: Why we do this?!