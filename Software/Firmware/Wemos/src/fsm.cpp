// Avans University of Applied Sciences (Avans Hogeschool)
// Module: Intelligent Wireless Sensor Netwerken (IWSN)
// Author: Maurice Snoeren
// Date  : 05-02-2021
//

#include <fsm.h>

FSM::FSM(int totalStates, int totalEvents, bool debug) : totalStates(totalStates), totalEvents(totalEvents), debugEnabled(debug) {
    this->states.resize(totalStates);
}

void FSM::addTransition(int state, int event, int newState) {
    if ( state < this->totalStates && event < this->totalEvents ) { 
        this->debug("FSM: Added transition for state " + String(state) + " and event " + String(event) + ": " + String(newState));
        this->transitions[state][event] = newState;
    }
}

void FSM::addState(int s, std::function<void(void)> pre, std::function<void(void)> loop, std::function<void(void)> post) {
    if ( s < this->totalStates ) {
        this->debug("FSM: Added state: " + String(s));
        this->states[s].pre = pre;
        this->states[s].loop = loop;
        this->states[s].post = post;
    }
}

void FSM::raiseEvent(int e) {
    this->debug("FSM: Event raised " + String(e));

    if ( this->currentState != -1 &&  e < this->totalEvents ) {
        this->debug("FSM: finding event " + String(e) + " for state " + String(currentState));

        if ( this->transitions[currentState].find(e) != this->transitions[currentState].end() ) { // Check if event exists for the current state!
            int newState = this->transitions[this->currentState][e]; // get the new state from the transition map
            this->debug("FSM: Found new state for event: " + String(newState));

            this->states[this->currentState].post(); // Leaving current state
            this->states[newState].pre();            // Entering new state

            this->currentState = newState;
        }
    }
}

void FSM::setup(int state, int eventStateExecuted) {
    if ( this->currentState == -1 || state < this->totalStates ) { // Only set start state if not set yet!
        this->currentState = state;
        this->eventStateExecuted = eventStateExecuted;
        this->states[state].pre(); // Call the pre function!
    }
    this->loopTiming = millis();
}

void FSM::loop () {
    this->currentLoopTime = millis() - this->loopTiming;
    this->debug("FSM: Loop time: " + String(this->currentLoopTime) + "ms");
    this->loopTiming = millis(); // Restart timing calculation => TODO Above code takes also time!

    this->debug("FSM: current state " + String(this->currentState));
    if ( this->currentState != -1 &&  this->currentState < this->totalStates ) {
        this->states[this->currentState].loop();
        this->raiseEvent(this->eventStateExecuted);

    } else {
        this->debug("FSM: Error in the FSM loop, deadlock!");
    }
}

void FSM::debug(String text) {
    if ( this->debugEnabled ) {
        Serial.println(text);
    }
}

unsigned long FSM::getLoopTime() {
    return this->currentLoopTime;
}
