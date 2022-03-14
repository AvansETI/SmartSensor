// class for handling states

#include <StateMachine.h>
#include <Communication.h>>

//Constructor for the FiniteStateMachine, totalstates and totalevents are passed along so they can be used in their checks
//transitionno is also set to 0 so that it can later be used when adding transitions
FiniteStateMachine::FiniteStateMachine(int totalState, int totalEvents)
{
    this->totalStates = totalState;
    this->totalEvents = totalEvents;
    this->transitionno = 0;
}

//method for adding states, the state and it's associated method are passed along
//If the state does not exceed the total number of states then it's method is added to the array at the states position
void FiniteStateMachine::addState(int s, void (*method)(void))
{
    if (s < this->totalStates)
    {
        this->states[s].loop = method;
    }
}

//method for adding transitions, the state from which the transition can be called, the associated event and the state it should transtion to are passed along
//If neither the state nor the event exceed the totals then the transition is added at the current position of transitionno and that variable is raised by 1
void FiniteStateMachine::addTransition(int state, int event, int nextState)
{

    if (state < this->totalStates && event < this->totalEvents)
    {
        this->transitions[this->transitionno].stateFrom = state;
        this->transitions[this->transitionno].eventRaised = event;
        this->transitions[this->transitionno].nextState = nextState;
        this->transitionno++;
    }
}

//Method for handling raised events, the raised event is passed along
void FiniteStateMachine::raiseEvent(int event)
{
    //If there is a state and the event does not exceed the amount of events continue
    if (this->currentState != -1 && event < this->totalEvents)
    {
        //Check if the transition is valid
        for (int i = 0; i < AMOUNT_OF_TRANSITIONS; i++)
        {
            //Check if the current state has an associated transition
            if (this->currentState == this->transitions[i].stateFrom)
            {
                //Check if that transition corresponds to the currently raised event
                //If it does, go to the state indicated
                if (event == this->transitions[i].eventRaised)
                {
                    int newState = this->transitions[i].nextState;
                    this->currentState = newState;
                }
            }
        }
    }
}

//Method used for setup of the State Machine, should be called once all states and transitions are added
void FiniteStateMachine::setup(int startState, int eventToRaise)
{
    //If the startstate does not exceed the amount of states it is set as the current state
    if (startState < this->totalStates)
    {
        this->currentState = startState;
    }
}

//Method used to loop through the State Machine
void FiniteStateMachine::loop()
{
    //If there is a current state and that state does noet exceed the amount of states call it's loop method
    if (this->currentState != -1 && this->currentState < this->totalStates)
    {
        this->states[this->currentState].loop();
    }
}