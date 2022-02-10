//Class for handling serial
#include <avr/io.h>


void initSerial();
void sendString(unsigned char input[]);
void sendChar(unsigned char c);