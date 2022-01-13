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