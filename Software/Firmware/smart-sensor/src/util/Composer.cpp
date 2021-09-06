//
// Created by Patrick on 28/05/2020.
//

#include <util/Composer.h>
#include <state/IdleState.h>
#include <state/PollState.h>
#include <SmartSensor.h>
#include <state/XbeeConnState.h>


Composer::Composer() : m_idle_state(IdleState(&m_s_machine)),
                        m_poll_state(PollState(&m_s_machine)),
                       m_conn_state(XbeeConnState(&m_s_machine)) {
    // Add here all of the internal components required to drive the sensors
}

void Composer::init() {
    // Behavior States

	//SerialLogger0.debug("Adding the states");

    this->m_s_machine.add_state(&m_idle_state, S_IDLE);
    this->m_s_machine.add_state(&m_poll_state, S_POLL);

    // Connection states
#if USE_XBEE == 1
    this->m_s_machine.add_state(&m_conn_state, S_XBEE);
#endif

	
    //SerialLogger0.info("Setting idle as start state");
    this->m_s_machine.set_state(S_IDLE);
}

void Composer::update() {
    this->m_s_machine.update();
}






