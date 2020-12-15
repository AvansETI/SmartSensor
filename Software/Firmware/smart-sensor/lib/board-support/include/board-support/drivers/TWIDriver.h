#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_

#include <boardsupport.h>

#if TWI0_ENABLED
    #ifndef TWI0_SR
        #error "Please define TWI0_SR in board configuration"
    #endif

    #ifndef TWI0_BR
        #error "Please define TWI0_BR in board configuration"
    #endif

    #ifndef TWI0_CR
        #error "Please define TWI0_CR in board configuration"
    #endif

    #ifndef TWI0_DR
        #error "Please define TWI0_DR in board configuration"
    #endif
#endif

#if TWI1_ENABLED
    #ifndef TWI1_SR
        #error "Please define TWI1_SR in board configuration"
    #endif

    #ifndef TWI1_BR
        #error "Please define TWI1_BR in board configuration"
    #endif

    #ifndef TWI1_CR
        #error "Please define TWI1_CR in board configuration"
    #endif

    #ifndef TWI1_DR
        #error "Please define TWI1_DR in board configuration"
    #endif
#endif

class TWIDriver {
	public:
        /**
         * Initialize TWIDriver, make sure to call this at least once!
         */
        static void init();
		enum Instance { TWI0 = 0, TWI1 = 1 };
		enum SelectMode { Write = 0 , Read = 1 };

		/**
		 * TWI Driver constructor
		 * @param instance TWI bus to use, either TWO0 or TWI1
		 */
        TWIDriver(Instance instance);

    protected:
        Instance m_instance;

        /**
         * Starts a new TWI transaction
         */
        bool twi_start();

        /**
         * Stops the TWI transaction.
         */
        void twi_stop();

        /**
         * Wait for ongoing transmission to be received by slave.
         */
        void twi_wait();

        /**
         * Select a slave address and set the mode to Read or Write
         * @param addr the slave address
         * @param mode the mode
         */
        bool twi_select(uint8_t addr, SelectMode mode);

        /**
         * Writes data to the selected slave.
         * @param data the data to send
         */
        void twi_write(uint8_t data);

        /**
         * Read one byte from TWI slave.
         * @return byte read from TWI slave.
         */
        uint8_t twi_read_ack();

        /**
         * Read one byte from TWI slave, read is followed by a stop condition
         * @return byte read from TWI slave.
         */
        uint8_t twi_read_nack();
};

#if TWI0_ENABLED
static TWIDriver TWI0 = TWIDriver(TWIDriver::TWI0);
#endif

#if TWI1_ENABLED
static TWIDriver TWI1 = TWIDriver(TWIDriver::TWI1);
#endif

#endif