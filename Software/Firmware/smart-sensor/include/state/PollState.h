//
// Created by Patrick on 02/06/2020.
//

#ifndef SMART_SENSOR_POLLSTATE_H
#define SMART_SENSOR_POLLSTATE_H

#include <board-support/state/State.h>
#include <board-support/util/SerialLogger.h>
#include <drivers/THSDriver.h>
#include <drivers/LightDriver.h>

/**
 * This state will
 */
class PollState : public State {
    private:
        THSDriver m_ths_driver;
        LightDriver m_light_driver;
    public:
        explicit PollState(StateMachine* s_machine);
        void init() override;

        void update() override;

        void destroy() override;
};

#endif //SMART_SENSOR_POLLSTATE_H