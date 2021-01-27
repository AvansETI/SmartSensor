#ifndef ISTATE_H_
#define ISTATE_H_

class IState {
	public:

        /**
         * Initializes the state
         */
        virtual void init() = 0;

        /**
         * Updates state
         */
		virtual void update() = 0;

		/**
		 * Destroys the state
		 */
		virtual void destroy() = 0;
};

#endif