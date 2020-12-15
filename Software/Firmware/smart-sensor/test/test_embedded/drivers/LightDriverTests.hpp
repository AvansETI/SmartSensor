#ifndef SMART_SENSOR_LIGHTDRIVERTESTS_HPP
#define SMART_SENSOR_LIGHTDRIVERTESTS_HPP

#include <unity.h>
#include <drivers/LightDriver.h>

namespace test_drivers_LightDriverTests {
    static LightDriver lightDriver;

    void test_LightDriver_begin() {
        TEST_ASSERT_TRUE(lightDriver.begin());
        SerialLogger::debug("LightDriver initialized");
    }

    void test_LightDriver_enableInterrupts() {
        TEST_ASSERT_TRUE(lightDriver.set_interrupts(true))
        SerialLogger::debug("Enabled interrupts");
    }

    void test_LightDriver_disableInterrupts() {
        TEST_ASSERT_TRUE(lightDriver.set_interrupts(false))
        SerialLogger::debug("Disabled interrupts");
    }

    void test_LightDriver_enablePower() {
        TEST_ASSERT_TRUE(lightDriver.set_power(true))
        SerialLogger::debug("Turned power on");
    }

    void test_LightDriver_disablePower() {
        TEST_ASSERT_TRUE(lightDriver.set_power(false))
        SerialLogger::debug("Turned power off");
    }

    void test_LightDriver_enablePowerSaving() {
        TEST_ASSERT_TRUE(lightDriver.set_power_saving(true))
        SerialLogger::debug("Enabled power saving");
    }

    void test_LightDriver_disablePowerSaving() {
        TEST_ASSERT_TRUE(lightDriver.set_power_saving(false))
        SerialLogger::debug("Disabled power saving");
    }

    void test_LightDriver_getALS() {
        uint16_t als;
        TEST_ASSERT_TRUE(lightDriver.get_als(als))
        SerialLogger::debug("Retrieved ALS");
        SerialLogger::debugf("ALS: %d", als);
    }

    void test_LightDriver_getALSLux() {
        float lux;
        TEST_ASSERT_TRUE(lightDriver.get_als_lux(lux))
        SerialLogger::debug("Retrieved ALS Lux");
        SerialLogger::debugf("Lux: %f", lux);
    }

    void test_LightDriver_getWhite() {
        uint16_t white;
        TEST_ASSERT_TRUE(lightDriver.get_white(white))
        SerialLogger::debug("Retrieved White");
        SerialLogger::debugf("White: %d", white);
    }

    void test_LightDriver_getWhiteLux() {
        float lux;
        TEST_ASSERT_TRUE(lightDriver.get_white_lux(lux))
        SerialLogger::debug("Retrieved White Lux");
        SerialLogger::debugf("Lux: %f", lux);
    }

    void test_LightDriver_setGain() {
        LightDriver::als_gain_t gain;

        TEST_ASSERT_TRUE(lightDriver.set_gain(LightDriver::ALS_GAIN_x2))
        TEST_ASSERT_TRUE(lightDriver.get_gain(gain))
        TEST_ASSERT_EQUAL(LightDriver::ALS_GAIN_x2, gain);

        TEST_ASSERT_TRUE(lightDriver.set_gain(LightDriver::ALS_GAIN_d4))
        TEST_ASSERT_TRUE(lightDriver.get_gain(gain))
        TEST_ASSERT_EQUAL(LightDriver::ALS_GAIN_d4, gain);

        TEST_ASSERT_TRUE(lightDriver.set_gain(LightDriver::ALS_GAIN_d8))
        TEST_ASSERT_TRUE(lightDriver.get_gain(gain))
        TEST_ASSERT_EQUAL(LightDriver::ALS_GAIN_d8, gain);

        TEST_ASSERT_TRUE(lightDriver.set_gain(LightDriver::ALS_GAIN_x1))
        TEST_ASSERT_TRUE(lightDriver.get_gain(gain))
        TEST_ASSERT_EQUAL(LightDriver::ALS_GAIN_x1, gain);
    }

    void test_LightDriver_setIntegrationTime() {
        LightDriver::als_integration_time_t integrationTime;

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_200ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_200ms, integrationTime);

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_400ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_400ms, integrationTime);

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_800ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_800ms, integrationTime);

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_25ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_25ms, integrationTime);

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_50ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_50ms, integrationTime);

        TEST_ASSERT_TRUE(lightDriver.set_integration_time(LightDriver::ALS_INTEGRATION_100ms))
        TEST_ASSERT_TRUE(lightDriver.get_integration_time(integrationTime))
        TEST_ASSERT_EQUAL(LightDriver::ALS_INTEGRATION_100ms, integrationTime);
    }

    void test_LightDriver_setPersistence() {
        TEST_ASSERT_TRUE(lightDriver.set_persistence(LightDriver::ALS_PERSISTENCE_2))
        SerialLogger::debug("Persistence changed to ALS_PERSISTENCE_2");

        TEST_ASSERT_TRUE(lightDriver.set_persistence(LightDriver::ALS_PERSISTENCE_4))
        SerialLogger::debug("Persistence changed to ALS_PERSISTENCE_4");

        TEST_ASSERT_TRUE(lightDriver.set_persistence(LightDriver::ALS_PERSISTENCE_8))
        SerialLogger::debug("Persistence changed to ALS_PERSISTENCE_8");

        TEST_ASSERT_TRUE(lightDriver.set_persistence(LightDriver::ALS_PERSISTENCE_1))
        SerialLogger::debug("Persistence changed to ALS_PERSISTENCE_1");
    }

    void test_LightDriver_setPowerSavingMode() {
        TEST_ASSERT_TRUE(lightDriver.set_power_saving_mode(LightDriver::ALS_POWER_MODE_1))
        SerialLogger::debug("Power saving mode changed to ALS_POWER_MODE_1");

        TEST_ASSERT_TRUE(lightDriver.set_power_saving_mode(LightDriver::ALS_POWER_MODE_2))
        SerialLogger::debug("Power saving mode changed to ALS_POWER_MODE_2");

        TEST_ASSERT_TRUE(lightDriver.set_power_saving_mode(LightDriver::ALS_POWER_MODE_3))
        SerialLogger::debug("Power saving mode changed to ALS_POWER_MODE_3");

        TEST_ASSERT_TRUE(lightDriver.set_power_saving_mode(LightDriver::ALS_POWER_MODE_4))
        SerialLogger::debug("Power saving mode changed to ALS_POWER_MODE_4");
    }

    void run() {
        RUN_TEST(test_LightDriver_begin);
        RUN_TEST(test_LightDriver_enableInterrupts);
        RUN_TEST(test_LightDriver_disableInterrupts);
        RUN_TEST(test_LightDriver_enablePower);
        RUN_TEST(test_LightDriver_disablePower);
        RUN_TEST(test_LightDriver_enablePowerSaving);
        RUN_TEST(test_LightDriver_disablePowerSaving);
        RUN_TEST(test_LightDriver_getALS);
        RUN_TEST(test_LightDriver_getALSLux);
        RUN_TEST(test_LightDriver_getWhite);
        RUN_TEST(test_LightDriver_getWhiteLux);
        RUN_TEST(test_LightDriver_setGain);
        RUN_TEST(test_LightDriver_setIntegrationTime);
        RUN_TEST(test_LightDriver_setPersistence);
        RUN_TEST(test_LightDriver_setPowerSavingMode);
    }
}

#endif //SMART_SENSOR_LIGHTDRIVERTESTS_HPP
