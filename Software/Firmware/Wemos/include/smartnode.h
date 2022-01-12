// Avans University of Applied Sciences (Avans Hogeschool)
// Module: Intelligent Wireless Sensor Netwerken (IWSN)
// Author: Maurice Snoeren
// Date  : 10-01-2022
// Author: Maurice Snoeren
//
#pragma once

#include <Arduino.h>
#include <Queue.h>

// Measurement mapping

#define MEASUREMENTS_TOTAL 10
#define ACTUATORS_TOTAL    4

char _buffer[150];

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

char* getMeasurementName(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_name[ index ])));
    }
    return _buffer;
}

char* getMeasurementName(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementName(index);
}

char* getMeasurementDescription(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_description[ index ])));
    }
    return _buffer;
}

char* getMeasurementDescription(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementDescription(index);
}

char* getMeasurementUnit(int8_t index) {
        strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(measurement_unit[ index ])));
    }
    return _buffer;
}

char* getMeasurementUnit(const char* key) {
    int8_t index = getMeasurementIndex(key);
    return getMeasurementUnit(index);
}

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

char* getActuatorName(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_name[ index ])));
    }
    return _buffer;
}

char* getActuatorName(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorName(index);
}

char* getActuatorDescription(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_description[ index ])));
    }
    return _buffer;
}

char* getActuatorDescription(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorDescription(index);
}

char* getActuatorUnit(int8_t index) {
    strcpy_P(_buffer, PSTR(""));
    if ( index != -1 ) {
        strcpy_P(_buffer, (char*)pgm_read_dword(&(actuator_unit[ index ])));
    }
    return _buffer;
}

char* getActuatorUnit(const char* key) {
    int8_t index = getActuatorIndex(key);
    return getActuatorUnit(index);
}

uint8_t countCharacters(String line, char c) {
    uint8_t counter = 0;

    for (uint8_t i=0; i < line.length(); ++i) {
        if ( line.charAt(i) == c ) {
            counter++;
        }
    }

    return counter;
}

class SmartNode {
private:
    String id;
    String name;
    String measurements;
    String actuators;
    Queue<String, 20> values;

public:
    SmartNode(): id(""), name(""), measurements(""), actuators("") {
    }

    SmartNode(String id, String name): id(id), name(name), measurements(""), actuators("") {
    }

    String getId() { return this->id; }

    void addMeasurementsData(String data) {
        this->measurements = data;
    }

    void addActuatorsData(String data) {
        this->actuators = data;
    }

    void addValue(String data) {
        this->values.add(data);
    }

    void resetValues() {
        this->values.empty();
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

    String getInitMessage() {
        String message = "{ \"type\": \"smartnode\", \"mode\": 0, ";
        message = message + "\"id\": \"" + this->name + "-" + this->id + "\", ";
        message = message + "\"name\": \"" + this->name + "\", \"measurements\": [" + this->getJsonMeasurements() + "],";
        message = message + "\"actuators\": [" + this->getJsonActuators() + "] }";

        return message;
    }

    String getMeasurementMessage() {
        return "";
    }


};