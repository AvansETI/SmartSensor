//
// Created by Patrick on 02/06/2020.
//

#include <string.h>
#include <stdio.h>

#include <SmartSensor.h>
#include <board-support/util/PinManager.h>

#include "state/XbeeConnState.h"
#include "drivers/XBeeDriver.h"
#include "sensor-data/XBeeData.h"


#define PACKET_SIZE 255


XbeeConnState::XbeeConnState(StateMachine *s_machine) : State(s_machine) {
}

void XbeeConnState::init() {
	#if defined(DEBUG_LOG)
    SerialLogger::debug("- [XBEE] - initing XBEE");
	#endif
}

void XbeeConnState::update() {
	// DEBUG SIGNAL
	PinManager::digital_write(STATUS_LED_1_PIN, HIGH);
    _delay_ms(50);
    PinManager::digital_write(STATUS_LED_1_PIN, LOW);


	//SerialLogger::debug("- [XBEE] - In the XBEE state update loop");
	

	XBeeData data = XBeeData(20.0f, 15.0f, 600.0f);
	//XBeeDriver::send(data);
	
	PinManager::digital_write(STATUS_LED_2_PIN, HIGH);
    _delay_ms(1000);
    PinManager::digital_write(STATUS_LED_2_PIN, LOW);
    
	this->m_state_machine->set_state(S_IDLE);
}

void XbeeConnState::destroy() {

}
