// class for handling states

#include <StateMachine.h>

STATE::STATE(int totalState, int totalEvents) {
    this->totalStates = totalState;
    this->totalEvents = totalEvents;
}

void STATE::addState(int s, void (*event)(void)) {
    if (s < this->totalStates)
    {
        this->methods[s].loop = event;   
    }
    
}

void STATE::addTransition(int state, int event, int nextState) {
    // if ( state < this->totalStates && event < this->totalEvents ) { 
    //     this->debug("FSM: Added transition for state " + String(state) + " and event " + String(event) + ": " + String(newState));
    //     this->transitions[state][event] = newState;
    // }

    if (state < this->totalStates && event < this->totalEvents)
    {
        this->transitions[state].stateFrom = state;
        this->transitions[state].eventRaised[event] = event;
        this->transitions[state].nextState[event] = nextState;
    }
    
}

void STATE::raiseEvent(int event) {
    if (this->currentState != -1 && event < this->totalEvents)
    {
        if (this->transitions[this->currentState].eventRaised[event] != -1)
        {
            int newState = this->transitions[this->currentState].nextState[event];

            this->currentState = newState;
        }
        
    }
    
}


void STATE::setup(int startState, int eventToRaise) {
    if (this->currentState == -1 || startState < this->totalStates)
    {
        this->currentState = startState;
        this->lastEvent = eventToRaise;
    }
    
}

void STATE::loop() {
    if (this->currentState != -1 && this->currentState < this->totalStates)
    {
        this->methods[this->currentState].loop();
        this->raiseEvent(this->lastEvent);
    }
    
}