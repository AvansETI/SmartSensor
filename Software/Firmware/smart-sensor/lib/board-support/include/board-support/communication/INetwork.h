#ifndef INETWORK_H_
#define INETWORK_H_

#include "board-support/util/DataTypes.h"

class INetwork {
	public:
        /**
         * Reads from network
         *
         * @return Data from network in bytes
         */
		virtual byte* read() = 0;

		 /**
		  * Sends data to network
		  *
		  * @param data Data which will be send
		  * @return Whether sending data was successful
		  */
		virtual bool send(byte* data) = 0;
};

#endif