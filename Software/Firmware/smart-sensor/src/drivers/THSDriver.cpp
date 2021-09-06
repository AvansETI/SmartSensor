#include <boardsupport.h>
#include <board-support/util/SerialLogger.h>

#include "drivers/THSDriver.h"

THSDriver::THSDriver() : TWIDriver(TWI0) {
}

bool THSDriver::update() {
    if (!twi_start()) {
		#if defined(DEBUG_LOG)
        	SerialLogger0.error("[THS]: TWI Unavailable");
		#endif
        return false;
    }

    if (!twi_select(TWI_THS_ADDRESS, Write)) {
		#if defined(DEBUG_LOG)
        	SerialLogger0.error("[THS]: Failed to request measurement");
		#endif
        twi_stop();
        return false;
    }

    twi_read_ack();

    twi_stop();

    // Wait around 40ms to receive measurement, should be more then 36,65ms according to datasheet.
    _delay_ms(40);

    twi_start();
    if (!twi_select(TWI_THS_ADDRESS, Read)) {
		#if defined(DEBUG_LOG)
        	SerialLogger0.error("[THS]: Failed to read measurement");
		#endif
        twi_stop();
        return false;
    }

    uint8_t hum_h = twi_read_ack();
    uint8_t hum_l = twi_read_ack();

    // Last two bits are status
    m_last_status = static_cast<THSStatus>(hum_h >> 6);

    if (m_last_status != THSStatus::NORMAL) {
        if (m_last_status == THSStatus::STALE) {
			#if defined(DEBUG_LOG)
            	SerialLogger0.warn("[THS]: Using stale measurement, try decreasing update rate.");
			#endif
        } else {
			#if defined(DEBUG_LOG)
            	SerialLogger0.warn("[THS]: Incorrect status received, is THS in command mode?");
			#endif
            twi_stop();
            return false;
        }
    }

    // Ignore last two bits and combine two 8bits
    uint16_t humidity = ((hum_h & 0x3f) << 8u) | hum_l;


    uint8_t temp_h = twi_read_ack();
    uint8_t temp_l = twi_read_ack();

    // Combine high and low into 16 bit value.
    // Ignore first two bits according to datasheet
    uint16_t temperature = ((temp_h << 6u) | (temp_l >> 2));


    // Tell sensor we are done.
    twi_read_nack();
    twi_stop();

    // Convert digital counts to % and Celsius
    m_last_humidity = ((float) humidity / (float) (pow(2, 14) - 2)) * 100.0f;
    m_last_temperature = ((float) temperature / (float) (pow(2, 14) - 2.0f)) * 165.0f - 40.0f;

    return true;
}

THSDriver::THSStatus THSDriver::get_status() {
    return m_last_status;
}

float THSDriver::get_humidity() const {
    return m_last_humidity;
}

float THSDriver::get_temperature() const {
    return m_last_temperature;
}

