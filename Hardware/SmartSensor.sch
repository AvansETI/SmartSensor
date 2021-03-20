EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "SmartSensor"
Date "2021-03-19"
Rev "1.1"
Comp "Avans Hogeschool"
Comment1 "Maurice Snoeren"
Comment2 "Expertise Centrum Technische Innovatie"
Comment3 "Lectoraat Smart Energy and Datascience & ICT"
Comment4 ""
$EndDescr
$Sheet
S 1000 1550 1400 500 
U 5F2DAD2E
F0 "Power Supply" 50
F1 "SmartSensor_PowerSupply.sch" 50
F2 "V_IN" O R 2400 1750 50 
F3 "ADAPTER_IN_USE" O R 2400 1850 50 
F4 "V_OUT_3.3V" O R 2400 1950 50 
F5 "V_BAT" U R 2400 1650 50 
$EndSheet
$Sheet
S 1000 2250 1400 1100
U 5F86FCBB
F0 "Sensors" 50
F1 "SmartSensor_Sensors.sch" 50
F2 "CO2_ENABLE" I R 2400 2500 50 
F3 "LS_ENABLE" I R 2400 2600 50 
F4 "HT_ENABLE" I R 2400 2700 50 
F5 "SDA" B R 2400 2900 50 
F6 "SCL" I R 2400 3000 50 
F7 "RESET" I R 2400 2350 50 
F8 "CO2_INT" O R 2400 3150 50 
F9 "CO2_WAKE" O R 2400 3250 50 
$EndSheet
$Sheet
S 2900 1550 1400 3600
U 5F76931A
F0 "Main Controller" 50
F1 "SmartSensor_MainController.sch" 50
F2 "ADAPTER_IN_USE" I L 2900 1850 50 
F3 "RESET" O L 2900 2350 50 
F4 "CO2_ENABLE" O L 2900 2500 50 
F5 "LS_ENABLE" O L 2900 2600 50 
F6 "THS_ENABLE" O L 2900 2700 50 
F7 "SDA" B L 2900 2900 50 
F8 "SCL" O L 2900 3000 50 
F9 "CO2_INT" O L 2900 3150 50 
F10 "CO2_WAKE" O L 2900 3250 50 
F11 "ATM_MOSI" O L 2900 4150 50 
F12 "ATM_MISO" I L 2900 4250 50 
F13 "ATM_CLK" O L 2900 4350 50 
F14 "ATM_TXD_0" O R 4300 3650 50 
F15 "ATM_TXD_1" O L 2900 3750 50 
F16 "ATM_RXD_0" I R 4300 3750 50 
F17 "ATM_RXD_1" I L 2900 3650 50 
F18 "XBEE_SS" O L 2900 4450 50 
F19 "XBEE_SLEEP" O L 2900 4650 50 
F20 "XBEE_ENABLE" O L 2900 4850 50 
F21 "RF_IRQ" I L 2900 5050 50 
F22 "ATM_PA0" T R 4300 4050 50 
F23 "ATM_PA1" T R 4300 4150 50 
F24 "ATM_PA2" T R 4300 4250 50 
F25 "ATM_MISO_1_RXD_2" I R 4300 4600 50 
F26 "ATM_MOSI_1_TXD_2" O R 4300 4500 50 
F27 "ATM_SCK_1" O R 4300 4700 50 
F28 "ATM_SDA_1" B R 4300 3250 50 
F29 "ATM_SCL_1" O R 4300 3350 50 
F30 "ATM_PA3" T R 4300 4350 50 
F31 "ATM_PB3" O R 4300 3850 50 
F32 "ATM_PB4" O R 4300 3950 50 
$EndSheet
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6005CA37
P 1000 7350
AR Path="/5F877B3A/6005CA37" Ref="H?"  Part="1" 
AR Path="/6005CA37" Ref="H1"  Part="1" 
F 0 "H1" H 1100 7399 50  0000 L CNN
F 1 "MountingHole_Pad" H 1000 7550 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1000 7350 50  0001 C CNN
F 3 "~" H 1000 7350 50  0001 C CNN
	1    1000 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6005CA3D
P 1300 7350
AR Path="/5F877B3A/6005CA3D" Ref="H?"  Part="1" 
AR Path="/6005CA3D" Ref="H2"  Part="1" 
F 0 "H2" H 1400 7399 50  0000 L CNN
F 1 "MountingHole_Pad" H 1000 7550 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1300 7350 50  0001 C CNN
F 3 "~" H 1300 7350 50  0001 C CNN
	1    1300 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6005CA43
P 1600 7350
AR Path="/5F877B3A/6005CA43" Ref="H?"  Part="1" 
AR Path="/6005CA43" Ref="H3"  Part="1" 
F 0 "H3" H 1700 7399 50  0000 L CNN
F 1 "MountingHole_Pad" H 1000 7550 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1600 7350 50  0001 C CNN
F 3 "~" H 1600 7350 50  0001 C CNN
	1    1600 7350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6005CA49
P 1450 7500
AR Path="/5F877B3A/6005CA49" Ref="#PWR?"  Part="1" 
AR Path="/6005CA49" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1450 7250 50  0001 C CNN
F 1 "GND" H 1455 7327 50  0000 C CNN
F 2 "" H 1450 7500 50  0001 C CNN
F 3 "" H 1450 7500 50  0001 C CNN
	1    1450 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 7450 1000 7500
Wire Wire Line
	1000 7500 1300 7500
Connection ~ 1450 7500
Wire Wire Line
	1600 7450 1600 7500
Wire Wire Line
	1600 7500 1450 7500
Wire Wire Line
	1300 7450 1300 7500
Connection ~ 1300 7500
Wire Wire Line
	1300 7500 1450 7500
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6005CA9F
P 1900 7350
AR Path="/5F877B3A/6005CA9F" Ref="H?"  Part="1" 
AR Path="/6005CA9F" Ref="H4"  Part="1" 
F 0 "H4" H 2000 7399 50  0000 L CNN
F 1 "MountingHole_Pad" H 1000 7550 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1900 7350 50  0001 C CNN
F 3 "~" H 1900 7350 50  0001 C CNN
	1    1900 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 7500 1900 7500
Wire Wire Line
	1900 7500 1900 7450
Connection ~ 1600 7500
$Sheet
S 1000 3550 1400 2600
U 5F877B3A
F0 "Communication" 50
F1 "SmartSensor_Communication.sch" 50
F2 "XBEE_UART_TX" O R 2400 3650 50 
F3 "XBEE_UART_RX" I R 2400 3750 50 
F4 "XBEE_RF_SPI_MOSI" I R 2400 4150 50 
F5 "XBEE_RF_SPI_MISO" O R 2400 4250 50 
F6 "XBEE_RF_SPI_CLK" I R 2400 4350 50 
F7 "XBEE_SPI_SSEL" I R 2400 4450 50 
F8 "XBEE_SLEEP" I R 2400 4650 50 
F9 "XBEE_RESET" I R 2400 4750 50 
F10 "XBEE_ENABLE" I R 2400 4850 50 
F11 "XBEE_AD1" B R 2400 5650 50 
F12 "XBEE_VREF" U R 2400 5750 50 
F13 "XBEE_PWM0" B R 2400 5850 50 
F14 "XBEE_PWM1" B R 2400 5950 50 
F15 "XBEE_D18" B R 2400 6050 50 
F16 "RF_IRQ" O R 2400 5050 50 
F17 "RF_CE" I R 2400 4950 50 
$EndSheet
Wire Wire Line
	2400 4150 2900 4150
Wire Wire Line
	2400 4250 2900 4250
Wire Wire Line
	2400 4350 2900 4350
Wire Wire Line
	2400 4450 2900 4450
Wire Wire Line
	2900 2350 2550 2350
Wire Wire Line
	2400 4750 2550 4750
Wire Wire Line
	2550 4750 2550 2350
Connection ~ 2550 2350
Wire Wire Line
	2550 2350 2400 2350
Wire Wire Line
	2400 1850 2800 1850
Wire Wire Line
	2400 2900 2800 2900
Wire Wire Line
	2400 3000 2750 3000
Wire Wire Line
	2400 3150 2900 3150
Wire Wire Line
	2400 3250 2900 3250
Wire Wire Line
	2400 2500 2900 2500
Wire Wire Line
	2400 2600 2900 2600
Wire Wire Line
	2400 2700 2900 2700
Wire Wire Line
	2400 3650 2900 3650
Wire Wire Line
	2900 3750 2400 3750
Wire Wire Line
	2400 4850 2900 4850
Wire Wire Line
	2400 5050 2900 5050
Wire Wire Line
	2800 1850 2800 1400
Wire Wire Line
	2800 1400 4400 1400
Wire Wire Line
	4400 1400 4400 1850
Wire Wire Line
	4400 1850 4800 1850
Connection ~ 2800 1850
Wire Wire Line
	2800 1850 2900 1850
Wire Wire Line
	2400 1750 2700 1750
Wire Wire Line
	2700 1750 2700 1300
Wire Wire Line
	2700 1300 4500 1300
Wire Wire Line
	4500 1300 4500 1750
Wire Wire Line
	4500 1750 4800 1750
Wire Wire Line
	2400 1650 2600 1650
Wire Wire Line
	2600 1650 2600 1200
Wire Wire Line
	2600 1200 4600 1200
Wire Wire Line
	4600 1200 4600 1650
Wire Wire Line
	4600 1650 4800 1650
Wire Wire Line
	2400 4650 2500 4650
Wire Wire Line
	2400 4950 2500 4950
Wire Wire Line
	2500 4950 2500 4650
Connection ~ 2500 4650
Wire Wire Line
	2500 4650 2900 4650
Wire Wire Line
	4300 3650 4800 3650
Wire Wire Line
	4800 3750 4300 3750
Wire Wire Line
	4300 4050 4800 4050
Wire Wire Line
	4800 4150 4300 4150
Wire Wire Line
	4300 4250 4800 4250
Wire Wire Line
	4300 4500 4800 4500
Wire Wire Line
	4300 4600 4800 4600
Wire Wire Line
	4300 4700 4800 4700
Wire Wire Line
	4800 5250 2800 5250
Wire Wire Line
	2800 5250 2800 2900
Connection ~ 2800 2900
Wire Wire Line
	2800 2900 2900 2900
Wire Wire Line
	4800 5350 2750 5350
Wire Wire Line
	2750 5350 2750 3000
Connection ~ 2750 3000
Wire Wire Line
	2750 3000 2900 3000
Wire Wire Line
	4800 5450 2550 5450
Wire Wire Line
	2550 5450 2550 4750
Connection ~ 2550 4750
Wire Wire Line
	2400 5650 4800 5650
Wire Wire Line
	2400 5750 4800 5750
Wire Wire Line
	2400 5850 4800 5850
Wire Wire Line
	2400 6050 4800 6050
Wire Wire Line
	2400 5950 4800 5950
Wire Wire Line
	4300 3250 4800 3250
Wire Wire Line
	4800 3350 4300 3350
$Sheet
S 4800 1550 1450 4600
U 5F375837
F0 "Interface" 50
F1 "SmartSensor_Interface.sch" 50
F2 "V_BAT" U L 4800 1650 50 
F3 "V_IN" U L 4800 1750 50 
F4 "ADAPTER_IN_USE" I L 4800 1850 50 
F5 "RESET" I L 4800 5450 50 
F6 "ATM_TX0" I L 4800 3650 50 
F7 "ATM_RX0" O L 4800 3750 50 
F8 "ATM_PA0" T L 4800 4050 50 
F9 "ATM_PA1" T L 4800 4150 50 
F10 "ATM_PA2" T L 4800 4250 50 
F11 "ATM_MOSI_1_TXD_2" I L 4800 4500 50 
F12 "ATM_MISO_1_RXD_2" O L 4800 4600 50 
F13 "ATM_SCK_1" I L 4800 4700 50 
F14 "SDA" B L 4800 5250 50 
F15 "SCL" I L 4800 5350 50 
F16 "XBEE_AD1" U L 4800 5650 50 
F17 "XBEE_VREF" U L 4800 5750 50 
F18 "XBEE_PWM0" I L 4800 5850 50 
F19 "XBEE_PWM1" I L 4800 5950 50 
F20 "XBEE_D18" B L 4800 6050 50 
F21 "ATM_SDA_1" B L 4800 3250 50 
F22 "ATM_SCL_1" I L 4800 3350 50 
F23 "ATM_PA3" T L 4800 4350 50 
F24 "ATM_PB3" I L 4800 3850 50 
F25 "ATM_PB4" I L 4800 3950 50 
$EndSheet
Wire Wire Line
	4800 4350 4300 4350
Wire Wire Line
	4800 3850 4300 3850
Wire Wire Line
	4300 3950 4800 3950
$EndSCHEMATC
