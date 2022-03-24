// Class for handling serial
#include <avr/io.h>

void initSerial();
void sendString(const char *input);
void sendChar(char c);
// char *getReceived();
// void resetArray();
bool isCharReceived();
char readChar();
bool isValidLine(char *line);
bool readLine(char *line, uint8_t timeout, uint8_t length);