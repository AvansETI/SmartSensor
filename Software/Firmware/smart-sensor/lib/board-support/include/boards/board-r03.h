/**
 * Smart Sensor v0.3 configuration
 * @date 15 June 2020
 */

#ifndef BOARD_SUPPORT_BOARD_CONFIG_R03_H
#define BOARD_SUPPORT_BOARD_CONFIG_R03_H

#include <board-support/util/PinPort.h>

/**
 * TWI Configuration
 */
#define TWI_RTC_ADDRESS         0xDC        // Real-time Clock (MCP7940N)
#define TWI_THS_ADDRESS         0x4E        // Temperature and Humidity Sensor (HIH6031)
#define TWI_ALS_ADDRESS         0x20        // Ambient Light Sensor (VEML7700)
#define TWI_CO2_ADDRESS         0x00        // CO2 Sensor (unknown!) (CCS811)
#define TWI_TPM_ADDRESS         0x00        // Trusted Platform Module (AT97SC3205T)

// TWI0
#define TWI0_ENABLED            1
#define TWI0_SR                 TWSR0
#define TWI0_BR                 TWBR0
#define TWI0_CR                 TWCR0
#define TWI0_DR                 TWDR0

// TWI1
#define TWI1_ENABLED            0
#define TWI1_SR                 TWSR1
#define TWI1_BR                 TWBR1
#define TWI1_CR                 TWCR1
#define TWI1_DR                 TWDR1


/**
 * USART Configuration
 */


/**
 * Pin Configuration
 */
#define ATM_PA0_PIN             PinPortA0   // GPIO
#define ATM_PA1_PIN             PinPortA1   // GPIO
#define ATM_PA2_PIN             PinPortA2   // GPIO
#define ADAPT_ENABLE_PIN        PinPortA3   // 1 when adapter is connected, otherwise 0
#define POWER_LOW_BAT_PIN       PinPortA4   // 1 when battery power is low, otherwise 0
#define CO2_WAKE_PIN            PinPortA5   // CO2 wake pin
#define CO2_INT_PIN             PinPortA6   // CO2 interrupt pin
#define CO2_ENABLE_PIN          PinPortA7   // CO2 enable pin

#define XBEE_ENABLE_PIN         PinPortB4   // Enable XBee power

#define THS_ENABLE_PIN          PinPortC6   // Enable Temperature en Humidity Sensor power
#define ALS_ENABLE_PIN          PinPortC7   // Enable Ambient Light Sensor power

#define RTC_MFP_PIN             PinPortD2   // Real-time clock multi-functional-pin
#define THS_AL_H_PIN            PinPortD3   // Temperature and humidity sensor alarm high pin
#define STATUS_LED_1_PIN        PinPortD4   // Led 1 (RED)
#define STATUS_LED_2_PIN        PinPortD5   // Led 2 (GREEN)


#endif // BOARD_SUPPORT_BOARD_CONFIG_R03_H