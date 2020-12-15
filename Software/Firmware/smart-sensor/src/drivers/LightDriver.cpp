//
// Created by Sergen on 16/04/2020.
//

#include <board-support/util/SerialLogger.h>
#include "drivers/LightDriver.h"
#include "boardsupport.h"

LightDriver::LightDriver() : TWIDriver(TWI0) {

}

bool LightDriver::begin() {
    if (!init) {
        // Write initial state to VEML7700.
        register_cache[0] = ((ALS_GAIN_x1 << ALS_SM_SHIFT) |
                             (ALS_INTEGRATION_100ms << ALS_IT_SHIFT) |
                             (ALS_PERSISTENCE_1 << ALS_PERS_SHIFT) |
                             (0 << ALS_INT_EN_SHIFT) |
                             (0 << ALS_SD_SHIFT));
        register_cache[1] = 0x0000;
        register_cache[2] = 0xffff;
        register_cache[3] = ((ALS_POWER_MODE_4 << PSM_SHIFT) |
                             (0 << PSM_EN_SHIFT));

        for (uint8_t i = 0; i < 4; i++) {
            if (!send_data(i, register_cache[i])) {
                twi_stop();
                return false;
            }
        }

        init = true;
    }

    // Wait at least 2.5ms as per datasheet.
    _delay_ms(3);

    return true;
}

bool LightDriver::set_gain(als_gain_t gain) {
    uint16_t reg = ((register_cache[COMMAND_ALS_SM] & ~ALS_SM_MASK) |
                    ((uint16_t(gain) << ALS_SM_SHIFT) & ALS_SM_MASK));
    register_cache[COMMAND_ALS_SM] = reg;
    return send_data(COMMAND_ALS_SM, reg);
}

bool LightDriver::get_gain(als_gain_t &gain) {
    gain = als_gain_t((register_cache[COMMAND_ALS_SM] & ALS_SM_MASK) >> ALS_SM_SHIFT);
    return true;
}

bool LightDriver::set_integration_time(als_integration_time_t integration_time) {
    uint16_t reg = ((register_cache[COMMAND_ALS_IT] & ~ALS_IT_MASK) |
                    ((uint16_t(integration_time) << ALS_IT_SHIFT) & ALS_IT_MASK));
    register_cache[COMMAND_ALS_IT] = reg;
    return send_data(COMMAND_ALS_IT, reg);
}

bool LightDriver::get_integration_time(als_integration_time_t &integration_time) {
    integration_time = als_integration_time_t(
            (register_cache[COMMAND_ALS_IT] & ALS_IT_MASK) >> ALS_IT_SHIFT);
    return true;
}

bool LightDriver::set_persistence(als_persistence_t persist) {
    uint16_t reg = ((register_cache[COMMAND_ALS_PERS] & ~ALS_PERS_MASK) |
                    ((uint16_t(persist) << ALS_PERS_SHIFT) & ALS_PERS_MASK));
    register_cache[COMMAND_ALS_PERS] = reg;
    return send_data(COMMAND_ALS_PERS, reg);
}

bool LightDriver::set_power_saving_mode(als_power_mode_t power_mode) {
    uint16_t reg = ((register_cache[COMMAND_PSM] & ~PSM_MASK) |
                    ((uint16_t(power_mode) << PSM_SHIFT) & PSM_MASK));
    register_cache[COMMAND_PSM] = reg;
    return send_data(COMMAND_PSM, reg);
}

bool LightDriver::set_power_saving(uint8_t enabled) {
    uint16_t reg = ((register_cache[COMMAND_PSM_EN] & ~PSM_EN_MASK) |
                    ((uint16_t(enabled) << PSM_EN_SHIFT) & PSM_EN_MASK));
    register_cache[COMMAND_PSM_EN] = reg;
    return send_data(COMMAND_PSM_EN, reg);
}

bool LightDriver::set_interrupts(uint8_t enabled) {
    uint16_t reg = ((register_cache[COMMAND_ALS_INT_EN] & ~ALS_INT_EN_MASK) |
                    ((uint16_t(enabled) << ALS_INT_EN_SHIFT) &
                     ALS_INT_EN_MASK));
    register_cache[COMMAND_ALS_INT_EN] = reg;
    return send_data(COMMAND_ALS_INT_EN, reg);
}

bool LightDriver::set_power(uint8_t on) {
    uint16_t reg = ((register_cache[COMMAND_ALS_SD] & ~ALS_SD_MASK) |
                    ((uint16_t(~on) << ALS_SD_SHIFT) & ALS_SD_MASK));
    register_cache[COMMAND_ALS_SD] = reg;
    bool status = send_data(COMMAND_ALS_SD, reg);
    if (on)
        // Wait at least 2.5ms as per datasheet.
        _delay_ms(3);
    return status;
}

bool LightDriver::get_als(uint16_t &als) {
    return get_data(COMMAND_ALS, als);
}

bool LightDriver::get_white(uint16_t &white) {
    return get_data(COMMAND_WHITE, white);
}

void LightDriver::scale_lux(uint16_t raw_counts, float &lux) {
    als_gain_t gain;
    als_integration_time_t integrationTime;
    get_gain(gain);
    get_integration_time(integrationTime);

    float factor1, factor2;

    switch (gain & 0x3) {
        case ALS_GAIN_x1:
            factor1 = 1.f;
            break;
        case ALS_GAIN_x2:
            factor1 = 0.5f;
            break;
        case ALS_GAIN_d8:
            factor1 = 8.f;
            break;
        case ALS_GAIN_d4:
            factor1 = 4.f;
            break;
        default:
            factor1 = 1.f;
            break;
    }

    switch (integrationTime) {
        case ALS_INTEGRATION_25ms:
            factor2 = 0.2304f;
            break;
        case ALS_INTEGRATION_50ms:
            factor2 = 0.1152f;
            break;
        case ALS_INTEGRATION_100ms:
            factor2 = 0.0576f;
            break;
        case ALS_INTEGRATION_200ms:
            factor2 = 0.0288f;
            break;
        case ALS_INTEGRATION_400ms:
            factor2 = 0.0144f;
            break;
        case ALS_INTEGRATION_800ms:
            factor2 = 0.0072f;
            break;
        default:
            factor2 = 0.2304f;
            break;
    }

    lux = raw_counts * factor1 * factor2;

    lux = lux * (1.0023f + lux * (8.1488e-5f + lux * (-9.3924e-9f + lux * 6.0135e-13f)));
}

bool LightDriver::get_als_lux(float &lux) {
    uint16_t raw_counts;
    bool status = get_als(raw_counts);
    scale_lux(raw_counts, lux);
    return status;
}

bool LightDriver::get_white_lux(float &lux) {
    uint16_t raw_counts;
    bool status = get_white(raw_counts);
    scale_lux(raw_counts, lux);
    return status;
}

bool LightDriver::send_data(uint8_t command, uint16_t data) {
    if (!twi_start()) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: TWI Unavailable (send_data)");
		#endif
        return false;
    }

    if (!twi_select(TWI_ALS_ADDRESS, Write)) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: Failed to request measurement (send_data)");
		#endif
        twi_stop();
        return false;
    }
    twi_write(command);
    twi_write(uint8_t(data & 0xff));
    twi_write(uint8_t(data >> 8));
    twi_stop();
    return true;
}

bool LightDriver::get_data(uint8_t command, uint16_t &data) {
    if (!twi_start()) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: TWI Unavailable (get_data)");
		#endif
        return false;
    }

    if (!twi_select(TWI_ALS_ADDRESS, Write)) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: Failed to request measurement (get_data write)");
		#endif
        twi_stop();
        return false;
    }
    twi_write(command);
    twi_read_ack();
    twi_stop();

    if (!twi_start()) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: TWI Unavailable (get_data)");
		#endif
        return false;
    }

    if (!twi_select(TWI_ALS_ADDRESS, Read)) {
		#if defined(DEBUG_LOG)
        SerialLogger::error("[Light]: Failed to request measurement (get_data read)");
		#endif
        twi_stop();
        return false;
    }
    data = twi_read_ack();
    data |= uint16_t(twi_read_nack() << 8);
    twi_stop();
    return true;
}
