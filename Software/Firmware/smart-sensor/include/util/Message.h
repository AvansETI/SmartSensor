#pragma once
/**
 * @file       : Message.h
 * @description: This class implements the Message that can be received by the SmartMeter.
 * @date       : 08-01-2022
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 * 
 */
#include <stdint.h>
#include <string.h>

#define MESSAGE_LENGTH 30

enum class MessageType {
    EMPTY,
    UNKNOWN,
    MEASUREMENT,
    COMMAND,
    TIMESTAMP,
};

class Message {
private:
    MessageType messageType;
    char message[MESSAGE_LENGTH];

public:
    Message() {
        this->messageType = MessageType::EMPTY;
        message[0] = '\0';
    }

    Message(MessageType type, char message[MESSAGE_LENGTH]) {
        this->messageType = type;
        strcpy(this->message, message);
    }

    MessageType getType() {
        return this->messageType;
    }

    char* getMessage() {
        return this->message;
    }

    uint8_t getMessageLength() {
        return MESSAGE_LENGTH;
    }
};

class MessageInterface {
public:

    /**
     * @brief add a message to be printed to the serial peripheral
     * 
     * @param message the message to be printed
     */
    virtual void addMessage(Message  message) = 0;
};

