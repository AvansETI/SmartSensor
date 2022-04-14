// Class for handling serial
#include <avr/io.h>

void initSerial();
void sendString(const char *input);
void sendChar(char c);
bool isCharReceived();
char readChar();
bool isValidLine(char *line, uint8_t *data, uint16_t *address, uint8_t *bytesInData);
bool readLine(char *line, uint8_t timeout, uint8_t length);
bool isDone();