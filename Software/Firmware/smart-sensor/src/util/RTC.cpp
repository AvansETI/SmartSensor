#include <util/RTC.h>

RTCTime::RTCTime(const char* iso8601) {
    this->setFromIso8601String(iso8601);
}

/* Convert the RTCTime to an ISO8601 string. */
const char* RTCTime::getIso8601String() {
  static char buffer[20] = "20YY-MM-DDThh:mm:ss";
  buffer[2] = '0' + (this->year/10);
  buffer[3] = '0' + (this->year%10);
  
  buffer[5] = '0' + (this->month/10);
  buffer[6] = '0' + (this->month%10);

  buffer[8] = '0' + (this->day/10);
  buffer[9] = '0' + (this->day%10);

  buffer[11] = '0' + (this->hours/10);
  buffer[12] = '0' + (this->hours%10);

  buffer[14] = '0' + (this->minutes/10);
  buffer[15] = '0' + (this->minutes%10);

  buffer[17] = '0' + (this->seconds/10);
  buffer[18] = '0' + (this->seconds%10);

  return buffer;
}

uint8_t RTCTime::setFromIso8601String(const char* iso8601) {
    // TODO: Set the attributes based on tiso8601 string
    return 0;
}

uint8_t RTCTime::getYear() {
    return this->year;
}

uint8_t RTCTime::getMonth() {
    return this->month;
}

uint8_t RTCTime::getDay() {
    return this->day;
}

uint8_t RTCTime::getWeekDay() {
    return this->weekday;
}

uint8_t RTCTime::getHours() {
    return this->hours;
}

uint8_t RTCTime::getMinutes() {
    return this->minutes;
}

uint8_t RTCTime::getSeconds() {
    return this->seconds;
}

uint8_t RTCTime::convertToBcd(uint8_t byteDecimal) {
  return (byteDecimal / 10) << 4 | (byteDecimal % 10);
}

uint8_t RTCTime::convertFromBcd(uint8_t byteBCD) {
  uint8_t byteMSB = 0;
  uint8_t byteLSB = 0;

  byteMSB = (byteBCD & 0b1111'0000) >> 4;
  byteLSB = (byteBCD & 0b0000'1111);

  return ((byteMSB * 10) + byteLSB);
}
