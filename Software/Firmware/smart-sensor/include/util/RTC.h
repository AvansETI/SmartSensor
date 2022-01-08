#pragma once
/**
 * @file       : RTC.h
 * @description: This file contains all generic classes for real-time clock (RTC) functions.
 * @date       : 24-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 1.0
 * @license    : GNU version 3.0
 * @todo       : 
 * @changes
 * 
 */
#include <stdint.h>

/* Class: RTCTime
   The class that holds the real-time and date (RTC). It can be used to manipulate the date. 
*/
class RTCTime {
private:
  /* The individual time values. */
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t weekday;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;

public:
    /* Default constructor. */
    RTCTime(): RTCTime(0, 0, 0, 0, 0, 0, 0) {}

    /* Constructor that sets all the individual time elements. */
    RTCTime(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday,
            uint8_t hours, uint8_t minutes, uint8_t seconds) :
            year(year), month(month), day(day), weekday(weekday), hours(hours), minutes(minutes), seconds(seconds) {}

    /* Constructor that sets all the individual time elements based on the given iso8601 string. */
    RTCTime(const char* iso8601);

    /* Constructor that accepts the data from the MCP7940N chip. */
    RTCTime(uint8_t data[7]);

    /* Convert the RTCTime to an ISO8601 string. */
    void getIso8601String(char iso8601[20]);

    void getShortString(char str[20]);

    /* Getters to retrieve the time components. */
    uint8_t getYear() const;
    uint8_t getMonth() const;
    uint8_t getDay() const;
    uint8_t getWeekDay() const;
    uint8_t getHours() const;
    uint8_t getMinutes() const;
    uint8_t getSeconds() const;

    /* Set the current time values to the given iso8601 string. If successfull
       it returns zeor, otherwise 1. */
    uint8_t setFromIso8601String(const char* iso8601);

    /* Helper function to convert bcd numbers to int. A BCD is a four bits number that represent
       the number of the clock. The four higher order bits is the digit of the ten and the lower
       order is the decimal.
     */
    static uint8_t bcd2int(uint8_t bcd);

    /* Helper function to convert an int back to a bcd value. */
    static uint8_t int2bcd(uint8_t value);
};

/* Enumeration used to identify which data is returned by the rtcReadTimestampEvent. */
enum RTCEventMode {
   TIME,
   ALARM0_TIME,
   ALARM1_TIME,
   POWER_DOWN_TIME,
   POWER_UP_TIME
};

/* Interface: RTCReadTimestampEvent
   Interface callback when a time is read. 
*/
class RTCReadTimestampEvent {
public:
  virtual void rtcReadTimestampEvent(RTCTime& time, RTCEventMode mode) = 0; // Used to communicate back the retrieved time
};