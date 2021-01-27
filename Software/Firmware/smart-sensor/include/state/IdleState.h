//
// Created by Patrick on 28/05/2020.
//

#ifndef SMART_SENSOR_IDLESTATE_H
#define SMART_SENSOR_IDLESTATE_H

#include <board-support/state/State.h>
#include <board-support/util/SerialLogger.h>
/**
 * This class will make sure that when the smart sensor has nothing to do,
 * that the modules on the smart sensor will go to sleep
 */
class IdleState : public State {
    public:
        explicit IdleState(StateMachine* s_machine);

        void init() override;

        void update() override;

        void destroy() override;
};


#endif //SMART_SENSOR_IDLESTATE_H
