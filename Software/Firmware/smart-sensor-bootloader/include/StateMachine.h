//class for state machine

class STATE {
    private:
        int totalStates;
        int totalEvents;
        int currentState;
    public:
        //constructor for state machine
        STATE(int totalStates, int totalEvents);

        //add transition to next state
        void addTransition(int state, int event, int nextState);

        //raise event method
        void raiseEvent(int event);

        //sets up state machine with input data
        void setup(int startState, int eventToRaise);

        //method to call to loop
        void loop();
};