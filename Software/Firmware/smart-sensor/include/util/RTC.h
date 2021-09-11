#pragma once
/**
 * @file       : RTC.h
 * @description: This file contains all generic classes for real-time clock (RTC) functions.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#include <stdint.h>

/* The class that holds the real-time and date (RTC). It can be used to manipulate the date. */
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
    /* Constructor that sets all the individual time elements. */
    RTCTime(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday,
            uint8_t hours, uint8_t minutes, uint8_t seconds) :
            year(year), month(month), day(day), weekday(weekday), hours(hours), minutes(minutes), seconds(seconds) {}

    /* Constructor that sets all the individual time elements based on the given iso8601 string. */
    RTCTime(const char* iso8601);

    /* Convert the RTCTime to an ISO8601 string. */
    const char* getIso8601String();

    /* Getters to retrieve the time components. */
    uint8_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getWeekDay();
    uint8_t getHours();
    uint8_t getMinutes();
    uint8_t getSeconds();

private:
    /* Set the current time values to the given iso8601 string. */
    uint8_t setFromIso8601String(const char* iso8601);
};
