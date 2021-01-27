#ifndef STATE_H_
#define STATE_H_

#include "StateMachine.h"

class State : public IState {
    protected:
		StateMachine* m_state_machine{};

	public:
		State(StateMachine* state_machine);

		void init() override;
		void update() override;
		void destroy() override;
};

#endif