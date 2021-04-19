#ifndef SERIAL_LOGGER_H_
#define SERIAL_LOGGER_H_

#include <boardsupport.h>

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
    public:
        /**
         * Print message
         * @param message Message to print
         */
        static void print(const char* message);

        /**
         * Print formatted message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        static void printf(const char* format, ...);

        /**
         * Print information message
         *
         * @param message Message to print
         */
        static void info(const char* message);

        /**
         * Print formatted information message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        static void infof(const char* format, ...);

        /**
         * Print warning message
         *
         * @param message Message to print
         */
        static void warn(const char* message);

        /**
         * Print formatted warning message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        static void warnf(const char* format, ...);

        /**
         * Print debug message
         *
         * @param message Message to print
         */
        static void debug(const char* message);

        /**
         * Print formatted debug message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        static void debugf(const char* format, ...);

        /**
         * Print error message
         *
         * @param message Message to print
         */
        static void error(const char* message);

        /**
         * Print formatted error message
         *
         * @param message Message to print
         * @param format Format that gets applied to the message
         */
        static void errorf(const char* format, ...);

    private:
        static void vprintf(const char* format, va_list args);
};

#endif
