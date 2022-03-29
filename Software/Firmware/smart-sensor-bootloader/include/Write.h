#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

char* bootReadBuffer();
bool writeToBuffer(uint32_t pageNo, uint8_t *buf);
bool flashBufferToPage();