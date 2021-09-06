#pragma once

#include <stdint.h>
#include <board-support/drivers/TWIDriver2.h>

class RTCDriver {
    public:
    struct timepoint {
      uint8_t seconds;
      uint8_t minutes;
      uint8_t hours;
      uint8_t weekday;
      uint8_t date;
      uint8_t month;
      uint8_t year;
    };

    bool isConnected();
    optional<timepoint> getTime();
    //void setTime(const timepoint& t);

    bool startClock();
    // bool stopClock();

};

const char* generate_ISO_8601_string(RTCDriver::timepoint t);

extern RTCDriver RTC;