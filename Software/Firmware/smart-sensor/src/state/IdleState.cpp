//
// Created by Patrick on 28/05/2020.
//


#include <SmartSensor.h>
#include <board-support/util/PinManager.h>
#include "state/IdleState.h"

IdleState::IdleState(StateMachine* s_machine) : State(s_machine) {
}

void IdleState::init() {
    // PinManager::digital_write(STATUS_LED_1_PIN, HIGH);
    // _delay_ms(50);
    // PinManager::digital_write(STATUS_LED_1_PIN, LOW);
}

void IdleState::update() {
	#if defined(DEBUG_LOG)
    	SerialLogger0.debug("Went to idle state, sleeping for 20 seconds...");
	#endif
    _delay_ms(2000);
    this->m_state_machine->set_state(S_POLL);
}

void IdleState::destroy() {

}
