#ifndef XBEEDATA_TESTS_H_
#define XBEEDATA_TESTS_H_

#include <unity.h>
#include "sensor-data/XBeeData.h"

namespace test_sensor_data_XBeeDataTests {
    void test_XBeeData_generate_packet() {
        XBeeData data = XBeeData(10.0f, 20.0f, 30.0f);

        TEST_ASSERT_EQUAL_STRING("[{\"name\":\"Temperature\",\"value\":10.00,\"unit\":\"C\"},{\"name\":\"Humidity\",\"value\":20.00,\"unit\":\"%\"},{\"name\":\"Illuminance\",\"value\":30.00,\"unit\":\"lx\"}]", data.get_packet());
    }

    void run() {
        RUN_TEST(test_XBeeData_generate_packet);
    }
}

#endif