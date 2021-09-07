#pragma once

class CO2Driver {

public:
    bool isConnected();
    void setupSensor();
    void takeMeasurement();
};

extern CO2Driver CO2;