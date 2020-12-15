#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include <board-support/util/DDR.h>
#include <board-support/util/PinUtil.h>
#include <board-support/util/PinManager.h>
#include <board-support/util/PWMPrescaler.h>

#define USABLE_PWM_WRITE_PIN_PORTS_COUNT 9
#define USABLE_PWM_WRITE_PIN_PORTS_16_BIT_COUNT 5
#define USABLE_PWM_WRITE_PIN_PORTS_8_BIT_COUNT 2
#define USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC_COUNT 2

/**
 * All usable PinPorts where a PWM signal can be written to
 */
const PinPort USABLE_PWM_WRITE_PIN_PORTS[USABLE_PWM_WRITE_PIN_PORTS_COUNT] = {
        PinPortB3, PinPortB4,   // <- 8-bit timers
        PinPortD5, PinPortD4,   // <- 16-bit timers
        PinPortD7, PinPortD6,   // <- 8-bit timers with async operations
        PinPortB6, PinPortB7,   // <- 16-bit timers
        PinPortC4               // <- 16-bit timer
};

/**
 * All PinPorts that use an 16-bit timer to write a PWM signal to
 */
const PinPort USABLE_PWM_WRITE_PIN_PORTS_16_BIT[USABLE_PWM_WRITE_PIN_PORTS_16_BIT_COUNT] = {
        PinPortD5, PinPortD4, PinPortB6, PinPortB7, PinPortC4
};

/**
 * All PinPorts that use an 8-bit timer to write a PWM signal to
 */
const PinPort USABLE_PWM_WRITE_PIN_PORTS_8_BIT[USABLE_PWM_WRITE_PIN_PORTS_8_BIT_COUNT] = {
        PinPortB3, PinPortB4
};

/**
 * All PinPorts that use an 8-bit timer with async operations to write a PWM signal to
 */
const PinPort USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC[USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC_COUNT] = {
        PinPortD7, PinPortD6
};

class PWMDriver {
    public:
        /**
         * Write a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS
         *
         * If the duty_cycle is 0, the {@link #stop_writing(PinPort)} method will be called
         *
         * These PinPorts have different timers which have an impact on the signal you want to write. The PinPorts with their kind of timer they use are listed below:
         *
         * 8-bit timers: PinPortB3, PinPortB4
         *
         * 8-bit timers with async operations: PinPortD7, PinPortD6
         *
         * 16-bit timers: PinPortD5, PinPortD4, PinPortB6, PinPortB7, PinPortC4
         *
         * @param pin_port PinPort where the signal will be written to
         * @param duty_cycle Duty cycle for the signal that is going to be written in percentages (0%-100%)
         * @param prescaler Prescaler that will be used when writing the signal. PWMPrescaler clkIO_1 will be used when there is no prescaler specified.
         * @return Whether the signal is successfully being written to the specified pin_port
         */
        static bool write(PinPort pin_port, uint8_t duty_cycle, PWMPrescaler prescaler = PWMPrescaler::clkIO_1);

        /**
         * Stop writing a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS
         *
         * @param pin_port  PinPort where the ongoing signal is being written to
         * @return Whether the signal stopped successfully
         */
        static bool stop_writing(PinPort pin_port);

        /**
         * todo
         */
        static uint32_t read(PinPort pin_port);
    private:
        /**
         * Available PWMCom's to use with the PWMDriver
         */
        enum PWMCom {
            COMA, COMB
        };

        /**
         * Write a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS_16_BIT
         *
         * @param pin_port      PinPort where the signal will be written to
         * @param tccra         TCCRxA that belongs to the specified pin_port
         * @param icr           ICRx that belongs to the specified pin_port
         * @param ocra          OCRxA that belongs to the specified pin_port
         * @param tccrb         TCCRxB that belongs to the specified pin_port
         * @param duty_cycle    Duty cycle for the signal that is going to be written in percentages (0%-100%)
         * @param prescaler     Prescaler that will be used when writing the signal
         * @param com           COMx that belongs to the specified pin_port
         * @return Whether the writing of a signal was successful
         */
        static bool write_using_16_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint16_t& icr,
                                             volatile uint16_t& ocra, volatile uint8_t& tccrb, uint8_t duty_cycle,
                                             PWMPrescaler prescaler, PWMCom com);

        /**
         * Write a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS_8_BIT
         *
         * @param pin_port      PinPort where the signal will be written to
         * @param tccra         TCCRxA that belongs to the specified pin_port
         * @param ocra          OCRxA that belongs to the specified pin_port
         * @param tccrb         TCCRxB that belongs to the specified pin_port
         * @param duty_cycle    Duty cycle for the signal that is going to be written in percentages (0%-100%)
         * @param prescaler     Prescaler that will be used when writing the signal
         * @param com           COMx that belongs to the specified pin_port
         * @return Whether the writing of a signal was successful
         */
        static bool write_using_8_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                            volatile uint8_t& tccrb, uint8_t duty_cycle, PWMPrescaler prescaler,
                                            PWMCom com);

        /**
         * Write a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC
         *
         * @param pin_port      PinPort where the signal will be written to
         * @param tccra         TCCRxA that belongs to the specified pin_port
         * @param ocra          OCRxA that belongs to the specified pin_port
         * @param tccrb         TCCRxB that belongs to the specified pin_port
         * @param duty_cycle    Duty cycle for the signal that is going to be written in percentages (0%-100%)
         * @param prescaler     Prescaler that will be used when writing the signal
         * @param com           COMx that belongs to the specified pin_port
         * @return Whether the writing of a signal was successful
         */
        static bool write_using_8_bit_async_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                                  volatile uint8_t& tccrb, uint8_t duty_cycle, PWMPrescaler prescaler,
                                                  PWMCom com);

        /**
         * Stop writing a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS_8_BIT or #USABLE_PWM_WRITE_PIN_PORTS_8_BIT_ASYNC
         *
         * @param pin_port  PinPort where tho ongoing signal is being written to
         * @param tccra     TCCRxA that belongs to the specified pin_port
         * @param ocra      OCRxA that belongs to the specified pin_port
         * @param tccrb     TCCRxB that belongs to the specified pin_port
         * @return Whether the signal was stopped successfully
         */
        static bool stop_writing_using_8_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint8_t& ocra,
                                                   volatile uint8_t& tccrb);

        /**
         * Stop writing a PWM signal to an usable PinPort from #USABLE_PWM_WRITE_PIN_PORTS_16_BIT
         *
         * @param pin_port  PinPort where tho ongoing signal is being written to
         * @param tccra     TCCRxA that belongs to the specified pin_port
         * @param ocra      OCRxA that belongs to the specified pin_port
         * @param tccrb     TCCRxB that belongs to the specified pin_port
         * @param icr       ICRx that belongs to the specified pin_port
         * @return Whether the signal was stopped successfully
         */
        static bool stop_writing_using_16_bit_timer(PinPort pin_port, volatile uint8_t& tccra, volatile uint16_t& icr,
                                                    volatile uint16_t& ocra, volatile uint8_t& tccrb);

        /**
         * Checks if a PinPort array contains the specified PinPort
         *
         * @param pin_port          PinPort to check if it is in the specified PinPort's array
         * @param pin_ports         Array from PinPort to check if it contains pin_port
         * @param pin_ports_size    Size of the array from pin_ports (amount of values the array holds)
         * @return Whether the pin_port exists in pin_ports
         */
        static bool contains_pin_port(PinPort pin_port, const PinPort pin_ports[], uint8_t pin_ports_size);
};

#endif