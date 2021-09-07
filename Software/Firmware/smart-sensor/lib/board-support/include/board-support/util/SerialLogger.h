#ifndef SERIAL_LOGGER_H_
#define SERIAL_LOGGER_H_

#include <boardsupport.h>
#include <board-support/drivers/UsartDriver.h>

#ifndef LOGGER_LEVEL
/**
 * ERROR    0
 * INFO     1
 * WARN     2
 * DEBUG    3
 */
#define LOGGER_LEVEL 1
#endif

class SerialLogger {
    UsartDriver& m_driver;

    public:
        SerialLogger(UsartDriver& driver);
        SerialLogger() = delete;
        SerialLogger(const SerialLogger&) = delete;

        /**
         * Print message
         * @param message Message to print
         */
        void print(const char* message);

        /**
         * Print formatted message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        void printf(const char* format, ...);

        /**
         * Print information message
         *
         * @param message Message to print
         */
        void info(const char* message);

        /**
         * Print formatted information message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        void infof(const char* format, ...);

        /**
         * Print warning message
         *
         * @param message Message to print
         */
        void warn(const char* message);

        /**
         * Print formatted warning message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        void warnf(const char* format, ...);

        /**
         * Print debug message
         *
         * @param message Message to print
         */
        void debug(const char* message);

        /**
         * Print formatted debug message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        void debugf(const char* format, ...);

        /**
         * Print error message
         *
         * @param message Message to print
         */
        void error(const char* message);

        /**
         * Print formatted error message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        void errorf(const char* format, ...);

    private:
        void vprintf(const char* format, va_list args);
};


#if USART0_ENABLED
static SerialLogger SerialLogger0{Usart0};
#endif

#if USART1_ENABLED
static SerialLogger SerialLogger1{Usart1};
#endif

#if USART2_ENABLED
static SerialLogger SerialLogger2{Usart2};
#endif

#endif
