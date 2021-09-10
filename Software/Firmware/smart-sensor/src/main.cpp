/**
 * Entry point of the application
 * @date   : 12 May 2020
 * @author : Patrick de Jong, Paul Hobbel, Sergen Peker, Carlos Cadel, Floris Bob van Elzelingen, Maurice Snoeren (MS)
 * @version: 0.9 test version
 * @updates
 *  10-09-2021: MS: Updating the code to a mature version
 * 
 */

#ifndef UNIT_TEST
#include <stdio.h>
#include <boardsupport.h>
#include <board-support/drivers/TWIDriver.h>
#include <board-support/util/PinManager.h>
#include <board-support/util/SerialLogger.h>

#include <board-support/drivers/UsartDriver.h>
#include <board-support/drivers/TWIDriver2.h>
#include "drivers/THSDriver2.h" // HELP: Why driver 2?
#include "drivers/ALSDriver.h" // HELP: Why not LightDriver?
#include "drivers/WemosDriver.h"
#include "drivers/RTCDriver.h"
#include "drivers/CO2Driver.h"
#include "drivers/TPMDriver.h"
#include "drivers/SHTC3Driver.h"

#define FIRMWARE_VERSION "v0.9"

// Hard coded coordinator variable to select the required functionality
// TODO: The software needs to detect this automatically
volatile bool is_coordinator = false;

// HELP: I do not know what this is?!
volatile char bitbuffer = 0;

volatile unsigned char usart1_buffer[256];
volatile uint8_t usart1_buffer_read_index = 0;
volatile uint8_t usart1_buffer_write_index = 0;

// TODO: This is a cyclic buffer that should be implemented by a class?!
void usart1_buffer_write(unsigned char c) {
    usart1_buffer[usart1_buffer_write_index] = c;
    usart1_buffer_write_index = usart1_buffer_write_index == 0xFF ? 0 : usart1_buffer_write_index + 1;
}

// TODO: This is a cyclic buffer that should be implemented by a class?!
bool usart1_buffer_has_data() {
    return usart1_buffer_read_index != usart1_buffer_write_index;
}

// TODO: This is a cyclic buffer that should be implemented by a class?!
unsigned usart1_buffer_read() {
    const auto res = usart1_buffer[usart1_buffer_read_index];
    usart1_buffer_read_index = usart1_buffer_read_index == 0xFF ? 0 : usart1_buffer_read_index + 1;
    return res;
}

// INTERRUPT HANDLING: Recieved byte via the UART1
ISR(USART1_RX_vect) {
    // HELP: What is happening here? Does it belong to the coordinator?
    //if (is_coordinator) UDR2 = UDR1;
    //else usart1_buffer_write(UDR1);
    usart1_buffer_write(UDR1);
}

// INTERRUPT HANDLING: Recieved byte via the UART2
ISR(USART2_RX_vect) {
    // HELP: What is happening here?
    UDR1 = UDR2; // HELP: Is this correct??
}

// HELP: What is happening here?
// HELP: this belongs to the XBee driver? And in fact to the communication class!
char xbee_buffer[512];
uint16_t xbee_buffer_index = 0;

void xbee_buffer_reset() {
    xbee_buffer_index = 0;
}


// HELP: Explain?!
void send_to_xbee(const char* msg, uint16_t msg_length) {

    auto length = msg_length + 14;

    uint64_t checksum = 0;
    auto send_byte = [&](uint8_t byte) { checksum += byte; Usart1.transmitChar(byte); };

    // MS: Is this API mode? page 59
    // MS: This code only supports star networks!!
    // MS: Also not a lot functionality created here!
    Usart1.transmitChar(0x7E);
    Usart1.transmitChar(length >> 8);
    Usart1.transmitChar(length & 0xFF);
    send_byte(0x10); // MS: 10 
    send_byte(1);    // MS: 01
    send_byte(0); // MS: Coordinator address 64 bit
    send_byte(0);
    send_byte(0);
    send_byte(0);
    send_byte(0);
    send_byte(0);
    send_byte(0);
    send_byte(0);
    send_byte(0xFF); // MS: 16 bit FF/FE when 0x0000 is used
    send_byte(0xFE);
    send_byte(0); // 
    send_byte(0);
    
    for (uint16_t i = 0; i < msg_length; ++i) { // MS: NO CHECK ON LENGTH!!
        checksum += *msg;
        Usart1.transmitChar(*msg++);
    }
    Usart1.transmitChar(0xFF - (checksum & 0xFF));
}

// Method to print a 1 or 0 depending on the boolean value to reduce the memory footprint!
void serial_print_boolean(bool value) {
    if (value) SerialLogger0.print("1\n"); else SerialLogger0.print("0\n");
}

// HELP: Explain?!
// MS: I think this does not work properly?
// MS: It is possible in rare circumstances for the destination to receive a data packet, but for the source to not receive
//     the network acknowledgment. In this case, the source will retransmit the data, which could cause the 
//     Module operation Modes of operation
//     destination to receive the same data packet multiple times. The XBee modules do not filter out duplicate
//     packets. The application should include provisions to address this potential issue
uint8_t read_from_xbee(char *buffer) {
    //while (true) UDR0 = Usart1.receiveChar();

    auto debug_byte = []{auto val = Usart1.receiveChar(); /*UDR0 = val;*/ return val; };

    while (debug_byte() != 0x7E); // HELP: POTENTIAL SECURITY ISSUE!!
    //SerialLogger0.print("in frame\n");    

    uint8_t h = debug_byte();
    uint8_t l = debug_byte();

    uint16_t length = (((uint16_t)h) << 8) | ((uint16_t)l);

    //_delay_ms(2);

    //SerialLogger0.printf("length := %d (0x%x 0x%x)\n", (int)length, (uint16_t)h, (uint16_t)l);

    uint16_t msg_bytes_read = 0;
    auto read_byte = [&]{++msg_bytes_read; return debug_byte(); };
    
    uint8_t frame_type = 0;
    if (length) frame_type = read_byte();
    if (frame_type == 0xFF) {
        for (uint16_t i = 0; i < 17; ++i) read_byte();
        for (uint16_t i = 0; msg_bytes_read < length; ++i)
            buffer[i] = read_byte();
        buffer[length - 17] = '\0';
    } else {
        for (uint16_t i = 1; i < length; ++i) read_byte();
    }
    //uint8_t checksum = debug_byte(); // unused!
    return frame_type;
}

int main() {
    /* Print the versions to the serial */
	SerialLogger0.print("SmartSensor ");
    SerialLogger0.print(BOARD_VERSION);
    SerialLogger0.print(", Firmware ");
    SerialLogger0.print(FIRMWARE_VERSION);
    SerialLogger0.print("\n");

    /* Setup the hardware */
    TWI2_0.setBitrate(TWI0_SCL_CLOCK);
    TWI2_1.setBitrate(TWI1_SCL_CLOCK);

    PinManager::set_mode(CO2_INT_PIN, INPUT);
    //PinManager::set_mode(CO2_ENABLE_PIN, OUTPUT); // NOT USED ANYMORE
    PinManager::set_mode(CO2_WAKE_PIN, OUTPUT);

    //PinManager::set_mode(LS_ENABLE_PIN, OUTPUT); // NOT USED ANYMORE
    //PinManager::set_mode(THS_ENABLE_PIN, OUTPUT); // NOT USED ANYMORE

    // HELP: What is this?
    PinManager::set_mode(ATM_MOSI_PIN, OUTPUT);
    PinManager::digital_write(ATM_MOSI_PIN, HIGH);
    PinManager::set_mode(ATM_MISO_PIN, OUTPUT);
    PinManager::digital_write(ATM_MISO_PIN, HIGH);
      
    //PinManager::set_mode(XBEE_ENABLE_PIN, OUTPUT); // NOT USED ANYMORE
    //PinManager::digital_write(XBEE_ENABLE_PIN, LOW); // NOT USED ANYMORE
    // HELP: What is this? It looks like communication with XBee_D18?! 
    PinManager::set_mode(PinPortA0, OUTPUT);
    PinManager::digital_write(PinPortA0, LOW);

    PinManager::set_mode(XBEE_SLEEP_PIN, INPUT); // HELP: INPUT? What is this then?
    //PinManager::set_mode(XBEE_SS_PIN, OUTPUT); // Why not?

    PinManager::set_mode(STATUS_LED_1_PIN, OUTPUT);

    //_delay_ms(1000);
    //PinManager::digital_write(CO2_ENABLE_PIN, HIGH); // NOT USED ANYMORE
    PinManager::digital_write(CO2_WAKE_PIN, HIGH);

    //PinManager::digital_write(LS_ENABLE_PIN, HIGH); // NOT USED ANYMORE
    //PinManager::digital_write(THS_ENABLE_PIN, LOW); // NOT USED ANYMORE

    /* Blink led for one second and a flash to show it has been started. */
    PinManager::digital_write(STATUS_LED_1_PIN, LOW);
    _delay_ms(1000);
    PinManager::digital_write(STATUS_LED_1_PIN, HIGH);
    _delay_ms(1000);
    PinManager::digital_write(STATUS_LED_1_PIN, LOW);
    _delay_ms(100);
    PinManager::digital_write(STATUS_LED_1_PIN, HIGH);
    _delay_ms(1000);

    // Eventually, the main method should only call sample sensors and get a list back with sensor data. This is too specific
    SHTC3Driver shtc3;

    // HELP: What is this?
    // TODO: Logic to detect wheter the software required to be a coordinator.
    if (is_coordinator) { // send xbee to wemos (HELP: What do you mean?)
        UCSR1B = 0b1001'1000;
        UCSR2B = 0b1001'1000;
        while (true); //HELP: ??
    } else {
        // HELP: What is this?
        //UCSR1B = 0b1001'1000;
    }

    /* Enable the interrupts */
    sei();
    _delay_ms(10);

    /* Perform hardware check! */
    SerialLogger0.print("RTC:");
    serial_print_boolean(RTC.isConnected());
    _delay_ms(1);

    SerialLogger0.print("CLOCK:");
    serial_print_boolean(RTC.startClock());
    _delay_ms(1);

    SerialLogger0.printf("THS:%d\n", shtc3.setup());
    _delay_ms(1);

    SerialLogger0.print("ALS:");
    serial_print_boolean(ALS.isConnected());
    ALS.setupSensor();
    _delay_ms(1);

    // HELP: What is this? Why not created a lib for this like the rest TPMDriver?! Lazy?
    SerialLogger0.print("TPM:");
    serial_print_boolean(TPM.isConnected());
    TPM.setup();
    _delay_ms(1);

    SerialLogger0.print("CO2:");
    serial_print_boolean(CO2.isConnected());
    CO2.setupSensor();
    _delay_ms(1);

    // HELP: ?!
    bool flip = false;

    // HELP: ?!
    //uint8_t data_to_write = 1; // Unused

    // HELP: does it belong to the XBee driver?!
    xbee_buffer_reset();

    // The unique sensor ID that should be taken from the TPM chip
    // TODO: The software needs to get a unique ID based on the hardware automatically (tpm-0000)
    // When the TPM is not available it can use the SHT sensor unique ID: sht-0000
    char sensor_id[20];
    sprintf(sensor_id, "smartsensor-sht-%04X", shtc3.getID());


    // HELP: I do not understand this?!
    if (is_coordinator) while(true); 

   // SerialLogger0.print("sending init to coordinator...");
   // MS: This should have been implemented in a method!
    xbee_buffer_index = sprintf(xbee_buffer, "!SmartSensor-%d"
    , *sensor_id);
    send_to_xbee(xbee_buffer, xbee_buffer_index);
    //SerialLogger0.print("done\n");   

    // MS: No state machine has been implemented.
    // MS: No generic method of measuring has been implemented?!
    // MS: A very simple approach have been implemented!
    // MS: I do not see any initialization of the XBee and also not the status of the XBee?!
    // MS: The XBee driver does not implement anything around the configuration of the XBee?!
    // MS: The coordinator does not measure things?!
    // MS: No configuration like sampling frequency as discussed implemented. (Less far?!?!)
    // MS: System does not check nor wait for the XBee?!
    // MS: Requirement to take measurements at a specified sampling rate.
    while (true) {
        _delay_ms(2000);

        shtc3.loop();

        if ( shtc3.isDataValid() ) {
            SerialLogger0.print("shtc3: data is valid.");
            xbee_buffer_reset();
            xbee_buffer_index = sprintf(xbee_buffer,
R"!(
{
    "id": "%s",
    "measurements": [{
        "timestamp": "%s",
        "temperature": %f,
        "humidity": %f
    }]
}
)!"
            ,sensor_id , generate_ISO_8601_string(*RTC.getTime()), (double) shtc3.getTemperature(), (double) shtc3.getHumidity());
            send_to_xbee(xbee_buffer, xbee_buffer_index);
            
            SerialLogger0.print(xbee_buffer);

        } else {
            SerialLogger0.print("shtc3: data is not valid.");
        }

        PinManager::digital_write(STATUS_LED_1_PIN, (flip = !flip) ? HIGH : LOW);
    }

}

#endif