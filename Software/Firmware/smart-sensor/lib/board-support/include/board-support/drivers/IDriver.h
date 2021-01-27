#ifndef IDRIVER_H_
#define IDRIVER_H_

class IDriver {
	public:
        /**
         * Gets value from driver
         */
		virtual void get_value() = 0;
};

#endif