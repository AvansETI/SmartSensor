/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <boards/Board.h>

#include <stdlib.h>

#include <avr/pgmspace.h>
#include <util/delay.h>

/* Define in the main.c which board you would like to compile to. In the future
   it is possible that the software detects the version itself. */
#if defined(SMARTSENSOR_BOARD_1_2)
    #include "boards/v1_2/Board.h"
    #pragma message "SmartSensor v1.2 has been selected to be compiled."
    SmartSensorBoardV1_2 board;

#else
    #include "boards/BoardV1_2.h"
    #pragma message "SMARTSENSOR_BOARD_X_X has not been defined, using the newest SmartBoard version v1.2."
    SmartSensorBoardV1_2 board;
#endif

SmartSensorBoard* SmartSensorBoard::getBoard() {
    return &board;
}

void SmartSensorBoard::addTask(ITask *task, const char* taskName) {
    if ( this->totalDrivers < SMARTSENSOR_MAX_TASKS) {
        uint8_t result = task->setup();

        this->debug_P(PSTR("Adding task: "));
        this->debug_P(taskName);

        if ( result == 0 ) {
            this->drivers[this->totalDrivers] = task;
            this->totalDrivers++;
            this->debug_P(PSTR(": Succes\n"));
        
        } else {
            this->debugf_P(PSTR(": Error %d\n"), result);
        }
    
    } else {
        this->debug_P(PSTR("Adding task: "));
        this->debug_P(taskName);
        this->debugf_P(PSTR(": Max drivers reached\n"), taskName);
    }
}

void SmartSensorBoard::setup() {
    this->loopTimstamp = this->millis();
    this->resetCause = MCUSR; // Read the reset cause
    MCUSR = 0x00; // Reset the flags
    this->measurementReceivedTimestamp = 0;
    this->totalMeasurementsSend = 0;
    this->sendInitMessage();
}

void SmartSensorBoard::loop() {
    char data[MESSAGE_LENGTH + 20];

    for ( uint8_t i=0; i < this->totalDrivers; ++i ) { // Loop through all the drivers
        this->drivers[i]->loop(this->millis());
    }

    if ( this->queueMessages.size() > 0 ) { // Handle all the message
        Message *message = this->queueMessages.peek();

        if ( message->getType() == MessageType::MEASUREMENT ) {
            if ( this->sendDataStringAvailable() ) {
                this->measurementReceivedTimestamp = this->millis()/100;
                sprintf_P(data, PSTR("%s:%s\n"), this->getID(), this->queueMessages.pop()->getMessage());
                this->sendDataString(data);
                this->totalMeasurementsSend++;
            }

        } else if ( message->getType() == MessageType::TIMESTAMP ) {
            if ( this->sendDataStringAvailable() ) {
                sprintf_P(data, PSTR("%s:%s\n"), this->getID(), this->queueMessages.pop()->getMessage());
                this->sendDataString(data);
            }
            
            
        } else if ( message->getType() == MessageType::COMMAND ) { // TODO
            this->processCommand(this->queueMessages.pop()->getMessage());            

        } else {
            this->queueMessages.pop();
        }
    }

    // When no measurements pop in after 500ms, request the timestamp
    if ( this->measurementReceivedTimestamp != 0 && (this->millis()/100) - this->measurementReceivedTimestamp > 5 ) {
        this->measurementReceivedTimestamp = 0;
        if ( this->totalMeasurementsSend > 0 ) {
            this->getActualTimestamp();
            if ( this->sendDataStringAvailable() ) {
                sprintf_P(data, PSTR("%s:lt:%d\n"), this->getID(), this->loopTime); // Send also the loop time.
                this->sendDataString(data);
            }
        }
    }

    this->loopTime = ( (SMARTSENSOR_RUNNING_AVERAGE_LOOP_TIME-1)*this->loopTime + (this->millis() - this->loopTimstamp) )/SMARTSENSOR_RUNNING_AVERAGE_LOOP_TIME; // Running average of 10 loops
    //this->debugf_P(PSTR("Loop time %d ms\n"), this->loopTime); // Show the actual loop timing in the serial
    this->loopTimstamp = this->millis();
}

// Documentation: http://www.cplusplus.com/reference/cstdio/vsprintf/
void SmartSensorBoard::debugf( const char* message, ...) { // TODO: Maybe move these functions to Serial0 (think of it)?
    char buffer[50];
    va_list args;
    va_start(args, message);
    vsprintf (buffer, message, args);
    va_end (args);

    this->debug(buffer);
}

void SmartSensorBoard::debugf_P( const char* message, ...) {
    char buffer[50];
    va_list args;
    va_start(args, message);
    vsprintf_P(buffer, message, args);
    va_end (args);

    this->debug(buffer);
}

bool SmartSensorBoard::resetCauseWatchdog() {
    return (this->resetCause & ( 1 << WDRF )) != 0;
}

bool SmartSensorBoard::resetCauseExternalReset() {
    return (this->resetCause & ( 1 << EXTRF )) != 0;
}

void SmartSensorBoard::addMessage(Message  message) {
    this->queueMessages.add(message);
}

void SmartSensorBoard::waitOnSendDataStringAvailable() {
    while ( !this->sendDataStringAvailable() ) {}
}

