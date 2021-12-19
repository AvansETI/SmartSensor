// Avans University of Applied Sciences (Avans Hogeschool)
// Module: Intelligent Wireless Sensor Netwerken (IWSN)
// Author: Maurice Snoeren
// Date  : 05-02-2021
// Author: Maurice Snoeren
//
#pragma once

#include <map>
#include <vector>
#include <functional>

#include <Arduino.h>

/* Define FSM transition structure (advanced using pre and post methods) */
struct FSMMethods {
   std::function<void(void)> pre;  // When the state is active, this method is called once at start
   std::function<void(void)> loop; // When the state is active, this method is continously called
   std::function<void(void)> post; // When the state is deactivated, this method is called once
};

/* Finite State Machine class that implements the state machine functionality */
class FSM {
    private:
        // The transaction map holds the transaction. If the transaction is not in the map
        // it does not exist. Usage: newState = map[state][event].
        std::map<int, std::map<int, int>> transitions;

        // The states vector contains the three callback methods for each state.
        std::vector<FSMMethods> states;

        // Total number of states that the state machine contains.
        int totalStates;

        // Total number of events that can be used with the state machine.
        int totalEvents;

        // The current state that the state machine is in.
        int currentState;

        // The last event that has been raised.
        int eventStateExecuted;

        // When debugging is enabled, messages are send on the Serial connection.
        bool debugEnabled;

        // To calculate the loop timing, the variable loopTiming is used.
        unsigned long loopTiming;

        // After each loop, the total loop time in milliseconds is calculated and 
        // that is stored in this variable.
        unsigned long currentLoopTime;

    public:
        // Initialized the FSM class.
        FSM(int totalStates, int totalEvents, bool debugEnabled = false);

        // Add a state to the state machine. Make sure the order is correct!
        void addState(int s, std::function<void(void)> pre, std::function<void(void)> loop, std::function<void(void)> post);

        // Adds a new transition to the state machine that will be used to get
        // the next state based on the raised event.
        void addTransition(int state, int event, int nextState);

        // Raise an event. When the event is found in the transision matrix, the
        // state machine will go to the next state automatically.
        void raiseEvent(int e);

        // Call this once before the state machine is used. It initializes
        // the objects and start with the given state. Furthermore, it is
        // required to set the event that represents the event that need
        // to be raised when a state has been executed.
        void setup(int state, int eventStateExecuted);

        // Call this within the loop of your main application. After the loop
        // an event is raised that has been given by the eventStateExecuted
        // of the setup class.
        void loop();

        // Returns the current loop time in milliseconds.
        unsigned long getLoopTime();

    private:
        // Used by the class to provide debug messages in case things go wrong.
        void debug(String text);

};