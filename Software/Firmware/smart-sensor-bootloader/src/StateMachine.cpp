// class for handling states

#include <StateMachine.h>

STATE::STATE(int totalState, int totalEvents) {
    this->totalStates = totalState;
    this->totalEvents = totalEvents;
}

void STATE::addTransition(int state, int event, int nextState) {
    // if ( state < this->totalStates && event < this->totalEvents ) { 
    //     this->debug("FSM: Added transition for state " + String(state) + " and event " + String(event) + ": " + String(newState));
    //     this->transitions[state][event] = newState;
    // }

    if (state < this->totalStates && event < this->totalEvents)
    {
        /* code */
    }
    
}

void STATE::raiseEvent(int event) {

}


void STATE::setup(int startState, int eventToRaise) {

}

void STATE::loop() {

}