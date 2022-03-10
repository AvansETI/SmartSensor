//class for state machine

//Define used for the amount of states that will be added to the statemachine
#define AMOUNT_OF_STATES 4

//Define used for the amountn of transitions to be added to the statemachine
#define AMOUNT_OF_TRANSITIONS 4

//Struct made for the calling of methods that will be added to the states
struct methodCall
{
    void (*loop)(void);
};

//Struct made for the transition, containing what state the transition is called from, what event is needed and what state it should go to
struct transitionCall
{
    int stateFrom;
    int eventRaised;
    int nextState;
};


//Class implementing the Finite State Machine
class FiniteStateMachine {
    private:

        //Variables used to store the total amount of states and events, currently used to check you aren't adding too many
        //TODO: Possibly change the checks to use the defines instead of these variables
        int totalStates;
        int totalEvents;

        //variable used to store the current state, this is then used in the loop to execute the associated method
        int currentState;

        //Variable used in adding transitions to their array, transitionno will never exceed the total number of events
        //TODO: It feels like there should be a better way to do this
        int transitionno;

        //arrays to be used for the storage of different events and their transitions
        methodCall states[AMOUNT_OF_STATES];
        transitionCall transitions[AMOUNT_OF_TRANSITIONS];
    public:
        //constructor for state machine
        FiniteStateMachine(int totalStates, int totalEvents);

        //add state to machine, void (*event)(void) used to pass function
        void addState(int s, void (*method)(void));

        //add transition to next state
        void addTransition(int state, int event, int nextState);

        //raise event method
        void raiseEvent(int event);

        //sets up state machine with input data
        void setup(int startState, int eventToRaise);

        //method to call to loop
        void loop();
};