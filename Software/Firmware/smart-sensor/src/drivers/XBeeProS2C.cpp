#include <drivers/XBeeProS2C.h>

#include <stdlib.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <tasks/Atmega324PBSerial1.h>
#include <tasks/Atmega324PBSerial0.h>

#include <boards/Board.h>
uint8_t XBeeProS2C::setup() {
    XBEEPROS2C_SLEEP_DDR = XBEEPROS2C_SLEEP_DDR | (1 << XBEEPROS2C_SLEEP_PIN); // Set the pin as output to drive the sleep pin
    this->wakeup();

    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();

    x->setCallback(this); // Recieve all characters on serial 1 to me.

    return 0;
}

#include <avr/wdt.h>
uint8_t XBeeProS2C::loop(uint32_t millis) {
    // TEST
    //7E 00 0D 90 00 7D 33 A2 00 41 8F 98 08 71 3B 01 31 6C  => correct API 2
    //7E 00 0D 90 00 13 A2 00 41 8F 98 08 71 3B 01 31 6C => correct API 1
    //   00 0D 90 00 13 A2 00 41 8F 98 08 71 3B 01 31 6C => recieved API 1 ( first time rest not correct.)
    SmartSensorBoard::getBoard()->debug("TEST\n");
    char frame[100];
    uint8_t counter = 0;
    uint8_t problems = 0;
    char c;

    while ( true ) {
        wdt_reset();

        while ( !(UCSR1A & (1<<RXC)) ) { wdt_reset(); }; // Is a character available?
        c = UDR1;

        if ( c == 0x7E ) {
            if ( counter != 0 ) { // frame recieved!
                if ( counter > 10 ) {
                    SmartSensorBoard::getBoard()->debugf("Frame recieved: %d (%d)!\n", counter, problems);
                    for (uint8_t i=0; i < counter; i++ ) {
                        uint8_t h2 = (frame[i] & 0b11110000) >>4;
                        uint8_t h1 = frame[i] & 0b00001111;
                        Atmega324PBSerial0::getInstance()->transmitChar((h2 < 10 ? h2+'0' : h2-10+'A'));
                        Atmega324PBSerial0::getInstance()->transmitChar((h1 < 10 ? h1+'0' : h1-10+'A'));
                        Atmega324PBSerial0::getInstance()->transmitChar(' ');

                    }
                    Atmega324PBSerial0::getInstance()->transmitChar('\n');
                } else {
                    problems++;
                }
            }
            counter = 0;

        } else {
            frame[counter] = c;
            counter++;
        }
    }



    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();

    // TODO: Check timeout when it is not in a waiting state!

    switch (this->state) {
    case 0: // Start to write and read configuration of the XBee
        this->atStart();
        this->state++;
        this->timestamp = millis;
        break;

    case 1:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            if ( this->checkResultOk() ) {
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBeeProS2C: Found\n"));
                this->state++;

            } else {
                this->state = 0; // Start over?!
            }
            this->stateReciever = XBeeProS2CStateReciever::IDLE;

        } else { // Not processing yet!
            if ( millis - this->timestamp > XBEEPROS2C_TIMEOUT_TIME_S ) { 
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBeeProS2C: Not found\n"));
                this->state = XBEEPROS2C_STATE_NOTFOUND;
            }
        }
        break;

    case 2:
        this->atSetPanId(XBEEPROS2C_PAN_ID);
        this->state++;
        break;

    case 4:
        this->atSetCoordinator(this->isCoordinator);
        this->state++;
        break;

    case 6:
        this->atSetNodeIdentifier(SmartSensorBoard::getBoard()->getID());
        this->state++;
        break;

    case 8:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATAP 1\r")); // 0 Transparant, 1 API, 2 API with escapes
        this->state++;
        break;

    case 10:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATAO 0\r"));
        this->state++;
        break;

    case 12:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATDH 0\r"));
        this->state++;
        break;
    
    case 14:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATDL 0\r"));
        this->state++;
        break;

    case 16:
        this->atWrite();
        this->state++;
        break;

    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
    case 17:
    case 33:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            if ( this->checkResultOk() ) {
                this->state++;
    
            } else {
                this->state = 0; // start over? TODO
            }
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
        }
        break;

    case 18: // Get PAN ID
        this->atGetPanId();
        this->state++;
        break;

    case 19:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C PAN ID: %s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 20:
        this->atGetSerialNumberHigh();
        this->state++;
        break;
    
    case 21:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C SERIAL: %s"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 22:
        this->atGetSerialNumberLow();
        this->state++;
        break;
    
    case 23:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("%s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 24:
        this->atGetCoordinatorEnable();
        this->state++;
        break;
    
    case 25:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C Coordinator: %s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 26:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATNI\r"));
        this->state++;
        break;
    
    case 27:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C Node Identifier: %s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 28:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATVR\r"));
        this->state++;
        break;
    
    case 29:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C Firmware Version: %s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    case 30:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATHV\r"));
        this->state++;
        break;
    
    case 31:
        if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C Hardware Version: %s\n"), this->recieveBuffer);
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            this->state++;
        }
        break;

    
    case 32:
        Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATCN\r")); // Exit command mode
        this->state++;
        this->timestamp = millis;
        break;

    case 34:
        this->state++;
        break;

    case 35: // Waiting on recieve a message from XBee or sending data to the coordinator
        if ( !this->isCoordinator ) {
            if ( false && !Atmega324PBSerial1::getInstance()->isBusy() && millis - this->timestamp > 5000 ) {
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBEE SEND\n"));
                //Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("temperature:24.5\r"));
                this->timestamp = millis;

                Atmega324PBSerial1::getInstance()->transmitChar(0x7E);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x0F);
                Atmega324PBSerial1::getInstance()->transmitChar(0x10);
                Atmega324PBSerial1::getInstance()->transmitChar(0x01);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0xFF);
                Atmega324PBSerial1::getInstance()->transmitChar(0xFE);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x31);
                Atmega324PBSerial1::getInstance()->transmitChar(0xC0);
                //7E 00 0F 10 01 0000 0000 0000 0000 FFFE 00 00 31 C0

            }

        } else {
            if ( !Atmega324PBSerial1::getInstance()->isBusy() && millis - this->timestamp > 10000 ) {
                SmartSensorBoard::getBoard()->debug_P(PSTR("XBEE SEND\n"));
                //Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("temperature:24.5\r"));
                this->timestamp = millis;

                Atmega324PBSerial1::getInstance()->transmitChar(0x7E);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x0F);
                Atmega324PBSerial1::getInstance()->transmitChar(0x10);
                Atmega324PBSerial1::getInstance()->transmitChar(0x01);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0xFF);
                Atmega324PBSerial1::getInstance()->transmitChar(0xFE);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x00);
                Atmega324PBSerial1::getInstance()->transmitChar(0x31);
                Atmega324PBSerial1::getInstance()->transmitChar(0xC0);

            }

            if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING ) {
                SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C Message: %s\n"), this->recieveBuffer);
                this->stateReciever = XBeeProS2CStateReciever::IDLE;
            }

            if ( this->stateReciever == XBeeProS2CStateReciever::PROCESSING_API ) {
                SmartSensorBoard::getBoard()->debugf_P(PSTR("XBeeProS2C API Message: %s\n"), this->recieveBuffer);
                this->stateReciever = XBeeProS2CStateReciever::IDLE;
            }
        }
        break;

    // case waiting 1->recieved message from XBee as coordinator (relay to gateway), 2->sending message to coordinator


    }

    return 0;
}

uint8_t XBeeProS2C::reset() {
    return 0;
}

uint8_t XBeeProS2C::sleep() {
    XBEEPROS2C_SLEEP_PORT = XBEEPROS2C_SLEEP_PORT | (1 << XBEEPROS2C_SLEEP_PIN); // Sleep 
    return 0;
}

uint8_t XBeeProS2C::wakeup() {
    XBEEPROS2C_SLEEP_PORT = XBEEPROS2C_SLEEP_PORT & ~(1 << XBEEPROS2C_SLEEP_PIN); // Wake 
    return 0;
}

#include <avr/wdt.h>
void XBeeProS2C::recievedCharacter(char c) {


    switch (this->stateReciever) {
    case XBeeProS2CStateReciever::IDLE:
        if ( c != '\r') {
            //if ( c == 0x7E ) { // API detected!
                //this->stateReciever = XBeeProS2CStateReciever::BUSY_API_LENGTH_H;
                //this->recieveBufferPointer = 0;
                //SmartSensorBoard::getBoard()->debug("GOT API FRAME\n");

            //} else {
                this->recieveBuffer[0] = c;
                this->recieveBufferPointer = 1;
                this->stateReciever = XBeeProS2CStateReciever::BUSY;
            //}
        }
        break;

    case XBeeProS2CStateReciever::BUSY:
        this->recieveBuffer[this->recieveBufferPointer] = c;

        if ( this->recieveBufferPointer > XBEEPROS2C_RECIEVE_BUFFER_AMOUNT - 1 ) { // Error, beyond the buffer!
             SmartSensorBoard::getBoard()->debug_P(PSTR("XBeeProS2C: Buffer overflow!\n"));
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
        }

        if ( c == '\r' ) { // Ready!
            this->recieveBuffer[this->recieveBufferPointer] = '\0'; // replace \r with \0 end character
            this->stateReciever = XBeeProS2CStateReciever::PROCESSING;
        }

        this->recieveBufferPointer++;
        break;

    case XBeeProS2CStateReciever::PROCESSING: // Help, the previous data has not been processed yet!
    case XBeeProS2CStateReciever::PROCESSING_API: // Help, the previous data has not been processed yet!
        {
            Atmega324PBSerial0* s = Atmega324PBSerial0::getInstance();
            SmartSensorBoard::getBoard()->debugf_P(PSTR("XBEE Problem: %d\n"), c);
            // TODO: Startover?
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
        }
        break;

    case XBeeProS2CStateReciever::BUSY_API_LENGTH_H:
        this->stateReciever = XBeeProS2CStateReciever::BUSY_API_LENGTH_L;
        //SmartSensorBoard::getBoard()->debug("GOT LENGTH H\n");
        this->apiLength = c << 8;
        break;

    case XBeeProS2CStateReciever::BUSY_API_LENGTH_L:
        this->stateReciever = XBeeProS2CStateReciever::BUSY_API_API_ID;
        this->apiLength = this->apiLength | c;
        //SmartSensorBoard::getBoard()->debugf("GOT LENGTH: %d\n", this->apiLength);
        break;

    case XBeeProS2CStateReciever::BUSY_API_API_ID:
        this->stateReciever = XBeeProS2CStateReciever::BUSY_API_FRAME_ID;
        this->apiId = c;
        this->apiLength--;
        this->apiChecksumCalculated = c;
        //SmartSensorBoard::getBoard()->debugf("GOT API ID: %d\n", this->apiId);
        break;

    case XBeeProS2CStateReciever::BUSY_API_FRAME_ID:
        this->stateReciever = XBeeProS2CStateReciever::BUSY_API_DATA;
        this->apiFrameId = c;
        this->apiChecksumCalculated = this->apiChecksumCalculated + c;
        this->apiLength--;
        //SmartSensorBoard::getBoard()->debugf("GOT API FRAME ID: %d\n", this->apiFrameId);
        break;

    case XBeeProS2CStateReciever::BUSY_API_DATA:
        if ( this->apiLength != 0 ) {
            this->recieveBuffer[ this->recieveBufferPointer ] = c;
            this->apiChecksumCalculated = this->apiChecksumCalculated + c;
            this->recieveBufferPointer++;
            //SmartSensorBoard::getBoard()->debugf("GOT API DATA[%d]: %d\n", this->apiLength, this->apiFrameId);
            this->apiLength--;

        } else {
            this->apiChecksum = c;
            this->apiChecksumCalculated = this->apiChecksumCalculated + c;
            //this->stateReciever = XBeeProS2CStateReciever::PROCESSING_API;
            this->stateReciever = XBeeProS2CStateReciever::IDLE;
            //SmartSensorBoard::getBoard()->debugf("GOT API CHECKSUM: %d, calc: %d\n", this->apiChecksum, this->apiChecksumCalculated);
        }
        break;


    }
}

void XBeeProS2C::enableCoordinator() {
    this->isCoordinator = true;
}

void XBeeProS2C::atStart() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("+++"));
}

void XBeeProS2C::atGetPanId() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATID\r"));
}

void XBeeProS2C::atGetCoordinatorEnable() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATCE\r"));
}

void XBeeProS2C::atGetSerialNumberHigh() {
    Atmega324PBSerial1* x = Atmega324PBSerial1::getInstance();
    x->printAsync_P(PSTR("ATSH\r"));
}

void XBeeProS2C::atGetSerialNumberLow() {
    Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATSL\r"));
}

bool XBeeProS2C::checkResultOk() {
    return ( this->recieveBuffer[0] == 'O' && this->recieveBuffer[1] == 'K' );
}

void XBeeProS2C::atSetPanId(const char* id) {
    char m[15];
    sprintf_P(m, PSTR("ATID %s\r"), id);
    Atmega324PBSerial1::getInstance()->printAsync(m);
}

void XBeeProS2C::atSetCoordinator(bool enable) {
    char m[15];
    sprintf_P(m, PSTR("ATCE %d\r"), enable);
    Atmega324PBSerial1::getInstance()->printAsync(m);
}

void XBeeProS2C::atSetNodeIdentifier(const char* id) {
    char m[30];
    sprintf_P(m, PSTR("ATNI %s\r"), id);
    Atmega324PBSerial1::getInstance()->printAsync(m);
}

void XBeeProS2C::atWrite() {
    Atmega324PBSerial1::getInstance()->printAsync_P(PSTR("ATWR\r"));
}
