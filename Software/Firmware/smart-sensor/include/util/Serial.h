#pragma once
/**
 * @file       : Serial.h
 * @description: This file contains all generic classes for the Serial interface.
 * @date       : 08-01-2022
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 * 
 */

/* Interface: SerialRecievedCharacter */
class SerialRecievedCharacter {
public:
    virtual void recievedCharacter(char c) = 0;
};

template<uint8_t T>
class SerialBuffer {
private:
    char buffer[T];
    uint8_t pointer;

public:
    SerialBuffer() {
        this->reset();
    }

    uint8_t add(char c) {
        if ( this->pointer < (T-1) ) {
            this->buffer[this->pointer] = c;
            this->buffer[this->pointer+1] = '\0';
            this->pointer++;
            return 0;
        }   

        return 1;
    }

    void reset() {
        this->pointer = 0;
        this->buffer[this->pointer] = '\0';
    }

    char* get() {
        this->buffer[T-1] = '\0';
        return this->buffer;
    }

    void copy(char toStr[T]) {
        strcpy(toStr, this->buffer);
    }
};
