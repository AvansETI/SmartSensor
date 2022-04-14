#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

bool writeToBuffer(uint16_t pageAddress, uint8_t *buf, uint8_t byteAmount);
bool flashBufferToPage();
void resetProg();
void resetAddress();