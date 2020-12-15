#ifndef PIN_MANAGER_H_
#define PIN_MANAGER_H_

#include <boardsupport.h>
#include "PinMode.h"
#include "PinPort.h"
#include "PinUtil.h"
#include "DigitalValues.h"
#include <board-support/drivers/PWMDriver.h>

class PinManager {
	public:
        /**
         * Set mode of specified pin
         *
         * @param pin The pin where the mode will be applied on
         * @param mode Mode which the pin will be set on
         */
		static void set_mode(PinPort pin, PinMode mode);

		/**
		 * Write digital signal to a port
		 *
		 * @param port The port where the signal will be written to
		 * @param value Value of the signal
		 */
        static void digital_write(PinPort port, DigitalValues value);

		/**
		 * Read digital signal from pin
		 *
		 * @param pin Pin where the signal will be read from
		 * @return Value of the signal
		 */
        static uint8_t digital_read(PinPort pin);

		/**
		 * Write analog signal to a port using PWM
		 *
		 * @param pin Port where the signal will be written to
		 * @param value The duty cycle for the signal that is going to be written in percentages (0%-100%)
		 */
        static void analog_write(PinPort pin, uint8_t value);

		/**
		 * Read analog signal from pin
		 *
		 * @param pin Pin where the signal will be read from
		 * @return Value of the signal
		 */
        static uint16_t analog_read(PinPort pin);

    private:
        /**
         * Initializes ADC (Analog to Digital Converter)
         */
        static void init_adc();

        /**
         * Checks if ADC has been initialized
         *
         * @return Boolean value whether ADC is initialized or not
         */
        static bool is_adc_initialized();
};

#endif