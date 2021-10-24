/*
 * @file       : boards/Board.cpp
 * @author     : Maurice Snoeren (MS)
 * @license    : GNU version 3.0
 */
#include <util/RTC.h>

#include <stdio.h>

#include <avr/pgmspace.h>

RTCTime::RTCTime(uint8_t data[7]) {
    this->year    = RTCTime::bcd2int( data[6] ); // Year
    this->month   = RTCTime::bcd2int( data[5] & 0b0001'1111 );  // Month
    this->day     = RTCTime::bcd2int( data[4] & 0b0011'1111 );  // Date
    this->weekday = RTCTime::bcd2int( data[3] & 0b0000'0111 );  // Weekday
    this->hours   = RTCTime::bcd2int( data[2] & 0b0001'1111 );  // Hour
    this->minutes = RTCTime::bcd2int( data[1] & 0b0111'1111 ); // Minute
    this->seconds = RTCTime::bcd2int( data[0] & 0b0111'1111 );  // Seconds
}

RTCTime::RTCTime(const char* iso8601) {
    this->setFromIso8601String(iso8601);
}

uint8_t RTCTime::int2bcd(uint8_t value) {
    return ((value / 10) << 4) + (value % 10);
}

uint8_t RTCTime::bcd2int(uint8_t bcd) {
    return ((bcd & 0xF0) >> 4)*10 + (bcd & 0x0F);
}

/* Convert the RTCTime to an ISO8601 string. */
void RTCTime::getIso8601String(char iso8601[20]) {
    sprintf(iso8601, "20%02d-%02d-%02dT%02d:%02d:%02d",
                this->year, this->month, this->day,
                this->hours, this->minutes, this->seconds);
}

uint8_t RTCTime::setFromIso8601String(const char* iso8601) {
    // TODO: Set the attributes based on tiso8601 string
    return 0;
}

uint8_t RTCTime::getYear() const {
    return this->year;
}

uint8_t RTCTime::getMonth() const {
    return this->month;
}

uint8_t RTCTime::getDay() const {
    return this->day;
}

uint8_t RTCTime::getWeekDay() const {
    return this->weekday;
}

uint8_t RTCTime::getHours() const {
    return this->hours;
}

uint8_t RTCTime::getMinutes() const {
    return this->minutes;
}

uint8_t RTCTime::getSeconds() const {
    return this->seconds;
}
