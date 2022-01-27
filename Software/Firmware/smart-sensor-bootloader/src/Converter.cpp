/**
 * Seperate class for Byte Conversion
 * @date   : 5 January 2022
 * @author : Tom Kaasenbrood
 * @version: 0.1 development version
 * #todo   : rewrite for correct input
 * @updates
 */

#include <Converter.h>

uint8_t getValueFromHex(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    return c - 'A' + 10;
}

//converts an input of 2 hex characters to a single byte value
uint8_t convertHexToByte(char one, char two)
{
    uint8_t value = ((getValueFromHex(one) << 4) | (getValueFromHex(two)));

    return value;
}