//
// Created by Patrick on 02/06/2020.
//

#include <board-support/util/PinManager.h>
#include <SmartSensor.h>
#include "state/PollState.h"


PollState::PollState(StateMachine *s_machine) : State(s_machine) {
}

void PollState::init() {
    //PinManager::digital_write(STATUS_LED_2_PIN, HIGH);
    this->m_light_driver.begin();
}

void PollState::update() {
		// DEBUG SIGNAL
	PinManager::digital_write(STATUS_LED_1_PIN, HIGH);
    _delay_ms(1000);
    PinManager::digital_write(STATUS_LED_1_PIN, LOW);

	#if defined(DEBUG_LOG)
    	SerialLogger0.debug("Polling sensors");
	#endif

    uint16_t als;
    float als_lux;
    uint16_t white;
    float white_lux;

    if (this->m_light_driver.get_als(als)) {
		#if defined(DEBUG_LOG)
			SerialLogger0.infof("[Light]: ALS (raw lux): %d\n", als);
		#endif
	}
        

    if (this->m_light_driver.get_als_lux(als_lux)) {
		#if defined(DEBUG_LOG)
			SerialLogger0.infof("[Light]: ALS lux: %f\n", als_lux);
		#endif
	}
        

    if (this->m_light_driver.get_white(white))
		#if defined(DEBUG_LOG) 
        	SerialLogger0.infof("[Light]: White (raw lux): %d\n", white);
		#endif

    if (this->m_light_driver.get_white_lux(white_lux))
		#if defined(DEBUG_LOG)
        	SerialLogger0.infof("[Light]: White lux: %f\n", white_lux);
		#endif

    _delay_ms(500);
#if USE_XBEE == 1
    this->m_state_machine->set_state(S_XBEE);
#else
    this->m_state_machine->set_state(S_IDLE);
#endif
}

void PollState::destroy() {
    //PinManager::digital_write(STATUS_LED_2_PIN, LOW);
}
