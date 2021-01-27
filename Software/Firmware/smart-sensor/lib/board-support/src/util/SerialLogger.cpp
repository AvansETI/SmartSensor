#include "board-support/util/SerialLogger.h"
#include "board-support/drivers/UsartDriver.h"

void SerialLogger::print(const char* message) {
    while (*message) {
        Usart0.transmitChar(*message++);
    }
}

void SerialLogger::printf(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void SerialLogger::info(const char *message) {
#if LOGGER_LEVEL >= 1
    print("[INFO] ");
    print(message);
    Usart0.transmitChar('\n');
#endif
}

void SerialLogger::infof(char* format, ...) {
#if LOGGER_LEVEL >= 1
    print("[INFO] ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

void SerialLogger::warn(char* message) {
#if LOGGER_LEVEL >= 2
    print("\033[1;33m[WARN]\033[0m ");
    print(message);
    Usart0.transmitChar('\n');
#endif
}

void SerialLogger::warnf(char* format, ...) {
#if LOGGER_LEVEL >= 2
    print("\033[1;33m[WARN]\033[0m ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

void SerialLogger::debug(char* message) {
#if LOGGER_LEVEL >= 3
    print("\033[1;34m[DEBU]\033[0m ");
    print(message);
    Usart0.transmitChar('\n');
#endif
}

void SerialLogger::debugf(char* format, ...) {
#if LOGGER_LEVEL >= 3
    print("\033[1;34m[DEBU]\033[0m ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

void SerialLogger::error(char* message) {
#if LOGGER_LEVEL >= 0
    print("\033[1;31m[ERRO]\033[0m ");
    print(message);
    Usart0.transmitChar('\n');
#endif
}

void SerialLogger::errorf(char* format, ...) {
#if LOGGER_LEVEL >= 0
    print("\033[1;31m[ERRO]\033[0m ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

void SerialLogger::vprintf(char* format, va_list arg_p) {
    const char* ptr;

    char ch;
    char* v_str;
    int16_t v_int16;
    uint16_t v_uint16;
    float v_float32;

    for(ptr = format; *ptr != '\0'; ptr++) {
        ch = *ptr;

        if (ch == '%') {
            ptr++;
            ch = *ptr;

            switch (ch) {
                case 'd':
                    v_int16 = va_arg(arg_p, signed int);
                    if (v_int16 < 0) {
                        v_int16 = -v_int16;
                        Usart0.transmitChar('-');
                    }
                    Usart0.transmitNumber(UsartDriver::DECIMAL, v_int16, 0xffu);
                    break;
                case 'u':
                    v_uint16 = va_arg(arg_p, uint16_t);
                    Usart0.transmitNumber(UsartDriver::DECIMAL, v_uint16, 0xffu);
                    break;
                case 'b':  /* Argument type is of binary,Read int and convert to binary */
                    v_uint16 = va_arg(arg_p, uint16_t);

                    Usart0.transmitNumber(UsartDriver::BINARY, v_uint16, 16);
                    break;
                case 'c':
                    ch = va_arg(arg_p, int);
                    Usart0.transmitChar(ch);
                    break;
                case 'f':
                    v_float32 = va_arg(arg_p, double);
                    Usart0.transmitFloat(v_float32);
                    break;
                case 's':
                    v_str = va_arg(arg_p, char*);
                    print(v_str);
                    break;
                case '%':
                    Usart0.transmitChar('%');
                    break;
            }
        } else {
            Usart0.transmitChar(ch);
        }
    }
}