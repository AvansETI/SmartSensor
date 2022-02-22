//class for state machine

struct methodCall
{
    void (*loop)(void);
};

struct transitionCall
{
    int stateFrom;
    int eventRaised;
    int nextState;
};



class STATE {
    private:
        int totalStates;
        int totalEvents;
        int currentState;
        int lastEvent;
        int transitionno;
        //until a good method for dynamic sizes is implemented, hardcoded as 10
        methodCall methods[10];
        transitionCall transitions[10];
    public:
        //constructor for state machine
        STATE(int totalStates, int totalEvents);

        //add state to machine, void (*event)(void) used to pass function
        void addState(int s, void (*event)(void));

        //add transition to next state
        void addTransition(int state, int event, int nextState);

        //raise event method
        void raiseEvent(int event);

        //sets up state machine with input data
        void setup(int startState, int eventToRaise);

        //method to call to loop
        void loop();
};