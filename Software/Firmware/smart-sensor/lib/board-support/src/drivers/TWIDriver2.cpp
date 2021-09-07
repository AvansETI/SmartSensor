#include "board-support/drivers/TWIDriver2.h"

#if TWI0_ENABLED
TWIDriver2<0xB9, 0xB8, 0xBA, 0xBB, 0xBC> TWI2_0;

ISR(TWI0_vect) {
    using namespace details;

    future_frame& frame = get_future_frame(TWI2_0);

    // @TODO can most likely be removed
    if (frame.m_state != future_frame::State::NoValue) {
        return;
    }

    frame.m_value = get_data_register(TWI2_0);
    frame.m_status_code = get_status(TWI2_0);
    frame.m_state = future_frame::State::Value;

    TWIControlRegister cr{0};
    cr.bits.twi_enable = 1;
    TWI0_CR = cr;
}
#endif