EESchema Schematic File Version 4
LIBS:SmartSensor-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Smart Sensor"
Date "2019-06-07"
Rev "v1.0"
Comp "Avans Hogeschool"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328-PU U4
U 1 1 5CE908D7
P 6850 2500
F 0 "U4" H 7300 4100 50  0000 R CNN
F 1 "ATmega328-PU" H 7600 4000 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 6850 2500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 6850 2500 50  0001 C CNN
	1    6850 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 5CE91F2D
P 6850 850
F 0 "#PWR030" H 6850 700 50  0001 C CNN
F 1 "+3.3V" H 6865 1023 50  0000 C CNN
F 2 "" H 6850 850 50  0001 C CNN
F 3 "" H 6850 850 50  0001 C CNN
	1    6850 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 850  6850 950 
Wire Wire Line
	5750 5100 5750 5000
$Comp
L Device:R_Small R6
U 1 1 5CEC9E7B
P 5750 4800
F 0 "R6" H 5809 4846 50  0000 L CNN
F 1 "100kΩ" H 5809 4755 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5750 4800 50  0001 C CNN
F 3 "~" H 5750 4800 50  0001 C CNN
	1    5750 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5CEC9F8F
P 5750 5300
F 0 "SW1" V 5704 5448 50  0000 L CNN
F 1 "SW_Push" V 5795 5448 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5750 5500 50  0001 C CNN
F 3 "" H 5750 5500 50  0001 C CNN
	1    5750 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 4650 5750 4700
$Comp
L power:+3.3V #PWR023
U 1 1 5CF027D7
P 5750 4650
F 0 "#PWR023" H 5750 4500 50  0001 C CNN
F 1 "+3.3V" H 5765 4823 50  0000 C CNN
F 2 "" H 5750 4650 50  0001 C CNN
F 3 "" H 5750 4650 50  0001 C CNN
	1    5750 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5CF1ED04
P 5750 5550
F 0 "#PWR024" H 5750 5300 50  0001 C CNN
F 1 "GND" H 5755 5377 50  0000 C CNN
F 2 "" H 5750 5550 50  0001 C CNN
F 3 "" H 5750 5550 50  0001 C CNN
	1    5750 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5500 5750 5550
$Comp
L power:GND #PWR031
U 1 1 5CF3B37E
P 6850 4100
F 0 "#PWR031" H 6850 3850 50  0001 C CNN
F 1 "GND" H 6855 3927 50  0000 C CNN
F 2 "" H 6850 4100 50  0001 C CNN
F 3 "" H 6850 4100 50  0001 C CNN
	1    6850 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4000 6850 4100
Wire Wire Line
	6950 1000 6950 950 
Wire Wire Line
	6950 950  6850 950 
Connection ~ 6850 950 
Wire Wire Line
	6850 950  6850 1000
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J8
U 1 1 5CF91FEA
P 10200 5100
F 0 "J8" H 10250 5417 50  0000 C CNN
F 1 "6 PIN ISP" H 10250 5326 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 10200 5100 50  0001 C CNN
F 3 "~" H 10200 5100 50  0001 C CNN
	1    10200 5100
	1    0    0    -1  
$EndComp
Text GLabel 7450 1800 2    50   Input ~ 0
SCK
Text GLabel 7450 1700 2    50   Input ~ 0
MISO
Text GLabel 7450 1600 2    50   Input ~ 0
MOSI
Text GLabel 7450 2800 2    50   Input ~ 0
RESET
Text GLabel 5550 5000 0    50   Input ~ 0
RESET
Wire Wire Line
	5550 5000 5750 5000
Connection ~ 5750 5000
Wire Wire Line
	5750 5000 5750 4900
Text GLabel 10000 5000 0    50   Input ~ 0
MISO
Text GLabel 10000 5100 0    50   Input ~ 0
SCK
Text GLabel 10000 5200 0    50   Input ~ 0
RESET
Text GLabel 10500 5100 2    50   Input ~ 0
MOSI
$Comp
L power:GND #PWR046
U 1 1 5D006BC6
P 10650 5350
F 0 "#PWR046" H 10650 5100 50  0001 C CNN
F 1 "GND" H 10655 5177 50  0000 C CNN
F 2 "" H 10650 5350 50  0001 C CNN
F 3 "" H 10650 5350 50  0001 C CNN
	1    10650 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 5200 10650 5200
Wire Wire Line
	10650 5200 10650 5350
Text GLabel 7450 2700 2    50   Input ~ 0
SCL
Text GLabel 7450 2600 2    50   Input ~ 0
SDA
Text GLabel 5450 6850 0    50   Input ~ 0
SDA
Text GLabel 6300 6850 2    50   Input ~ 0
SDA
Text GLabel 5450 7000 0    50   Input ~ 0
SCL
Text GLabel 6300 7000 2    50   Input ~ 0
SCL
Wire Wire Line
	5450 6850 6150 6850
Wire Wire Line
	6300 7000 5650 7000
$Comp
L Device:R_Small R8
U 1 1 5D20D710
P 6150 6550
F 0 "R8" H 6209 6596 50  0000 L CNN
F 1 "4.7kΩ" H 6209 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6150 6550 50  0001 C CNN
F 3 "~" H 6150 6550 50  0001 C CNN
	1    6150 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5D20D81A
P 5650 6550
F 0 "R7" H 5709 6596 50  0000 L CNN
F 1 "4.7kΩ" H 5709 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5650 6550 50  0001 C CNN
F 3 "~" H 5650 6550 50  0001 C CNN
	1    5650 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 6650 5650 7000
Connection ~ 5650 7000
Wire Wire Line
	5650 7000 5450 7000
Connection ~ 6150 6850
Wire Wire Line
	6150 6850 6300 6850
Wire Wire Line
	5650 6450 5650 6300
Wire Wire Line
	6150 6300 6150 6450
$Comp
L power:+3.3V #PWR025
U 1 1 5D28D05A
P 5650 6300
F 0 "#PWR025" H 5650 6150 50  0001 C CNN
F 1 "+3.3V" H 5665 6473 50  0000 C CNN
F 2 "" H 5650 6300 50  0001 C CNN
F 3 "" H 5650 6300 50  0001 C CNN
	1    5650 6300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR026
U 1 1 5D28D22D
P 6150 6300
F 0 "#PWR026" H 6150 6150 50  0001 C CNN
F 1 "+3.3V" H 6165 6473 50  0000 C CNN
F 2 "" H 6150 6300 50  0001 C CNN
F 3 "" H 6150 6300 50  0001 C CNN
	1    6150 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 6650 6150 6850
NoConn ~ 7450 1300
NoConn ~ 7450 1900
NoConn ~ 7450 2000
NoConn ~ 7450 2300
NoConn ~ 7450 2400
NoConn ~ 7450 2500
NoConn ~ 7450 3700
$Comp
L Connector:USB_B_Micro J5
U 1 1 5CAD0879
P 8300 5300
F 0 "J5" H 8355 5767 50  0000 C CNN
F 1 "USB_B_Micro" H 8355 5676 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 8450 5250 50  0001 C CNN
F 3 "~" H 8450 5250 50  0001 C CNN
	1    8300 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5800 8200 5800
Wire Wire Line
	8200 5800 8200 5700
Connection ~ 8300 5800
$Comp
L Device:Battery_Cell BT1
U 1 1 5CAD8454
P 900 3600
F 0 "BT1" H 1018 3696 50  0000 L CNN
F 1 "Battery_Cell" H 1018 3605 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_2462_2xAA" V 900 3660 50  0001 C CNN
F 3 "~" V 900 3660 50  0001 C CNN
	1    900  3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5CAD9102
P 900 3800
F 0 "#PWR02" H 900 3550 50  0001 C CNN
F 1 "GND" H 905 3627 50  0000 C CNN
F 2 "" H 900 3800 50  0001 C CNN
F 3 "" H 900 3800 50  0001 C CNN
	1    900  3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  3250 900  3300
$Comp
L Transistor_FET:MMBF170 Q1
U 1 1 5CB2D1A9
P 7050 5250
F 0 "Q1" H 7255 5296 50  0000 L CNN
F 1 "MMBF170" H 7255 5205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7250 5175 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/ds30104.pdf" H 7050 5250 50  0001 L CNN
	1    7050 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5CB48E0D
P 7150 5650
F 0 "#PWR034" H 7150 5400 50  0001 C CNN
F 1 "GND" H 7155 5477 50  0000 C CNN
F 2 "" H 7150 5650 50  0001 C CNN
F 3 "" H 7150 5650 50  0001 C CNN
	1    7150 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR033
U 1 1 5CB5F612
P 7150 4700
F 0 "#PWR033" H 7150 4550 50  0001 C CNN
F 1 "+3.3V" H 7165 4873 50  0000 C CNN
F 2 "" H 7150 4700 50  0001 C CNN
F 3 "" H 7150 4700 50  0001 C CNN
	1    7150 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R10
U 1 1 5CB5F75F
P 7150 4850
F 0 "R10" H 7200 4900 50  0000 L CNN
F 1 "100kΩ" H 7200 4800 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7150 4850 50  0001 C CNN
F 3 "~" H 7150 4850 50  0001 C CNN
	1    7150 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4700 7150 4750
$Comp
L Device:R_Small R9
U 1 1 5CB6B420
P 6750 5400
F 0 "R9" H 6800 5450 50  0000 L CNN
F 1 "100kΩ" H 6800 5350 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6750 5400 50  0001 C CNN
F 3 "~" H 6750 5400 50  0001 C CNN
	1    6750 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 5250 6750 5300
Wire Wire Line
	6750 5250 6850 5250
Wire Wire Line
	6750 5500 6750 5550
Wire Wire Line
	7150 5450 7150 5550
Wire Wire Line
	6750 5550 7150 5550
Connection ~ 7150 5550
Wire Wire Line
	7150 5550 7150 5650
Wire Wire Line
	7150 4950 7150 5000
Wire Wire Line
	7150 5000 7450 5000
Connection ~ 7150 5000
Wire Wire Line
	7150 5000 7150 5050
Text GLabel 7450 5000 2    50   Input ~ 0
Vadap_IO9
Wire Wire Line
	900  3700 900  3800
Wire Wire Line
	8300 5700 8300 5800
$Comp
L power:+BATT #PWR01
U 1 1 5D062D43
P 900 3250
F 0 "#PWR01" H 900 3100 50  0001 C CNN
F 1 "+BATT" H 915 3423 50  0000 C CNN
F 2 "" H 900 3250 50  0001 C CNN
F 3 "" H 900 3250 50  0001 C CNN
	1    900  3250
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR039
U 1 1 5D08BA1C
P 8850 5000
F 0 "#PWR039" H 8850 4850 50  0001 C CNN
F 1 "VBUS" H 8865 5173 50  0000 C CNN
F 2 "" H 8850 5000 50  0001 C CNN
F 3 "" H 8850 5000 50  0001 C CNN
	1    8850 5000
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR020
U 1 1 5D0A733C
P 4950 2350
F 0 "#PWR020" H 4950 2200 50  0001 C CNN
F 1 "VBUS" H 4965 2523 50  0000 C CNN
F 2 "" H 4950 2350 50  0001 C CNN
F 3 "" H 4950 2350 50  0001 C CNN
	1    4950 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR015
U 1 1 5D0A73DC
P 4300 2150
F 0 "#PWR015" H 4300 2000 50  0001 C CNN
F 1 "+BATT" H 4315 2323 50  0000 C CNN
F 2 "" H 4300 2150 50  0001 C CNN
F 3 "" H 4300 2150 50  0001 C CNN
	1    4300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 5800 8300 5800
Wire Wire Line
	8600 5500 8750 5500
Wire Wire Line
	8750 5500 8750 5800
$Comp
L Sensor_Temperature:MCP9804_MSOP U2
U 1 1 5CB860AF
P 4000 5050
F 0 "U2" H 3650 5650 50  0000 L CNN
F 1 "MCP9808_MSOP" H 3350 5550 50  0000 L CNN
F 2 "Package_SO:MSOP-8_3x3mm_P0.65mm" H 3000 4550 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22203b.pdf" H 3750 5500 50  0001 C CNN
	1    4000 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5CBA293A
P 4750 4600
F 0 "C6" H 4842 4646 50  0000 L CNN
F 1 "100nF" H 4842 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4750 4600 50  0001 C CNN
F 3 "~" H 4750 4600 50  0001 C CNN
	1    4750 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5CBA2AFC
P 4750 4700
F 0 "#PWR019" H 4750 4450 50  0001 C CNN
F 1 "GND" H 4900 4600 50  0000 C CNN
F 2 "" H 4750 4700 50  0001 C CNN
F 3 "" H 4750 4700 50  0001 C CNN
	1    4750 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 5CBA2BA0
P 4350 4300
F 0 "#PWR017" H 4350 4150 50  0001 C CNN
F 1 "+3.3V" H 4365 4473 50  0000 C CNN
F 2 "" H 4350 4300 50  0001 C CNN
F 3 "" H 4350 4300 50  0001 C CNN
	1    4350 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4550 4000 4400
Wire Wire Line
	4000 4400 4350 4400
Wire Wire Line
	4750 4400 4750 4500
Wire Wire Line
	4350 4300 4350 4400
Connection ~ 4350 4400
Wire Wire Line
	4350 4400 4750 4400
Text GLabel 3600 4750 0    50   Input ~ 0
SDA
Text GLabel 3600 4850 0    50   Input ~ 0
SCL
$Comp
L power:GND #PWR013
U 1 1 5CBC01AE
P 3750 6250
F 0 "#PWR013" H 3750 6000 50  0001 C CNN
F 1 "GND" H 3900 6150 50  0000 C CNN
F 2 "" H 3750 6250 50  0001 C CNN
F 3 "" H 3750 6250 50  0001 C CNN
	1    3750 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5550 4000 5650
Wire Wire Line
	4000 5650 3750 5650
Wire Wire Line
	3750 5650 3750 5750
Wire Wire Line
	3600 5150 3450 5150
Wire Wire Line
	3450 5150 3450 5250
Wire Wire Line
	3450 5650 3750 5650
Connection ~ 3750 5650
Wire Wire Line
	3600 5250 3450 5250
Connection ~ 3450 5250
Wire Wire Line
	3450 5250 3450 5350
Wire Wire Line
	3600 5350 3450 5350
Connection ~ 3450 5350
Wire Wire Line
	3450 5350 3450 5650
$Comp
L RF_ZigBee:XBee_SMT U5
U 1 1 5CE50B8D
P 9700 2150
F 0 "U5" H 10150 3250 50  0000 C CNN
F 1 "XBee_SMT" H 10150 3150 50  0000 C CNN
F 2 "RF_Module:Digi_XBee_SMT" H 10540 1090 50  0001 C CNN
F 3 "http://www.digi.com/resources/documentation/digidocs/pdfs/90002126.pdf" H 9700 1750 50  0001 C CNN
	1    9700 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 5CE76E8D
P 9700 3450
F 0 "#PWR042" H 9700 3200 50  0001 C CNN
F 1 "GND" H 9850 3350 50  0000 C CNN
F 2 "" H 9700 3450 50  0001 C CNN
F 3 "" H 9700 3450 50  0001 C CNN
	1    9700 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 3250 9500 3350
Wire Wire Line
	9500 3350 9600 3350
Wire Wire Line
	9900 3350 9900 3250
Wire Wire Line
	9800 3250 9800 3350
Connection ~ 9800 3350
Wire Wire Line
	9800 3350 9900 3350
Wire Wire Line
	9700 3250 9700 3350
Connection ~ 9700 3350
Wire Wire Line
	9700 3350 9800 3350
Wire Wire Line
	9600 3250 9600 3350
Connection ~ 9600 3350
Wire Wire Line
	9600 3350 9700 3350
Wire Wire Line
	9700 3350 9700 3450
NoConn ~ 10800 2150
Wire Wire Line
	9800 1150 9800 750 
Wire Wire Line
	9800 750  10600 750 
Wire Wire Line
	10600 750  10600 850 
$Comp
L power:GND #PWR044
U 1 1 5CF9F74A
P 10600 850
F 0 "#PWR044" H 10600 600 50  0001 C CNN
F 1 "GND" H 10750 750 50  0000 C CNN
F 2 "" H 10600 850 50  0001 C CNN
F 3 "" H 10600 850 50  0001 C CNN
	1    10600 850 
	1    0    0    -1  
$EndComp
Text GLabel 8600 2350 0    50   Input ~ 0
RESET
NoConn ~ 8600 3050
NoConn ~ 8600 2950
NoConn ~ 8600 2850
NoConn ~ 8600 2750
NoConn ~ 8600 2650
NoConn ~ 8600 2450
NoConn ~ 8600 2150
NoConn ~ 8600 2050
NoConn ~ 8600 1950
NoConn ~ 8600 1850
NoConn ~ 10800 1350
NoConn ~ 10800 1450
NoConn ~ 10800 1550
NoConn ~ 10800 1650
NoConn ~ 10800 1750
NoConn ~ 10800 1850
$Comp
L power:+3.3V #PWR041
U 1 1 5CF9F74B
P 9700 750
F 0 "#PWR041" H 9700 600 50  0001 C CNN
F 1 "+3.3V" H 9550 850 50  0000 C CNN
F 2 "" H 9700 750 50  0001 C CNN
F 3 "" H 9700 750 50  0001 C CNN
	1    9700 750 
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5CF9F74C
P 9300 950
F 0 "C10" H 9392 996 50  0000 L CNN
F 1 "100nF" H 9392 905 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9300 950 50  0001 C CNN
F 3 "~" H 9300 950 50  0001 C CNN
	1    9300 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1150 9700 800 
Wire Wire Line
	9700 800  9300 800 
Wire Wire Line
	9300 800  9300 850 
Connection ~ 9700 800 
Wire Wire Line
	9700 800  9700 750 
$Comp
L power:GND #PWR040
U 1 1 5D1109FA
P 9300 1100
F 0 "#PWR040" H 9300 850 50  0001 C CNN
F 1 "GND" H 9150 1000 50  0000 C CNN
F 2 "" H 9300 1100 50  0001 C CNN
F 3 "" H 9300 1100 50  0001 C CNN
	1    9300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1050 9300 1100
Text Notes 10600 700  0    50   ~ 0
Xbee module
$Comp
L LTC3536EMSEPBF:LTC3536EMSEPBF U1
U 1 1 5CD156EB
P 650 1500
F 0 "U1" H 2275 1765 50  0000 C CNN
F 1 "LTC3536EMSEPBF" H 2275 1674 50  0000 C CNN
F 2 "LTC3536EMSEPBF:MSOP-12_MSE" H 1500 1550 50  0001 L BNN
F 3 "LTC3536EMSE#PBF-ND" H 1800 1750 50  0001 L BNN
F 4 "LTC3536EMSE#PBF" H 1950 1650 50  0001 L BNN "Field4"
F 5 "MSOP-12 Linear Technology" H 1800 1750 50  0001 L BNN "Field5"
F 6 "https://www.digikey.com/product-detail/en/linear-technology-analog-devices/LTC3536EMSE-PBF/LTC3536EMSE-PBF-ND/2720693?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 400 1650 50  0001 L BNN "Field6"
F 7 "DC-DC converter; step up/down; Uin: 1.8÷5.5V; Uout: 1.8÷5" H 400 1650 50  0001 L BNN "Field7"
F 8 "Linear Technology/Analog" H 1800 1750 50  0001 L BNN "Field8"
	1    650  1500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J4
U 1 1 5CD8F2D5
P 9000 4350
F 0 "J4" H 9000 3950 50  0000 R CNN
F 1 "FTDI cable connector" H 9100 3850 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 9000 4350 50  0001 C CNN
F 3 "~" H 9000 4350 50  0001 C CNN
	1    9000 4350
	-1   0    0    1   
$EndComp
Text GLabel 8600 1450 0    50   Input ~ 0
XBEE_RX
Text GLabel 8600 1350 0    50   Input ~ 0
XBEE_TX
Text GLabel 8600 1650 0    50   Input ~ 0
XBEE_RTS
Text GLabel 8600 1550 0    50   Input ~ 0
XBEE_CTS
$Comp
L power:GND #PWR037
U 1 1 5CDA2EB9
P 9400 4700
F 0 "#PWR037" H 9400 4450 50  0001 C CNN
F 1 "GND" H 9300 4550 50  0000 C CNN
F 2 "" H 9400 4700 50  0001 C CNN
F 3 "" H 9400 4700 50  0001 C CNN
	1    9400 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4550 9400 4550
Text GLabel 9200 4450 2    50   Input ~ 0
XBEE_CTS
Text GLabel 9200 4050 2    50   Input ~ 0
XBEE_RTS
Text GLabel 9900 5950 0    50   Input ~ 0
XBEE_RX
Text GLabel 10400 5950 2    50   Input ~ 0
XBEE_TX
Text GLabel 9200 4250 2    50   Input ~ 0
FTDI_TX
Text GLabel 9200 4150 2    50   Input ~ 0
FTDI_RX
NoConn ~ 9200 4350
Text GLabel 9900 6050 0    50   Input ~ 0
FTDI_TX
Text GLabel 10400 6050 2    50   Input ~ 0
FTDI_RX
Text GLabel 10400 5850 2    50   Input ~ 0
AVR_RX
Text GLabel 9900 5850 0    50   Input ~ 0
AVR_TX
$Comp
L Device:L_Small L1
U 1 1 5CEEBE37
P 1150 1950
F 0 "L1" H 1250 1900 50  0000 C CNN
F 1 "4.7uH" H 1300 1950 50  0000 C CNN
F 2 "Inductor_SMD:L_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 1150 1950 50  0001 C CNN
F 3 "~" H 1150 1950 50  0001 C CNN
	1    1150 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 1850 1150 1850
Wire Wire Line
	1450 2050 1150 2050
$Comp
L MOSFET-P:MOSFET-P U3
U 1 1 5CF612D7
P 4300 2750
F 0 "U3" H 4393 2780 30  0000 L CNN
F 1 "DMG2301L" H 4393 2720 30  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4300 2700 60  0001 C CNN
F 3 "" H 4300 2700 60  0000 C CNN
	1    4300 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 2750 4950 3050
Connection ~ 4300 3050
$Comp
L Device:CP_Small C3
U 1 1 5D128009
P 3650 3350
F 0 "C3" H 3400 3450 50  0000 L CNN
F 1 "10uF" H 3400 3350 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 3650 3350 50  0001 C CNN
F 3 "~" H 3650 3350 50  0001 C CNN
	1    3650 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5D13B74A
P 3650 3650
F 0 "#PWR012" H 3650 3400 50  0001 C CNN
F 1 "GND" H 3655 3477 50  0000 C CNN
F 2 "" H 3650 3650 50  0001 C CNN
F 3 "" H 3650 3650 50  0001 C CNN
	1    3650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3450 3650 3650
Wire Wire Line
	1450 1650 850  1650
Wire Wire Line
	850  1650 850  1750
Wire Wire Line
	850  2200 1350 2200
Wire Wire Line
	1350 2200 1350 2350
Wire Wire Line
	1450 1950 1350 1950
Wire Wire Line
	1350 1950 1350 2200
Connection ~ 1350 2200
Wire Wire Line
	1450 1750 850  1750
Connection ~ 850  1750
Wire Wire Line
	850  1750 850  2200
$Comp
L power:GND #PWR05
U 1 1 5D19F744
P 1350 2350
F 0 "#PWR05" H 1350 2100 50  0001 C CNN
F 1 "GND" H 1355 2177 50  0000 C CNN
F 2 "" H 1350 2350 50  0001 C CNN
F 3 "" H 1350 2350 50  0001 C CNN
	1    1350 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5D208B96
P 3300 1600
F 0 "R1" V 3104 1600 50  0000 C CNN
F 1 "49.9kΩ" V 3195 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3300 1600 50  0001 C CNN
F 3 "~" H 3300 1600 50  0001 C CNN
	1    3300 1600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5D208C50
P 3800 1850
F 0 "R3" H 3859 1896 50  0000 L CNN
F 1 "221kΩ" H 3859 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3800 1850 50  0001 C CNN
F 3 "~" H 3800 1850 50  0001 C CNN
	1    3800 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5D208CEA
P 4250 1700
F 0 "R4" V 4054 1700 50  0000 C CNN
F 1 "1000kΩ" V 4145 1700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4250 1700 50  0001 C CNN
F 3 "~" H 4250 1700 50  0001 C CNN
	1    4250 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5D208F86
P 3800 1400
F 0 "R2" H 3859 1446 50  0000 L CNN
F 1 "6.49kΩ" H 3859 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3800 1400 50  0001 C CNN
F 3 "~" H 3800 1400 50  0001 C CNN
	1    3800 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5D2091DD
P 3800 1100
F 0 "C4" H 3892 1146 50  0000 L CNN
F 1 "47pF" H 3892 1055 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3800 1100 50  0001 C CNN
F 3 "~" H 3800 1100 50  0001 C CNN
	1    3800 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C5
U 1 1 5D20971C
P 4550 1350
F 0 "C5" H 4700 1400 50  0000 L CNN
F 1 "47uF" H 4650 1300 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4550 1350 50  0001 C CNN
F 3 "~" H 4550 1350 50  0001 C CNN
	1    4550 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5D209863
P 3600 1600
F 0 "C2" V 3400 1550 50  0000 L CNN
F 1 "220pF" V 3500 1500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3600 1600 50  0001 C CNN
F 3 "~" H 3600 1600 50  0001 C CNN
	1    3600 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 1600 3200 1600
Wire Wire Line
	3400 1600 3500 1600
$Comp
L power:GND #PWR018
U 1 1 5D2D66DC
P 4550 1750
F 0 "#PWR018" H 4550 1500 50  0001 C CNN
F 1 "GND" H 4555 1577 50  0000 C CNN
F 2 "" H 4550 1750 50  0001 C CNN
F 3 "" H 4550 1750 50  0001 C CNN
	1    4550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1600 3800 1600
Wire Wire Line
	3800 1600 3800 1500
Wire Wire Line
	3800 1600 3800 1700
Connection ~ 3800 1600
Wire Wire Line
	3100 1700 3800 1700
Connection ~ 3800 1700
Wire Wire Line
	3800 1700 3800 1750
Wire Wire Line
	3800 1700 4150 1700
Wire Wire Line
	3800 1200 3800 1300
Text GLabel 3550 2300 3    50   Input ~ 0
LTC_VOUT
Text GLabel 3100 1000 0    50   Input ~ 0
LTC_VOUT
Wire Wire Line
	3100 1000 3800 1000
Connection ~ 3800 1000
Wire Wire Line
	3800 1000 4450 1000
Wire Wire Line
	4350 1700 4450 1700
Wire Wire Line
	4450 1700 4450 1000
Wire Wire Line
	4550 1450 4550 1500
Wire Wire Line
	3100 1100 3300 1100
Wire Wire Line
	3100 1100 3100 1500
$Comp
L power:GND #PWR011
U 1 1 5D57C9FB
P 3300 1100
F 0 "#PWR011" H 3300 850 50  0001 C CNN
F 1 "GND" H 3305 927 50  0000 C CNN
F 2 "" H 3300 1100 50  0001 C CNN
F 3 "" H 3300 1100 50  0001 C CNN
	1    3300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1900 3300 1900
Wire Wire Line
	3300 1900 3300 1950
Wire Wire Line
	3300 2000 3100 2000
Wire Wire Line
	3300 1950 3650 1950
Wire Wire Line
	3650 1950 3650 2800
Wire Wire Line
	3650 3050 4300 3050
Connection ~ 3300 1950
Wire Wire Line
	3300 1950 3300 2000
$Comp
L power:GND #PWR014
U 1 1 5D604911
P 3800 2000
F 0 "#PWR014" H 3800 1750 50  0001 C CNN
F 1 "GND" H 3805 1827 50  0000 C CNN
F 2 "" H 3800 2000 50  0001 C CNN
F 3 "" H 3800 2000 50  0001 C CNN
	1    3800 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1950 3800 2000
Wire Wire Line
	700  1550 700  2800
Wire Wire Line
	700  2800 3650 2800
Wire Wire Line
	700  1550 1450 1550
Connection ~ 3650 2800
Wire Wire Line
	3650 2800 3650 3050
Wire Wire Line
	3100 1800 3300 1800
Wire Wire Line
	3300 1800 3300 1900
Connection ~ 3300 1900
NoConn ~ 4400 5050
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 5DD0F7AA
P 3200 2100
F 0 "FB1" V 3350 2100 50  0000 C CNN
F 1 "BL01RN1A1F1J" V 3450 2100 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L5.3mm_D2.2mm_P10.16mm_Horizontal_Vishay_IM-1" V 3130 2100 50  0001 C CNN
F 3 "~" H 3200 2100 50  0001 C CNN
	1    3200 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 5000 8850 5100
Wire Wire Line
	3300 2100 3550 2100
Wire Wire Line
	3550 2100 3550 2300
Wire Wire Line
	6750 5250 6450 5250
Wire Wire Line
	6450 5250 6450 5100
Connection ~ 6750 5250
$Comp
L power:VBUS #PWR027
U 1 1 5CF9C43C
P 6450 5100
F 0 "#PWR027" H 6450 4950 50  0001 C CNN
F 1 "VBUS" H 6465 5273 50  0000 C CNN
F 2 "" H 6450 5100 50  0001 C CNN
F 3 "" H 6450 5100 50  0001 C CNN
	1    6450 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 5D414B21
P 5000 800
F 0 "#PWR022" H 5000 650 50  0001 C CNN
F 1 "+3.3V" H 5015 973 50  0000 C CNN
F 2 "" H 5000 800 50  0001 C CNN
F 3 "" H 5000 800 50  0001 C CNN
	1    5000 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 800  5000 1000
$Comp
L Device:C_Small C7
U 1 1 5D6EF7B9
P 5000 1300
F 0 "C7" H 5092 1346 50  0000 L CNN
F 1 "220nF" H 5092 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5000 1300 50  0001 C CNN
F 3 "~" H 5000 1300 50  0001 C CNN
	1    5000 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1200 5000 1100
Wire Wire Line
	5000 1100 4550 1100
Wire Wire Line
	4550 1100 4550 1250
Wire Wire Line
	4550 1500 5000 1500
Wire Wire Line
	5000 1500 5000 1400
Connection ~ 4550 1500
Wire Wire Line
	4550 1500 4550 1750
Wire Wire Line
	8600 5100 8850 5100
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D76E543
P 5200 1000
F 0 "#FLG01" H 5200 1075 50  0001 C CNN
F 1 "PWR_FLAG" V 5200 1128 50  0000 L CNN
F 2 "" H 5200 1000 50  0001 C CNN
F 3 "~" H 5200 1000 50  0001 C CNN
	1    5200 1000
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5CF1862E
P 5400 1300
F 0 "C8" H 5492 1346 50  0000 L CNN
F 1 "100nF" H 5492 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5400 1300 50  0001 C CNN
F 3 "~" H 5400 1300 50  0001 C CNN
	1    5400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1100 5400 1100
Wire Wire Line
	5400 1100 5400 1200
Connection ~ 5000 1100
Wire Wire Line
	5400 1400 5400 1500
Wire Wire Line
	5400 1500 5000 1500
Connection ~ 5000 1500
Wire Wire Line
	5000 1000 5000 1100
Connection ~ 5000 1000
Wire Wire Line
	4450 1000 5000 1000
Connection ~ 4450 1000
Wire Wire Line
	5000 1000 5200 1000
$Comp
L Device:D_Schottky D2
U 1 1 5D4E090C
P 4950 2550
F 0 "D2" V 4900 2750 50  0000 C CNN
F 1 "MBR120" V 5000 2750 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123F" H 4950 2550 50  0001 C CNN
F 3 "~" H 4950 2550 50  0001 C CNN
	1    4950 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 2700 4950 2750
Connection ~ 4950 2750
Wire Wire Line
	4300 2950 4300 3050
Wire Wire Line
	4500 2750 4950 2750
Wire Wire Line
	3650 3050 3650 3250
Connection ~ 3650 3050
Wire Wire Line
	4950 2350 4950 2400
$Comp
L Device:C_Small C9
U 1 1 5CF7F879
P 8900 950
F 0 "C9" H 8992 996 50  0000 L CNN
F 1 "1uF" H 8992 905 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8900 950 50  0001 C CNN
F 3 "~" H 8900 950 50  0001 C CNN
	1    8900 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 800  8900 800 
Wire Wire Line
	8900 800  8900 850 
Connection ~ 9300 800 
$Comp
L power:GND #PWR038
U 1 1 5CFA34DC
P 8900 1100
F 0 "#PWR038" H 8900 850 50  0001 C CNN
F 1 "GND" H 8750 1000 50  0000 C CNN
F 2 "" H 8900 1100 50  0001 C CNN
F 3 "" H 8900 1100 50  0001 C CNN
	1    8900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1050 8900 1100
$Comp
L DS1337+:DS1337+ IC1
U 1 1 5D3F93BD
P 1500 4900
F 0 "IC1" H 1850 5065 50  0000 C CNN
F 1 "DS1337+" H 1850 4974 50  0000 C CNN
F 2 "DS1337+:DIP794W56P254L938H457Q8N" H 2350 4900 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1337-DS1337C.pdf" H 2350 4850 50  0001 L CNN
F 4 "Maxim DS1337+ Real Time Clock, 7B RAM 8-Pin PDIP" H 2350 4750 50  0001 L CNN "Description"
F 5 "4.572" H 2350 4650 50  0001 L CNN "Height"
F 6 "Maxim Integrated" H 2350 4550 50  0001 L CNN "Manufacturer_Name"
F 7 "DS1337+" H 2350 4400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "700-DS1337" H 2350 4300 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=700-DS1337" H 2350 4200 50  0001 L CNN "Mouser Price/Stock"
F 10 "7860749P" H 2350 4100 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/7860749P" H 2350 4000 50  0001 L CNN "RS Price/Stock"
	1    1500 4900
	1    0    0    -1  
$EndComp
Text GLabel 2400 5200 2    50   Input ~ 0
SCL
Text GLabel 2400 5300 2    50   Input ~ 0
SDA
$Comp
L power:+3.3V #PWR07
U 1 1 5D40E682
P 2550 4700
F 0 "#PWR07" H 2550 4550 50  0001 C CNN
F 1 "+3.3V" H 2565 4873 50  0000 C CNN
F 2 "" H 2550 4700 50  0001 C CNN
F 3 "" H 2550 4700 50  0001 C CNN
	1    2550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5000 2550 5000
Wire Wire Line
	2550 5000 2550 4900
$Comp
L Device:C_Small C1
U 1 1 5D41918E
P 2800 5150
F 0 "C1" H 2892 5196 50  0000 L CNN
F 1 "100nF" H 2892 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2800 5150 50  0001 C CNN
F 3 "~" H 2800 5150 50  0001 C CNN
	1    2800 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5D41943A
P 2800 5350
F 0 "#PWR010" H 2800 5100 50  0001 C CNN
F 1 "GND" H 2805 5177 50  0000 C CNN
F 2 "" H 2800 5350 50  0001 C CNN
F 3 "" H 2800 5350 50  0001 C CNN
	1    2800 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4900 2800 4900
Wire Wire Line
	2800 4900 2800 5050
Connection ~ 2550 4900
$Comp
L CRYSTAL:XTAL X1
U 1 1 5D42EE3C
P 650 5000
F 0 "X1" V 620 5088 30  0000 L CNN
F 1 "XTAL" V 680 5088 30  0000 L CNN
F 2 "Crystal:Crystal_C38-LF_D3.0mm_L8.0mm_Vertical" H 650 5000 60  0001 C CNN
F 3 "" H 650 5000 60  0000 C CNN
	1    650  5000
	0    1    1    0   
$EndComp
Wire Wire Line
	650  4700 650  4850
Wire Wire Line
	650  5250 650  5150
Wire Wire Line
	1300 5000 1150 5000
Wire Wire Line
	1150 5000 1150 4700
Wire Wire Line
	1150 4700 650  4700
$Comp
L power:GND #PWR04
U 1 1 5D4529CD
P 1150 5500
F 0 "#PWR04" H 1150 5250 50  0001 C CNN
F 1 "GND" H 1155 5327 50  0000 C CNN
F 2 "" H 1150 5500 50  0001 C CNN
F 3 "" H 1150 5500 50  0001 C CNN
	1    1150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5300 1150 5300
Wire Wire Line
	1150 5300 1150 5500
NoConn ~ 2400 5100
Text GLabel 1300 5200 0    50   Input ~ 0
INTA_IO2
NoConn ~ 6250 1300
Wire Wire Line
	9400 4550 9400 4700
Text GLabel 7450 3300 2    50   Input ~ 0
AVR_RX
Text GLabel 7450 3400 2    50   Input ~ 0
AVR_TX
Wire Notes Line
	11150 3350 10100 3350
Wire Notes Line
	10100 3350 10100 3600
Wire Notes Line
	10100 3600 8000 3600
Wire Notes Line
	6100 550  6100 4400
Wire Notes Line
	6100 4400 8000 4400
Wire Notes Line
	3250 4050 6100 4050
Wire Notes Line
	550  550  11150 550 
Text Notes 5750 4200 0    50   ~ 0
RESET
Wire Notes Line
	6250 4400 6250 5950
Wire Notes Line
	6900 5950 6900 7150
Wire Notes Line
	6900 7150 5200 7150
$Comp
L Connector:Conn_01x07_Female SHT31
U 1 1 5D794BC3
P 1750 3550
F 0 "SHT31" H 1644 4035 50  0000 C CNN
F 1 "SHT31" H 1644 3944 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 1750 3550 50  0001 C CNN
F 3 "~" H 1750 3550 50  0001 C CNN
	1    1750 3550
	-1   0    0    -1  
$EndComp
Text GLabel 1950 3450 2    50   Input ~ 0
SCL
Text GLabel 1950 3550 2    50   Input ~ 0
SDA
Text GLabel 1950 3750 2    50   Input ~ 0
RESET
Wire Wire Line
	1950 3650 2350 3650
Wire Wire Line
	1950 3350 2350 3350
Wire Wire Line
	2350 3350 2350 3650
Connection ~ 2350 3650
$Comp
L power:+3.3V #PWR08
U 1 1 5D801B38
P 2350 3150
F 0 "#PWR08" H 2350 3000 50  0001 C CNN
F 1 "+3.3V" H 2365 3323 50  0000 C CNN
F 2 "" H 2350 3150 50  0001 C CNN
F 3 "" H 2350 3150 50  0001 C CNN
	1    2350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3250 2350 3250
Wire Wire Line
	2350 3250 2350 3150
NoConn ~ 1950 3850
Wire Notes Line
	550  4150 1950 4150
Wire Notes Line
	1950 4400 1950 4150
Wire Notes Line
	1950 4400 3250 4400
Wire Notes Line
	550  5750 3250 5750
Wire Notes Line
	5200 5950 8000 5950
$Comp
L Connector:Conn_01x05_Female APDS1
U 1 1 5D8D2053
P 1300 6650
F 0 "APDS1" H 1150 6200 50  0000 L CNN
F 1 "APDS" H 1150 6300 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1300 6650 50  0001 C CNN
F 3 "~" H 1300 6650 50  0001 C CNN
	1    1300 6650
	-1   0    0    -1  
$EndComp
NoConn ~ 1500 6450
$Comp
L power:GND #PWR03
U 1 1 5D91364A
P 2100 7100
F 0 "#PWR03" H 2100 6850 50  0001 C CNN
F 1 "GND" V 2105 6927 50  0000 C CNN
F 2 "" H 2100 7100 50  0001 C CNN
F 3 "" H 2100 7100 50  0001 C CNN
	1    2100 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  5100 900  5250
Wire Wire Line
	900  5250 650  5250
Wire Wire Line
	900  5100 1300 5100
Text GLabel 1500 6850 2    50   Input ~ 0
SCL
Text GLabel 1500 6750 2    50   Input ~ 0
SDA
$Comp
L power:+3.3V #PWR06
U 1 1 5D948A5C
P 1500 6650
F 0 "#PWR06" H 1500 6500 50  0001 C CNN
F 1 "+3.3V" V 1500 6900 50  0000 C CNN
F 2 "" H 1500 6650 50  0001 C CNN
F 3 "" H 1500 6650 50  0001 C CNN
	1    1500 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 6550 2100 6550
Text Notes 600  4250 0    50   ~ 0
Real time clock
Text Notes 4800 4150 0    50   ~ 0
MCP9808
Text Notes 1300 3050 0    50   ~ 0
Battery
Text Notes 2950 3050 0    50   ~ 0
SHT31
Text Notes 6600 6100 0    50   ~ 0
I2C
Wire Wire Line
	2800 5250 2800 5350
Wire Wire Line
	2550 4700 2550 4900
Text GLabel 7450 3200 2    50   Input ~ 0
INTA_IO2
Text GLabel 7450 3000 2    50   Input ~ 0
AVR_DBG_RX
Text GLabel 7450 3100 2    50   Input ~ 0
AVR_DBG_TX
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J3
U 1 1 5DADF6F5
P 10100 5950
F 0 "J3" H 10150 6267 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 10150 6176 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 10100 5950 50  0001 C CNN
F 3 "~" H 10100 5950 50  0001 C CNN
	1    10100 5950
	1    0    0    -1  
$EndComp
Text GLabel 9900 6150 0    50   Input ~ 0
AVR_DBG_RX
Text GLabel 10400 6150 2    50   Input ~ 0
AVR_DBG_TX
NoConn ~ 8600 5300
NoConn ~ 8600 5400
Text GLabel 7450 1400 2    50   Input ~ 0
Vadap_IO9
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DB89C4C
P 900 3300
F 0 "#FLG0101" H 900 3375 50  0001 C CNN
F 1 "PWR_FLAG" V 900 3428 50  0000 L CNN
F 2 "" H 900 3300 50  0001 C CNN
F 3 "~" H 900 3300 50  0001 C CNN
	1    900  3300
	0    1    1    0   
$EndComp
Connection ~ 900  3300
Wire Wire Line
	900  3300 900  3400
$Comp
L Transistor_FET:2N7002 Q2
U 1 1 5DBF11B0
P 2200 6800
F 0 "Q2" H 2000 7050 50  0000 L CNN
F 1 "2N7002" H 1850 6950 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2400 6725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 2200 6800 50  0001 L CNN
	1    2200 6800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2100 7000 2100 7050
Wire Wire Line
	2100 6550 2100 6600
Text GLabel 7450 1500 2    50   BiDi ~ 0
APDS_IO9
$Comp
L Transistor_FET:2N7002 Q4
U 1 1 5DC78807
P 3850 5950
F 0 "Q4" H 3650 6200 50  0000 L CNN
F 1 "2N7002" H 3500 6100 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4050 5875 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 3850 5950 50  0001 L CNN
	1    3850 5950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 6150 3750 6250
Text GLabel 7450 3500 2    50   BiDi ~ 0
TMP_IO5
Text GLabel 2400 6800 2    50   BiDi ~ 0
APDS_IO9
Text GLabel 4050 5950 2    50   BiDi ~ 0
TMP_IO5
$Comp
L Transistor_FET:2N7002 Q3
U 1 1 5DC8FE6C
P 2450 3850
F 0 "Q3" H 2250 4100 50  0000 L CNN
F 1 "2N7002" H 2100 4000 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2650 3775 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 2450 3850 50  0001 L CNN
	1    2450 3850
	-1   0    0    -1  
$EndComp
Wire Notes Line
	550  2900 3250 2900
$Comp
L power:GND #PWR09
U 1 1 5DCD3BE8
P 2350 4150
F 0 "#PWR09" H 2350 3900 50  0001 C CNN
F 1 "GND" H 2500 4050 50  0000 C CNN
F 2 "" H 2350 4150 50  0001 C CNN
F 3 "" H 2350 4150 50  0001 C CNN
	1    2350 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4050 2350 4150
Text GLabel 7450 3600 2    50   BiDi ~ 0
SHT31_IO6
Text GLabel 2650 3850 2    50   BiDi ~ 0
SHT31_IO6
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DCDFE40
P 4000 5650
F 0 "#FLG0102" H 4000 5725 50  0001 C CNN
F 1 "PWR_FLAG" V 4000 5778 50  0000 L CNN
F 2 "" H 4000 5650 50  0001 C CNN
F 3 "~" H 4000 5650 50  0001 C CNN
	1    4000 5650
	0    1    1    0   
$EndComp
Connection ~ 4000 5650
Wire Notes Line
	1650 2900 1650 4150
$Comp
L Device:R_Small R11
U 1 1 5CFD8AF9
P 8300 6100
F 0 "R11" H 8241 6054 50  0000 R CNN
F 1 "25mΩ" H 8241 6145 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8300 6100 50  0001 C CNN
F 3 "~" H 8300 6100 50  0001 C CNN
	1    8300 6100
	-1   0    0    1   
$EndComp
Wire Notes Line
	11150 6500 8000 6500
Wire Notes Line
	11150 550  11150 6500
Wire Notes Line
	8000 550  8000 6500
$Comp
L Connector:Conn_01x01_Female J1
U 1 1 5D0165DF
P 8500 5950
F 0 "J1" H 8527 5976 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8527 5885 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8500 5950 50  0001 C CNN
F 3 "~" H 8500 5950 50  0001 C CNN
	1    8500 5950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 5D01668B
P 8500 6250
F 0 "J2" H 8527 6276 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8527 6185 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8500 6250 50  0001 C CNN
F 3 "~" H 8500 6250 50  0001 C CNN
	1    8500 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5800 8300 5950
Connection ~ 8300 5950
Wire Wire Line
	8300 5950 8300 6000
Wire Wire Line
	8300 6200 8300 6250
$Comp
L power:GND #PWR0101
U 1 1 5D071942
P 8300 6300
F 0 "#PWR0101" H 8300 6050 50  0001 C CNN
F 1 "GND" H 8200 6200 50  0000 C CNN
F 2 "" H 8300 6300 50  0001 C CNN
F 3 "" H 8300 6300 50  0001 C CNN
	1    8300 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 6250 8300 6300
Connection ~ 8300 6250
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D07CEE5
P 2100 7050
F 0 "#FLG0103" H 2100 7125 50  0001 C CNN
F 1 "PWR_FLAG" V 2100 7178 50  0000 L CNN
F 2 "" H 2100 7050 50  0001 C CNN
F 3 "~" H 2100 7050 50  0001 C CNN
	1    2100 7050
	0    1    1    0   
$EndComp
Connection ~ 2100 7050
Wire Wire Line
	2100 7050 2100 7100
NoConn ~ 10500 5000
$Comp
L Device:R_Small R12
U 1 1 5D094127
P 4250 6850
F 0 "R12" H 4309 6896 50  0000 L CNN
F 1 "100kΩ" H 4309 6805 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4250 6850 50  0001 C CNN
F 3 "~" H 4250 6850 50  0001 C CNN
	1    4250 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R13
U 1 1 5D0941C3
P 4250 7250
F 0 "R13" H 4309 7296 50  0000 L CNN
F 1 "100kΩ" H 4309 7205 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4250 7250 50  0001 C CNN
F 3 "~" H 4250 7250 50  0001 C CNN
	1    4250 7250
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR016
U 1 1 5D09435F
P 4250 6650
F 0 "#PWR016" H 4250 6500 50  0001 C CNN
F 1 "+BATT" H 4265 6823 50  0000 C CNN
F 2 "" H 4250 6650 50  0001 C CNN
F 3 "" H 4250 6650 50  0001 C CNN
	1    4250 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 6650 4250 6750
Wire Wire Line
	4250 6950 4250 7050
$Comp
L power:GND #PWR028
U 1 1 5D0BD994
P 4250 7450
F 0 "#PWR028" H 4250 7200 50  0001 C CNN
F 1 "GND" H 4400 7350 50  0000 C CNN
F 2 "" H 4250 7450 50  0001 C CNN
F 3 "" H 4250 7450 50  0001 C CNN
	1    4250 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 7350 4250 7450
Text GLabel 7450 2200 2    50   Input ~ 0
VBATT_ADC0
Text GLabel 4450 7050 2    50   Input ~ 0
VBATT_ADC0
Wire Wire Line
	4250 7050 4450 7050
Connection ~ 4250 7050
Wire Wire Line
	4250 7050 4250 7150
Wire Notes Line
	4050 6400 5200 6400
Wire Notes Line
	4050 6400 4050 6600
Wire Notes Line
	4050 6600 3250 6600
Wire Notes Line
	3250 2900 3250 7700
Wire Notes Line
	5200 4050 5200 7700
Wire Notes Line
	550  550  550  7700
Wire Notes Line
	550  7700 5200 7700
Text Notes 7400 700  0    50   ~ 0
ATmega328p
Text Notes 650  700  0    50   ~ 0
PMU
Text Notes 600  5900 0    50   ~ 0
APDS (light)
Text Notes 7650 4550 0    50   ~ 0
Vadap
Text Notes 4650 6550 0    50   ~ 0
Battery level
Text Notes 10700 3500 0    50   ~ 0
Connector
Wire Wire Line
	4300 3050 4950 3050
$Comp
L Device:D_Schottky D1
U 1 1 5D16F809
P 4300 2350
F 0 "D1" V 4250 2550 50  0000 C CNN
F 1 "MBR120" V 4350 2550 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123F" H 4300 2350 50  0001 C CNN
F 3 "~" H 4300 2350 50  0001 C CNN
	1    4300 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 2150 4300 2200
Wire Wire Line
	4300 2500 4300 2550
$EndSCHEMATC
