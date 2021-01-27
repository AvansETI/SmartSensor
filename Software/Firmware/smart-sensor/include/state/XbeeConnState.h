//
// Created by Patrick on 02/06/2020.
//

#ifndef SMART_SENSOR_XBEECONNSTATE_H
#define SMART_SENSOR_XBEECONNSTATE_H


#include <board-support/state/State.h>
#include <board-support/util/SerialLogger.h>


/**
 * This state will handle transmit/receive data with the XBEE Module
 */
class XbeeConnState : public State {
    public:
        explicit XbeeConnState(StateMachine* s_machine);

        void init() override;

        void update() override;

        void destroy() override;

};


#endif //SMART_SENSOR_XBEECONNSTATE_H
