#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "IState.h"
#include <boardsupport.h>

class StateMachine {
    private:
        IState* m_cur_state;
        IState* m_prev_state;
        IState* states[MAX_NUM_STATES];

    public:
        /**
         * state to the array, It only adds the state
         * @param state state The state you want to add
         * @param index Which position
         * @returns if it is successful or not
         */
        bool add_state(IState* state, int index);

        /**
         * Add the state that you want to add
         * @param s_index Which index state you want to be
         * @return if setting the start state was successful
         */
        bool set_state(int s_index);

        /**
        * Start the update method
        */
        void update();

        /**
         * Reverts state
         * @return Whether reverting state was successful
         */
        bool revert_state();


        /**
         * Getter for the field m_current_state
         * @return an IState pointer
         */
        IState* get_current_state();

        /**
        * Getter for the field m_prev_state
        * @return an IState pointer
        */
        IState* get_prev_state();

        /**
         * Get the state object
         * @param index The number of which index you want
         * @return IState object of the the index that is given in the parameter
         */
        IState* get_state_on_index(int index);
};

#endif