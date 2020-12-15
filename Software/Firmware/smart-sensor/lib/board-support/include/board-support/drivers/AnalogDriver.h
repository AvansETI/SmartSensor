#ifndef ANALOG_DRIVER_H_
#define ANALOG_DRIVER_H_

#include "IDriver.h"

class AnalogDriver : IDriver {
    public:
        void get_value() override;
};

#endif