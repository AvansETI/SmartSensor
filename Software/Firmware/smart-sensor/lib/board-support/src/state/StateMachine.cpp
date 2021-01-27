#include "board-support/state/StateMachine.h"


bool StateMachine::add_state(IState *state, int index) {
    // Checking if index is not going over the max_index
    if(index < (MAX_NUM_STATES - 1)) {
        // Adding state to the next index
        this->states[index] = state;
        return true;
    }
    return false;
}

bool StateMachine::set_state(int s_index) {
    if (s_index <= (MAX_NUM_STATES -1) && s_index >= 0) {
        if(this->states[s_index] != nullptr) {
            // Check if there is a prev state
            // Replace it with the old current state
            this->m_prev_state = this->m_cur_state;
            // Set the new current state
            this->m_cur_state = this->states[s_index];

            if(this->m_prev_state != nullptr) {
                // Destroy old prev state
                this->m_prev_state->destroy();
            }

            // Run the initializer of that state
            this->m_cur_state->init();
            return true;
        }
        return false;
    }
    return false;
}

bool StateMachine::revert_state() {
    if (m_prev_state != nullptr) {
        IState* prev_state = nullptr;
        if(m_cur_state != nullptr) {
            prev_state = m_cur_state;
            m_cur_state->destroy();
        }
        if(prev_state != nullptr) {
            this->m_prev_state = prev_state;
        }
        this->m_cur_state = m_prev_state;
        this->m_cur_state->init();
        return true;
    }
    return false;
}

void StateMachine::update() {
    if (m_cur_state != nullptr) {
        m_cur_state->update();
    }
}


IState *StateMachine::get_current_state() {
    return this->m_cur_state;
}

IState *StateMachine::get_prev_state() {
    return this->m_prev_state;
}

IState *StateMachine::get_state_on_index(int index) {
    return this->states[index];
}