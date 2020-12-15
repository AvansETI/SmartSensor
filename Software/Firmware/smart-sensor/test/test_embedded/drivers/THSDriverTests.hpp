#ifndef HUMTEMPDRIVER_TESTS_H_
#define HUMTEMPDRIVER_TESTS_H_

#include <unity.h>
#include <avr/delay.h>
#include <board-support/util/SerialLogger.h>
#include "drivers/THSDriver.h"

namespace test_drivers_THSDriverTests {

    static THSDriver driver;
    SerialLogger logger;

    void test_THSDriver_updates() {
        TEST_ASSERT_TRUE(driver.update());
        logger.debugf("Hum: %f, Temp: %f, Status: %d\n", driver.get_humidity(), driver.get_temperature(), driver.get_status());
    }

    void test_THSDriver_status_correct() {
        TEST_ASSERT_EQUAL(THSDriver::NORMAL, driver.get_status());
    }

    void test_THSDriver_humidity_not_zero() {
        TEST_ASSERT_GREATER_THAN(0, driver.get_humidity());
    }

    void test_THSDriver_temperature_not_zero() {
        TEST_ASSERT_GREATER_THAN(0, driver.get_temperature());
    }

    void run() {
        // Setup TWI
        THSDriver::init();

        RUN_TEST(test_THSDriver_updates);
        RUN_TEST(test_THSDriver_status_correct);
        RUN_TEST(test_THSDriver_humidity_not_zero);
        RUN_TEST(test_THSDriver_temperature_not_zero);
    }
}

#endif