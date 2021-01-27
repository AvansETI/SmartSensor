#ifndef SMART_SENSOR_LIGHTDRIVER_H_
#define SMART_SENSOR_LIGHTDRIVER_H_

#include <board-support/drivers/TWIDriver.h>

/**
 * The VEML77000 light sensor documentation:
 * https://www.vishay.com/docs/84286/veml7700.pdf
 */

class LightDriver : public TWIDriver {
public:
    /**
     * Enum for all possible gain configurations.
     * This affects the refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     */
    enum als_gain_t {
        ALS_GAIN_x1 = 0x0,      // x 1
        ALS_GAIN_x2 = 0x1,      // x 2
        ALS_GAIN_d8 = 0x2,      // x 1/8
        ALS_GAIN_d4 = 0x3       // x 1/4
    };

    /**
     * Enum for all possible integration time configurations.
     * This affects the refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     */
    enum als_integration_time_t {
        ALS_INTEGRATION_25ms = 0xc,
        ALS_INTEGRATION_50ms = 0x8,
        ALS_INTEGRATION_100ms = 0x0,
        ALS_INTEGRATION_200ms = 0x1,
        ALS_INTEGRATION_400ms = 0x2,
        ALS_INTEGRATION_800ms = 0x3
    };

    /**
     * Enum for all possible persistence protect configurations.
     */
    enum als_persistence_t {
        ALS_PERSISTENCE_1 = 0x0,
        ALS_PERSISTENCE_2 = 0x1,
        ALS_PERSISTENCE_4 = 0x2,
        ALS_PERSISTENCE_8 = 0x3
    };

    /**
     * Enum for all possible power saving mode configurations.
     * This affects the refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     */
    enum als_power_mode_t {
        ALS_POWER_MODE_1 = 0x0,
        ALS_POWER_MODE_2 = 0x1,
        ALS_POWER_MODE_3 = 0x2,
        ALS_POWER_MODE_4 = 0x3
    };

    /**
     * Initiates new LightDriver instance.
     */
    LightDriver();

    /**
     * Configures the initial state of the sensor (gain, integration,
     * persistence and power mode)
     * @return true if successful, false if communication failed
     */
    bool begin();

    /**
     * Returns the raw ALS lux value.
     * @param als Pointer to raw ALS lux value, in which the value will be
     * inserted
     * @return true if successful, false if communication failed
     */
    bool get_als(uint16_t &als);

    /**
     * Returns the ALS lux value.
     * @param lux Pointer to ALS lux value, in which the value will be inserted
     * @return true if successful, false if communication failed
     */
    bool get_als_lux(float &lux);

    /**
     * Returns the configured gain. Gain (ALS_GAIN) affects the sensor's
     * refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     * @param gain Pointer to gain value, in which the value will be inserted
     * @return true if successful, false if communication failed
     */
    bool get_gain(als_gain_t &gain);

    /**
     * Returns the configured integration time. Integration time (ALS_IT) affects
     * the sensor's refresh time. (See "Refresh time" table in VEML7700 documentation)
     * @param integration_time Pointer to integration time value, in which
     * the value will be inserted
     * @return true if successful, false if communication failed
     */
    bool get_integration_time(als_integration_time_t &integration_time);

    /**
     * Returns the raw white lux value.
     * @param white Pointer to raw white lux value, in which the value will
     * be inserted
     * @return true if successful, false if communication failed
     */
    bool get_white(uint16_t &white);

    /**
     * Returns the white lux value.
     * @param lux Pointer to white lux value, in which the value will be inserted
     * @return true if successful, false if communication failed
     */
    bool get_white_lux(float &lux);

    /**
     * Set a new gain configuration. Gain (ALS_GAIN) affects the sensor's
     * refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     * @param gain New gain configuration
     * @return true if successful, false if communication failed
     */
    bool set_gain(als_gain_t gain);

    /**
     * Set a new integration time configuration. Integration time (ALS_IT)
     * affects the sensor's refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     * @param integration_time New integration time configuration
     * @return true if successful, false if communication failed
     */
    bool set_integration_time(als_integration_time_t integration_time);

    /**
     * Enables or disables the interrupts.
     * @param enabled Boolean whether the interrupts should be
     * enabled or disabled.
     * @return true if successful, false if communication failed
     */
    bool set_interrupts(uint8_t enabled);

    /**
     * Set a new persistence protect configuration.
     * @param persist New persistence protect configuration
     * @return true if successful, false if communication failed
     */
    bool set_persistence(als_persistence_t persist);

    /**
     * Enables or disables the power saving mode.
     * @param enabled Boolean whether the power saving mode should
     * be enabled or disabled.
     * @return true if successful, false if communication failed
     */
    bool set_power_saving(uint8_t enabled);

    /**
     * Set a new power saving mode configuration. Power saving mode (PSM)
     * affects the sensor's refresh time.
     * (See "Refresh time" table in VEML7700 documentation)
     * @param power_mode New power saving mode configuration
     * @return true if successful, false if communication failed
     */
    bool set_power_saving_mode(als_power_mode_t power_mode);

    /**
     * Turns the sensor on/off.
     * @param on Boolean whether the power should be turned on/off
     * @return true if successful, false if communication failed
     */
    bool set_power(uint8_t on);

private:
    /**
     * ALS configuration values (bits).
     */
    enum {
        COMMAND_ALS_SM = 0x00, ALS_SM_MASK = 0x1800, ALS_SM_SHIFT = 11
    };
    enum {
        COMMAND_ALS_IT = 0x00, ALS_IT_MASK = 0x03c0, ALS_IT_SHIFT = 6
    };
    enum {
        COMMAND_ALS_PERS = 0x00, ALS_PERS_MASK = 0x0030, ALS_PERS_SHIFT = 4
    };
    enum {
        COMMAND_ALS_INT_EN = 0x00, ALS_INT_EN_MASK = 0x0002, ALS_INT_EN_SHIFT = 1
    };
    enum {
        COMMAND_ALS_SD = 0x00, ALS_SD_MASK = 0x0001, ALS_SD_SHIFT = 0
    };

    /**
     * ALS power saving mode configuration values (bits).
     */
    enum {
        COMMAND_PSM = 0x03, PSM_MASK = 0x0006, PSM_SHIFT = 1
    };
    enum {
        COMMAND_PSM_EN = 0x03, PSM_EN_MASK = 0x0001, PSM_EN_SHIFT = 0
    };

    /**
     * ALS value command (bits).
     */
    enum {
        COMMAND_ALS = 0x04
    };

    /**
     * White value command (bits)
     */
    enum {
        COMMAND_WHITE = 0x05
    };

    uint16_t register_cache[4]{};
    bool init = false;

    /**
     * Returns the requested data according to the given command.
     * @param command Command what data needs to be retrieved
     * @param data Pointer to the data value, in which the data will be inserted
     * @return true if successful, false if communication failed
     */
    bool get_data(uint8_t command, uint16_t &data);

    /**
     * Raw lux to lux calculator.
     * @param raw_counts The raw lux value
     * @param lux Pointer to lux value, in which the data will be inserted.
     */
    void scale_lux(uint16_t raw_counts, float &lux);

    /**
     * Sets a configuration, specified by the given command, with
     * a new configuration (data).
     * @param command Command what data needs to be set
     * @param data The new configuration value
     * @return true if successful, false if communication failed
     */
    bool send_data(uint8_t command, uint16_t data);
};

#endif //SMART_SENSOR_LIGHTDRIVER_H_