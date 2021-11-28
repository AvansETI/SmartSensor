#pragma once
/**
 * @file       : boards/Communication.h
 * @description: Communication with the SmartNetwork abstraction. This abstraction enables multiple communication
 *               channels like XBee of LoRa or WiFi. The specific board shall implement the specifics and should
 *               check which channels have been installed and can be used.
 * @date       : 11-09-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : -
 * @updates
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>
