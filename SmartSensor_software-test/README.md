# Smart Sensor Software

This documentation descibres how the development environment is set up and how the software
design has been created.

# Development environment

1. Install Visual Studio Code.
2. Install the "PlatformIO IDE" extension for Visual Studio Code.
3. Restart Visual Studio Code and open the folder SmartSensor/SmartSensor_software_test.
4. Build your project with "PlatformIO: Build" and everything should build automatically.

At this moment that Atmega can be programmed.

# XBee

https://www.digi.com/products/embedded-systems/digi-xbee/digi-xbee-tools/xctu

# Atmega32A-AU pinout

- PA0 - VBAT_ADC0 
- PA1 - HAT_AIO1
- PA2 - INTA_ADC3
- PA3 - HAT_AIO2
- PA4 - HAT_AIO6
- PA5 - HAT_AIO4
- PA6 - HAT_AIO5
- PA7 - HAT_AIO3

- PB0 - HDC1080_IO6
- PB1 - HAT_DIO5
- PB2 - HAT_DIO3
- PB3 - HAT_DIO4
- PB4 - SS
- PB5 - MOSI
- PB6 - MISO
- PB7 - SCK

- PC0 - SCL
- PC1 - SDA
- PC2 - LED_IO8
- PC3 - Vadap_IO9
- PC4 - XBEE_SLEEP
- PC5 - HAT_DIO1
- PC6 - HAT_DIO6
- PC7 - HAT_DIO7

- PD0 - AVR_DBG_RX
- PD1 - AVR_DBG_TX
- PD2 - XBEE_ON_OFF
- PD3 - AVR_RX
- PD4 - AVR_TX
- PD5 - VEML7700_IO5
- PD6 - HAT_DIO2
- PD7 - HAT_DIO31



