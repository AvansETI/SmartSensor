/**
 * Seperate class for Byte Conversion
 * @date   : 5 January 2022
 * @author : Tom Kaasenbrood
 * @version: 0.1 development version
 * #todo   : rewrite for correct input
 * @updates
 */

#include <stdio.h>
#include <Converter.h>
#include <string.h>
#include <stdlib.h>

uint8_t getValueFromHex(char c) {
    if ( c >= '0' && c <= '9') {
        return c - '0';
    }
    return c - 'A'+ 10;
}

void kanweg() {
    uint8_t buffer = getValueFromHex('A') + (8 << getValueFromHex('B'));

}

//converts an input of 2 hex characters to a single byte value
uint8_t convertHexToByte(char *one, char *two) {
    char val[4];
    val[0] = '0';
    val[1] = 'x';
    val[2] = *one;
    val[3] = *two;

    uint8_t value = (uint8_t)strtol(val, NULL, 0);

    return value;
}