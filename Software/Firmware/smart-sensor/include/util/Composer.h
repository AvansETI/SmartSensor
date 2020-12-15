#ifndef SMART_SENSOR_COMPOSER_H
#define SMART_SENSOR_COMPOSER_H

#include <board-support/state/StateMachine.h>
#include <board-support/util/SerialLogger.h>
#include <state/IdleState.h>
#include <state/PollState.h>
#include <state/XbeeConnState.h>

/**
 * This class will initialize all of the classes required in this program
 * It will make sure the state machine is initialized and all of the tasks are created
 * @author Patrick de Jong
 */
class Composer {
    private:
        StateMachine m_s_machine;
        IdleState m_idle_state;
        PollState m_poll_state;
        XbeeConnState m_conn_state;

    public:
        /**
         * This has to be ran first it will create all of the states and tasks to be ran.
         */
        Composer();

        void init();
        void update();
};


#endif //SMART_SENSOR_COMPOSER_H
