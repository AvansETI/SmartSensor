#include <SmartSensor.h>

void enableHumiditySensor () {
    digitalWrite(HDC1080_IO6, HIGH);
}

void disableHumiditySensor () {
    digitalWrite(HDC1080_IO6, LOW);
}

void enableLightSensor() {
    digitalWrite(VEML7700_IO5, HIGH);
}

void disableLightSensor() {
    digitalWrite(VEML7700_IO5, LOW);
}

void enableXBee() {
    digitalWrite(XBEE_ON_OFF, HIGH);
}

void disableXBee() {
    digitalWrite(XBEE_ON_OFF, LOW);
}

void sleepXBee(uint8_t state) {
    digitalWrite(XBEE_SLEEP, state);
}
