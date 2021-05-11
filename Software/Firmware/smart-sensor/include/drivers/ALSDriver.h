#pragma once

class ALSDriver {
    public:

    bool isConnected();
    void takeMeasurement();
};

extern ALSDriver ALS;