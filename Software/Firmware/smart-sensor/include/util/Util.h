#pragma once
/**
 * @file       : Util.h
 * @description: Implements helping functions to make the life easier of the programmer.
 * @date       : 07-01-2022
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : 
 * @updates
 * 
 */
#include <stdint.h>
#include <string.h>

class Binary {
public:
    /* Returns the new state of the flags with the bit set given by flag. */
    static uint8_t setFlag(uint8_t flags, uint8_t flag) {
        return (flags | (1 << flag));
    }

    /* Returns the new state of the flags with the bit cleared given by flag. */
    static uint8_t clearFlag(uint8_t flags, uint8_t flag) {
        return (flags & ~(1 << flag));
    }

    /* Return true when flas is set, otherwise false. */
    static uint8_t isFlag(uint8_t flags, uint8_t flag) {
        return (flags & (1 << flag)) != 0;
    }

    /* Returns the new state of the flags with the bit set given by flag. */
    static uint16_t setFlag(uint16_t flags, uint8_t flag) {
        return (flags | (1 << flag));
    }

    /* Returns the new state of the flags with the bit cleared given by flag. */
    static uint16_t clearFlag(uint16_t flags, uint8_t flag) {
        return (flags & ~(1 << flag));
    }

    /* Return true when flas is set, otherwise false. */
    static uint16_t isFlag(uint16_t flags, uint8_t flag) {
        return (flags & (1 << flag)) != 0;
    }

};

class Generic {
public:
    static uint8_t strlen(const char* text) {
        int8_t size = 0;
        while (text[size] != '\0') size++;
        return size;
    }

    static uint8_t char2int(char c) {
        return (c - '0');
    }
};

template<uint8_t T>
class String {
private:
    char data[T];

public:
    String() {}
    String(const char* str) {
        this->set(str);
    }

    void set(const char* str) {
        //strcpy((this->data, str);
        uint8_t i;
        for ( i=0; i < Generic::strlen(str) && i < T-1; ++i ) {
            this->data[i] = str[i];
        }
        this->data[i] = '\0';
    }

    char* get() {
        return this->data;
    }

};
