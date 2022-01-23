// Avans University of Applied Sciences (Avans Hogeschool)
// Project: SmartSensor
// Author: Maurice Snoeren
// Date  : 10-01-2022
//
#pragma once

#include <Arduino.h>
#include <Queue.h>

// String buffer to hold the largest string of the memory mapping, see the description.
char _buffer[150];

// Total measurements have been configured by the mapping
#define MEASUREMENTS_TOTAL 10

// Measurement mapping
const char* const measurement_mapping[] PROGMEM = {
    "lt", // loop_time
    "te", // temperature
    "hu", // humidity
    "li", // light
    "c2", // CO2
    "gi", // gpio
    "ai", // analog
    "rs", // rs232
    "tv", // tvoc
    "ts", // timestamp, no measurement ... just for translation!
};

const char* const measurement_name[] PROGMEM = {
    "loop_time", // loop_time
    "temperature", // temperature
    "humidity", // humidity
    "light", // light
    "co2", // CO2
    "gpio", // gpio
    "analog", // analog
    "rs232", // rs232
    "tvoc", // tvoc
    "timestamp", // timestamp, no measurement ... just for translation!
};

const char* const measurement_description[] PROGMEM = {
    "Loop time is the time how long it takes to go through all the tasks.", // loop_time
    "Measured temperature.", // temperature
    "Measured humidity.", // humidity
    "Measurement of the ambient light.", // light
    "Measurement of the CO2.", // CO2
    "The status of the GPIO pins, based on the configuration.", // gpio
    "Is configured the analogue value of the respective pins.", // analog
    "The bytes that has been received on the RS232 connection. Setup gpio 6-7 as S!", // rs232
    "The equivalent Total Volatile Organic Compound (eTVOC).", // tvoc
    "-", // timestamp, no measurement ... just for translation!
};

const char* const measurement_unit[] PROGMEM = {
    "ms", // loop_time
    "Celsius", // temperature
    "%", // humidity
    "lux", // light
    "ppm", // CO2
    "hex", // gpio
    "hex", // analog
    "-", // rs232
    "ppb", // tvoc
    "-", // timestamp, no measurement ... just for translation!
};

// Total actuators have been configured by the mapping
#define ACTUATORS_TOTAL    4

// Actuator mapping
const char* const actuator_mapping[] PROGMEM = {
    "bm", // boot_mode
    "gs", // gpio_setup
    "go", // gpio_output
    "rs", // rs232
};

const char* const actuator_name[] PROGMEM = {
    "boot_mode", // boot_mode
    "gpio_setup", // gpio_setup
    "gpio", // gpio_output
    "rs232", // rs232
};

const char* const actuator_description[] PROGMEM = {
    "Switch to boot mode to update the software.", // boot_mode
    "Configureation of the gpio pins: (I)nput, (O)utput, (A)nalog, (P)TC, (N)ot_used, (S)erial: 0-3(I/O/A/N/P), 4-5(I/O/N/P), 6-7(I/O/N/P/S).", // gpio_setup
    "Set the state of the gpio pins that have been configured as output.", // gpio_output
    "Send data characters to the rs232, not more that 25 character each time! Setup gpio 6-7 as S!", // rs232
};

const char* const actuator_unit[] PROGMEM = {
    "-", // boot_mode
    "-", // gpio_setup
    "hex", // gpio_output
    "-", // rs232
};

// Returns the index of the location of the measurement based on the key
int8_t getMeasurementIndex(const char* key) {
    char buffer[2];
    for ( uint8_t i=0; i < MEASUREMENTS_TOTAL; ++i ) {
        strcpy_P(buffer, (char*)pgm_read_dword(&(measurement_mapping[i])));

        if ( key[0] == buffer[0] && key[1] == buffer[1] ) {
            return i;
        }
    }

    return -1;
}

// Returns the name of the measurement based on the index
char* getMeasurementName(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_name[ index ])));
    }
    return _buffer;
}

// Returns the name of the measurement based on the key
char* getMeasurementName(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementName(index);
}

// Returns the description of the measurement based on the index
char* getMeasurementDescription(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_description[ index ])));
    }
    return _buffer;
}

// Returns the description of the measurement based on the key
char* getMeasurementDescription(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementDescription(index);
}

// Returns the unit of the measurement based on the index
char* getMeasurementUnit(int8_t index) {
        strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_unit[ index ])));
    }
    return _buffer;
}

// Returns the unit of the measurement based on the key
char* getMeasurementUnit(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementUnit(index);
}

// Returns the index of the measurement mapping
int8_t getActuatorIndex(const char* key) {
    char buffer[2];
    for ( uint8_t i=0; i < MEASUREMENTS_TOTAL; ++i ) {
        strcpy_P(buffer, (char*)pgm_read_dword(&(actuator_mapping[i])));

        if ( key[0] == buffer[0] && key[1] == buffer[1] ) {
            return i;
        }
    }

    return -1;
}

// Returns the name of the actuator based on the index
char* getActuatorName(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_name[ index ])));
    }
    return _buffer;
}

// Returns the name of the actuator based on the key
char* getActuatorName(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorName(index);
}

// Returns the description of the actuator based on the index
char* getActuatorDescription(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_description[ index ])));
    }
    return _buffer;
}

// Returns the description of the actuator based on the key
char* getActuatorDescription(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorDescription(index);
}

// Returns the unit of the actuator based on the index
char* getActuatorUnit(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_unit[ index ])));
    }
    return _buffer;
}

// Returns the unit of the actuator based on the key
char* getActuatorUnit(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorUnit(index);
}

// Count how many times a character given by c is found in the string
uint8_t countCharacters(String line, char c) {
    uint8_t counter = 0;

    for (uint8_t i=0; i < line.length(); ++i) {
        if ( line.charAt(i) == c ) {
            counter++;
        }
    }

    return counter;
}

// Returns true when the string is holding an integer value
bool isInteger(String data) {
    for (uint8_t i=0; i < data.length(); ++i ) {
        if ( data.charAt(i) >= '0' && data.charAt(i) <= '9' ) {

        } else {
            return false;
        }
    }
    return true;
}

// Returns true when the string is holding a float value
bool isFloat(String data) {
    int dot = data.indexOf(".");
    if ( dot > 0 ) {
        return isInteger(data.substring(0, dot)) && isInteger(data.substring(dot+1));
    }

    return false;
}

// Class to hold a node value, which is often a measurement.
class SmartNodeValue {
public:
    String key;
    String value;
    SmartNodeValue(String key, String value): key(key), value(value) {}
    SmartNodeValue(): key(""), value("") {}
};

// Class that holds the node information
class SmartNode {
private:
    String id;
    String name;
    String measurements;
    String actuators;
    Queue<SmartNodeValue, 20> values;
    String timestamp;

public:
    SmartNode(): id(""), name(""), measurements(""), actuators(""), timestamp("") {
    }

    SmartNode(String id): id(id), name(""), measurements(""), actuators(""), timestamp("") {
    }
    
    SmartNode(String id, String name): id(id), name(name), measurements(""), actuators(""), timestamp("") {
    }

    String getId() { return this->id; }

    void addMeasurementsData(String data) {
        this->measurements = data;
    }

    void addActuatorsData(String data) {
        this->actuators = data;
    }

    void addValue(String data) {
        int i = data.indexOf(':');
        if ( i > 0 ) {
            String key = data.substring(0, i);
            String value = data.substring(i+1);
            if ( getMeasurementIndex(key.c_str()) != -1 ) { // It exist!
                if ( key.equals("ts") ) { // timestamp, so send the message!
                    if ( this->values.size() > 0 ) {
                        this->timestamp = value;
                        //Serial.print("Timestampe! Send the message!\n");
                    } else { 
                        Serial.printf_P(PSTR("Timestamp received, but no values in the buffer?!\n"));
                    }
                } else {
                    //Serial.printf("Adding: %s:%s\n", key.c_str(), value.c_str());
                    this->values.add(SmartNodeValue(key, value));
                }
            }
        }
    }

    void resetValues() {
        this->values.empty();
        this->timestamp = "";
    }

    String getJsonMeasurement(const char* measurement) {
        return "{\"name\":\"" + String(getMeasurementName(measurement)) + 
             "\",\"description\":\"" + String(getMeasurementDescription(measurement)) + 
             "\",\"unit\":\"" + String(getMeasurementUnit(measurement)) + "\"}";
    }

    // lt:te:hu:li:c2:gi:ai:rs
    String getJsonMeasurements() {
        String json = "";
        uint8_t counter = 0;
        String measurement = "";

        for (uint8_t i=0; i < this->measurements.length(); ++i) {
            if ( this->measurements.charAt(i) != ':' ) {
                measurement += this->measurements.charAt(i);
                counter++;
            } else {
                json = json + this->getJsonMeasurement(measurement.c_str()) + ",";
                measurement = "";
                counter++;
            }
        }

        json = json + this->getJsonMeasurement(measurement.c_str());

        return json;
    }

    String getJsonActuator(const char* actuator) {
        return "{\"name\":\"" + String(getActuatorName(actuator)) + 
             "\",\"description\":\"" + String(getActuatorDescription(actuator)) + 
             "\",\"unit\":\"" + String(getActuatorUnit(actuator)) + "\"}";
    }

    String getJsonActuators() {
        String json = "";
        uint8_t counter = 0;
        String actuator = "";

        for (uint8_t i=0; i < this->actuators.length(); ++i) {
            if ( this->actuators.charAt(i) != ':' ) {
                actuator += this->actuators.charAt(i);
                counter++;
            } else {
                json = json + this->getJsonActuator(actuator.c_str()) + ",";
                actuator = "";
                counter++;
            }
        }

        json = json + this->getJsonActuator(actuator.c_str());

        return json;
    }

    String getJsonValues() {
        String json = "";
        while ( this->values.size() > 0 ) {
            SmartNodeValue* value = this->values.pop();

            if ( isInteger( value->value ) ) {
                value->value = value->value + ".0";
            } else if (isFloat( value->value) ) {
                // it is okay
            } else {
                value->value = "\"" + value->value + "\"";
            }

            json = json + "\"" + getMeasurementName(value->key.c_str())+ "\":" + value->value;
            if ( this->values.size() != 0 ) {
                json = json + ",";
            } 
        }

        return json;
    }

    String getInitMessage() {
        String message = "{ \"type\": \"smartnode\", \"mode\": 0, ";
        //message = message + "\"id\": \"" + this->name + "-" + this->id + "\", ";
        message = message + "\"id\": \"" + this->id + "\", ";
        message = message + "\"name\": \"" + this->name + "\", \"measurements\": [" + this->getJsonMeasurements() + "],";
        message = message + "\"actuators\": [" + this->getJsonActuators() + "] }";

        return message;
    }

    String getMeasurementMessage() {
        //String message = "{ \"id\": \"" + this->name + "-" + this->id + "\",";
        String message = "{ \"id\": \"" + this->id + "\",";
        message = message + "\"measurements\": [{" + this->getJsonValues() + ",\"timestamp\": \"" + this->timestamp + "\"}],";
        message = message + "\"timestamp\": \"" + this->timestamp + "\" }";

        return message;
    }

    bool readyToSendData() {
        return (!this->timestamp.equals(""));
    }

};