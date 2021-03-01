/**
 * Smart Sensor v1.0 configuration
 * @date 25 February 2021
 * @author: Maurice Snoeren - mac.snoeren(at)avans.nl
 */

#ifndef BOARD_SUPPORT_BOARD_CONFIG_R10_H
#define BOARD_SUPPORT_BOARD_CONFIG_R10_H

#include <board-support/util/PinPort.h>

/**
 * TWI Configuration
 */
#define TWI_RTC_ADDRESS         0xDC        // Real-time Clock (MCP7940N)
#define TWI_THS_ADDRESS         0x70        // Temperature and Humidity Sensor (SHTC3)
#define TWI_ALS_ADDRESS         0x20        // Ambient Light Sensor (VEML7700)
#define TWI_CO2_ADDRESS         0x5A        // CO2 Sensor (CCS811)
#define TWI_TPM_ADDRESS         0x60        // Trusted Platform Module (ATECC608B)

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
#define ATM_PA3_PIN             PinPortA3   // GPIO
#define RF_IRQ_PIN              PinPortA4
#define XBEE_ENABLE_PIN         PinPortA5
#define ADAPTER_IN_USE_PIN      PinPortA6
#define CO2_INT_PIN             PinPortA7

#define XBEE_SS_PIN             PinPortB0
#define XBEE_SLEEP_PIN          PinPortB1
#define RTC_MFP_PIN             PinPortB2
#define ATM_PB3_PIN             PinPortB3
#define ATM_PB4_PIN             PinPortB4
#define ATM_MOSI_PIN            PinPortB5
#define ATM_MISO_PIN            PinPortB6
#define ATM_SCK_PIN             PinPortB7

#define SCL_MAIN_PIN            PinPortC0
#define SDA_MAIN_PIN            PinPortC1
#define ATM_JTAG_TCK_PIN        PinPortC2
#define ATM_JTAG_TMS_PIN        PinPortC3
#define ATM_JTAG_TDO_PIN        PinPortC4
#define ATM_JTAG_TDI_PIN        PinPortC5
#define LS_ENABLE_PIN           PinPortC6
#define THS_ENABLE_PIN          PinPortC7

#define ATM_RXD_0_PIN           PinPortD0
#define ATM_TXD_0_PIN           PinPortD1
#define ATM_RXD_1_PIN           PinPortD2
#define ATM_TXD_1_PIN           PinPortD3
#define STATUS_LED_1_PIN        PinPortD4
#define CO2_ENABLE_PIN          PinPortD5
#define CO2_WAKE_PIN            PinPortD6
#define ATM_SCK_1_PIN           PinPortD7

#define ATM_MISO_1_PIN          PinPortE2
#define ATM_MOSI_1_PIN          PinPortE3
#define ATM_SDA_1_PIN           PinPortE5
#define ATM_SCL_1_PIN           PinPortE6

#endif // BOARD_SUPPORT_BOARD_CONFIG_R10_H