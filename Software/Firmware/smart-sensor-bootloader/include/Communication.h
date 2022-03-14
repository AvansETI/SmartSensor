//Class for handling serial
#include <avr/io.h>

void initSerial();
void sendString(const char *input);
void sendChar(char c);
char* getRecieved();
void resetArray();