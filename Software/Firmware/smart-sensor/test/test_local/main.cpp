#include <unity.h>

#include "sensor-data/XBeeDataTests.hpp"

int main() {
    UNITY_BEGIN();

    test_sensor_data_XBeeDataTests::run();

    return UNITY_END();
}