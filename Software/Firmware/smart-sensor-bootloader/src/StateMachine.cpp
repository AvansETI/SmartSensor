// class for handling states

#include <StateMachine.h>
#include <Serial.h>

int currenstateNo = 0;

STATE::STATE(int totalState, int totalEvents)
{
    this->totalStates = totalState;
    this->totalEvents = totalEvents;
    this->transitionno = 0;
}

void STATE::addState(int s, void (*event)(void))
{
    if (s < this->totalStates)
    {
        this->methods[s].loop = event;
    }
}

void STATE::addTransition(int state, int event, int nextState)
{
    // if ( state < this->totalStates && event < this->totalEvents ) {
    //     this->debug("FSM: Added transition for state " + String(state) + " and event " + String(event) + ": " + String(newState));
    //     this->transitions[state][event] = newState;
    // }

    if (state < this->totalStates && event < this->totalEvents)
    {
        this->transitions[this->transitionno].stateFrom = state;
        this->transitions[this->transitionno].eventRaised = event;
        this->transitions[this->transitionno].nextState = nextState;
        this->transitionno++;
    }
}

void STATE::raiseEvent(int event)
{
    if (this->currentState != -1 && event < this->totalEvents)
    {
        // go through the transitions to check if this one is valid
        // currently hardcoded to 10 because transition size
        for (int i = 0; i < 10; i++)
        {
            if (this->currentState == this->transitions[i].stateFrom)
            {
                if (event == this->transitions[i].eventRaised)
                {
                    int newState = this->transitions[i].nextState;
                    this->currentState = newState;
                }
            }
        }

        // if (this->transitions[this->currentState].eventRaised != -1)
        // {
        //     int newState = this->transitions[this->currentState].nextState;

        //     this->currentState = newState;
        //     // currenstateNo = newState;
        //     // switch (currenstateNo)
        //     // {
        //     // case 0:
        //     //     sendString("0\n");
        //     //     break;
        //     // case 1:
        //     //     sendString("1\n");
        //     //     break;
        //     // case 2:
        //     //     sendString("2\n");
        //     //     break;
        //     // case 3:
        //     //     sendString("3\n");
        //     //     break;
        //     // case 4:
        //     //     sendString("4\n");
        //     //     break;
        //     // case 5:
        //     //     sendString("5\n");
        //     //     break;
        //     // case 6:
        //     //     sendString("6\n");
        //     //     break;

        //     // default:
        //     //     break;
        //     // }
        // }
    }
}

void STATE::setup(int startState, int eventToRaise)
{
    if (this->currentState == -1 || startState < this->totalStates)
    {
        this->currentState = startState;
        // this->lastEvent = eventToRaise;
    }
}

void STATE::loop()
{
    if (this->currentState != -1 && this->currentState < this->totalStates)
    {
        this->methods[this->currentState].loop();
        // this->raiseEvent(this->lastEvent);
    }
}