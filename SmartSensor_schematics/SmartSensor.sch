EESchema Schematic File Version 4
LIBS:SmartSensor-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Smart Sensor"
Date "2019-06-07"
Rev "v2.0"
Comp "Avans Hogeschool"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
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
P 10500 5550
F 0 "J8" H 10550 5867 50  0000 C CNN
F 1 "6 PIN ISP" H 10550 5776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 10500 5550 50  0001 C CNN
F 3 "~" H 10500 5550 50  0001 C CNN
	1    10500 5550
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
Text GLabel 10300 5450 0    50   Input ~ 0
MISO
Text GLabel 10300 5550 0    50   Input ~ 0
SCK
Text GLabel 10300 5650 0    50   Input ~ 0
RESET
Text GLabel 10800 5550 2    50   Input ~ 0
MOSI
$Comp
L power:GND #PWR046
U 1 1 5D006BC6
P 10950 5800
F 0 "#PWR046" H 10950 5550 50  0001 C CNN
F 1 "GND" H 10955 5627 50  0000 C CNN
F 2 "" H 10950 5800 50  0001 C CNN
F 3 "" H 10950 5800 50  0001 C CNN
	1    10950 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 5650 10950 5650
Wire Wire Line
	10950 5650 10950 5800
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
NoConn ~ 7450 1900
NoConn ~ 7450 2000
NoConn ~ 7450 2500
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
P 7150 5700
F 0 "#PWR034" H 7150 5450 50  0001 C CNN
F 1 "GND" H 7155 5527 50  0000 C CNN
F 2 "" H 7150 5700 50  0001 C CNN
F 3 "" H 7150 5700 50  0001 C CNN
	1    7150 5700
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
	7150 5550 7150 5700
Wire Wire Line
	7150 4950 7150 5000
Wire Wire Line
	7150 5000 7450 5000
Connection ~ 7150 5000
Wire Wire Line
	7150 5000 7150 5050
Text GLabel 7450 5000 2    50   Input ~ 0
Vadap_IO9
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
P 3750 6200
F 0 "#PWR013" H 3750 5950 50  0001 C CNN
F 1 "GND" H 3900 6100 50  0000 C CNN
F 2 "" H 3750 6200 50  0001 C CNN
F 3 "" H 3750 6200 50  0001 C CNN
	1    3750 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5550 4000 5650
Wire Wire Line
	4000 5650 3750 5650
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
L Connector:Conn_01x06_Female J4
U 1 1 5CD8F2D5
P 8200 4200
F 0 "J4" H 8200 3800 50  0000 R CNN
F 1 "FTDI cable connector" H 8300 3700 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8200 4200 50  0001 C CNN
F 3 "~" H 8200 4200 50  0001 C CNN
	1    8200 4200
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
P 8600 4550
F 0 "#PWR037" H 8600 4300 50  0001 C CNN
F 1 "GND" H 8500 4400 50  0000 C CNN
F 2 "" H 8600 4550 50  0001 C CNN
F 3 "" H 8600 4550 50  0001 C CNN
	1    8600 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4400 8600 4400
Text GLabel 8400 4300 2    50   Input ~ 0
XBEE_CTS
Text GLabel 8400 3900 2    50   Input ~ 0
XBEE_RTS
Text GLabel 9400 6100 0    50   Input ~ 0
XBEE_RX
Text GLabel 9900 6100 2    50   Input ~ 0
XBEE_TX
Text GLabel 8400 4100 2    50   Input ~ 0
FTDI_TX
Text GLabel 8400 4000 2    50   Input ~ 0
FTDI_RX
NoConn ~ 8400 4200
Text GLabel 9400 6200 0    50   Input ~ 0
FTDI_TX
Text GLabel 9900 6200 2    50   Input ~ 0
FTDI_RX
Text GLabel 9900 6000 2    50   Input ~ 0
AVR_RX
Text GLabel 9400 6000 0    50   Input ~ 0
AVR_TX
NoConn ~ 4400 5050
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
	8600 4400 8600 4550
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
Text Notes 5250 4150 0    50   ~ 0
RESET
Wire Notes Line
	6250 4400 6250 5950
Wire Notes Line
	6900 5950 6900 7150
Wire Notes Line
	6900 7150 5200 7150
Wire Notes Line
	550  6100 3250 6100
Wire Notes Line
	5200 5950 8000 5950
Wire Wire Line
	900  5100 900  5250
Wire Wire Line
	900  5250 650  5250
Wire Wire Line
	900  5100 1300 5100
Text Notes 600  4500 0    50   ~ 0
Real time clock
Text Notes 4800 4150 0    50   ~ 0
MCP9808
Text Notes 600  2300 0    50   ~ 0
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
P 9600 6100
F 0 "J3" H 9650 6417 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 9650 6326 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 9600 6100 50  0001 C CNN
F 3 "~" H 9600 6100 50  0001 C CNN
	1    9600 6100
	1    0    0    -1  
$EndComp
Text GLabel 9400 6300 0    50   Input ~ 0
AVR_DBG_RX
Text GLabel 9900 6300 2    50   Input ~ 0
AVR_DBG_TX
Text GLabel 7450 1400 2    50   Input ~ 0
Vadap_IO9
Text GLabel 7450 1500 2    50   BiDi ~ 0
APDS_IO9
Wire Wire Line
	3750 6100 3750 6150
Text GLabel 7450 3500 2    50   BiDi ~ 0
TMP_IO5
Text GLabel 4050 5900 2    50   BiDi ~ 0
TMP_IO5
Text GLabel 7450 3600 2    50   BiDi ~ 0
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
	11150 6500 8000 6500
Wire Notes Line
	11150 550  11150 6500
Wire Notes Line
	8000 550  8000 6500
NoConn ~ 10800 5450
$Comp
L Device:R_Small R12
U 1 1 5D094127
P 4550 6900
F 0 "R12" H 4609 6946 50  0000 L CNN
F 1 "100kΩ" H 4609 6855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4550 6900 50  0001 C CNN
F 3 "~" H 4550 6900 50  0001 C CNN
	1    4550 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R13
U 1 1 5D0941C3
P 4550 7300
F 0 "R13" H 4609 7346 50  0000 L CNN
F 1 "100kΩ" H 4609 7255 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4550 7300 50  0001 C CNN
F 3 "~" H 4550 7300 50  0001 C CNN
	1    4550 7300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR016
U 1 1 5D09435F
P 4550 6700
F 0 "#PWR016" H 4550 6550 50  0001 C CNN
F 1 "+BATT" H 4565 6873 50  0000 C CNN
F 2 "" H 4550 6700 50  0001 C CNN
F 3 "" H 4550 6700 50  0001 C CNN
	1    4550 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 6700 4550 6800
Wire Wire Line
	4550 7000 4550 7100
$Comp
L power:GND #PWR028
U 1 1 5D0BD994
P 4550 7500
F 0 "#PWR028" H 4550 7250 50  0001 C CNN
F 1 "GND" H 4700 7400 50  0000 C CNN
F 2 "" H 4550 7500 50  0001 C CNN
F 3 "" H 4550 7500 50  0001 C CNN
	1    4550 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 7400 4550 7500
Text GLabel 7450 2200 2    50   Input ~ 0
VBATT_ADC0
Text GLabel 4650 7100 2    50   Input ~ 0
VBATT_ADC0
Wire Wire Line
	4550 7100 4650 7100
Connection ~ 4550 7100
Wire Wire Line
	4550 7100 4550 7200
Wire Notes Line
	5200 4050 5200 7700
Wire Notes Line
	550  550  550  7700
Wire Notes Line
	550  7700 5200 7700
Text Notes 7400 700  0    50   ~ 0
ATmega328p
Text Notes 600  6200 0    50   ~ 0
APDS (light)
Text Notes 7650 4550 0    50   ~ 0
Vadap
Text Notes 4650 6450 0    50   ~ 0
Battery level
Text Notes 10700 3500 0    50   ~ 0
Connector
$Comp
L Connector:Barrel_Jack J6
U 1 1 5DB1010E
P 8300 5500
F 0 "J6" H 8355 5825 50  0000 C CNN
F 1 "Barrel_Jack" H 8355 5734 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Wuerth_6941xx301002" H 8350 5460 50  0001 C CNN
F 3 "~" H 8350 5460 50  0001 C CNN
	1    8300 5500
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AZ1117-3.3 U1
U 1 1 5DB235F9
P 1600 1250
F 0 "U1" H 1600 1492 50  0000 C CNN
F 1 "AZ1117-3.3" H 1600 1401 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 1600 1500 50  0001 C CIN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117.pdf" H 1600 1250 50  0001 C CNN
	1    1600 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5DB23C5C
P 2650 1500
F 0 "C3" H 2742 1546 50  0000 L CNN
F 1 "1uF" H 2742 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2650 1500 50  0001 C CNN
F 3 "~" H 2650 1500 50  0001 C CNN
	1    2650 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5DB23D66
P 700 1500
F 0 "C2" H 792 1546 50  0000 L CNN
F 1 "1uF" H 792 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 700 1500 50  0001 C CNN
F 3 "~" H 700 1500 50  0001 C CNN
	1    700  1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1250 700  1400
$Comp
L power:GND #PWR02
U 1 1 5DB3A83E
P 1600 1900
F 0 "#PWR02" H 1600 1650 50  0001 C CNN
F 1 "GND" H 1605 1727 50  0000 C CNN
F 2 "" H 1600 1900 50  0001 C CNN
F 3 "" H 1600 1900 50  0001 C CNN
	1    1600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1600 700  1750
Wire Wire Line
	700  1750 1100 1750
Wire Wire Line
	1600 1750 1600 1900
Wire Wire Line
	1600 1750 1600 1550
Connection ~ 1600 1750
Wire Wire Line
	2650 1750 2650 1600
$Comp
L power:VBUS #PWR021
U 1 1 5DB5CBEC
P 8750 5100
F 0 "#PWR021" H 8750 4950 50  0001 C CNN
F 1 "VBUS" H 8765 5273 50  0000 C CNN
F 2 "" H 8750 5100 50  0001 C CNN
F 3 "" H 8750 5100 50  0001 C CNN
	1    8750 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5400 8750 5400
Wire Wire Line
	8750 5400 8750 5100
$Comp
L power:GND #PWR022
U 1 1 5DB6143D
P 8800 5800
F 0 "#PWR022" H 8800 5550 50  0001 C CNN
F 1 "GND" H 8805 5627 50  0000 C CNN
F 2 "" H 8800 5800 50  0001 C CNN
F 3 "" H 8800 5800 50  0001 C CNN
	1    8800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5600 8800 5600
Wire Wire Line
	8800 5600 8800 5800
$Comp
L power:VBUS #PWR01
U 1 1 5DB6AE0E
P 700 1050
F 0 "#PWR01" H 700 900 50  0001 C CNN
F 1 "VBUS" H 715 1223 50  0000 C CNN
F 2 "" H 700 1050 50  0001 C CNN
F 3 "" H 700 1050 50  0001 C CNN
	1    700  1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1050 700  1100
Connection ~ 700  1250
$Comp
L power:+3.3V #PWR05
U 1 1 5DB6FC01
P 3650 6650
F 0 "#PWR05" H 3650 6500 50  0001 C CNN
F 1 "+3.3V" H 3665 6823 50  0000 C CNN
F 2 "" H 3650 6650 50  0001 C CNN
F 3 "" H 3650 6650 50  0001 C CNN
	1    3650 6650
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR012
U 1 1 5DB9352D
P 4600 900
F 0 "#PWR012" H 4600 750 50  0001 C CNN
F 1 "+BATT" H 4615 1073 50  0000 C CNN
F 2 "" H 4600 900 50  0001 C CNN
F 3 "" H 4600 900 50  0001 C CNN
	1    4600 900 
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DB989DA
P 4600 1000
F 0 "#FLG01" H 4600 1075 50  0001 C CNN
F 1 "PWR_FLAG" V 4600 1128 50  0000 L CNN
F 2 "" H 4600 1000 50  0001 C CNN
F 3 "~" H 4600 1000 50  0001 C CNN
	1    4600 1000
	0    1    1    0   
$EndComp
Wire Notes Line
	550  4400 3250 4400
Wire Wire Line
	700  1250 1100 1250
$Comp
L Diode:1N4148W D1
U 1 1 5DBDF50D
P 1100 1500
F 0 "D1" V 1054 1580 50  0000 L CNN
F 1 "1N4148W" V 1145 1580 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 1100 1325 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 1100 1500 50  0001 C CNN
	1    1100 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 1250 1100 1350
Connection ~ 1100 1250
Wire Wire Line
	1100 1250 1300 1250
Wire Wire Line
	1100 1650 1100 1750
Connection ~ 1100 1750
Wire Wire Line
	1100 1750 1600 1750
$Comp
L Regulator_Switching:MCP1640BCH U6
U 1 1 5DBF565C
P 4300 3100
F 0 "U6" H 4300 3567 50  0000 C CNN
F 1 "MCP1640BCH" H 4300 3476 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 4350 2850 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002234D.pdf" H 4050 3550 50  0001 C CNN
	1    4300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR015
U 1 1 5DBFB38D
P 3500 2700
F 0 "#PWR015" H 3500 2550 50  0001 C CNN
F 1 "+BATT" H 3515 2873 50  0000 C CNN
F 2 "" H 3500 2700 50  0001 C CNN
F 3 "" H 3500 2700 50  0001 C CNN
	1    3500 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5DC07470
P 4300 3500
F 0 "#PWR020" H 4300 3250 50  0001 C CNN
F 1 "GND" H 4305 3327 50  0000 C CNN
F 2 "" H 4300 3500 50  0001 C CNN
F 3 "" H 4300 3500 50  0001 C CNN
	1    4300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3400 4300 3500
$Comp
L Device:C_Small C4
U 1 1 5DC0D702
P 3500 3150
F 0 "C4" H 3592 3196 50  0000 L CNN
F 1 "1uF" H 3592 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3500 3150 50  0001 C CNN
F 3 "~" H 3500 3150 50  0001 C CNN
	1    3500 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2700 3500 2900
Connection ~ 3500 2900
Wire Wire Line
	3500 2900 3500 3050
$Comp
L power:GND #PWR018
U 1 1 5DC32476
P 3500 3350
F 0 "#PWR018" H 3500 3100 50  0001 C CNN
F 1 "GND" H 3505 3177 50  0000 C CNN
F 2 "" H 3500 3350 50  0001 C CNN
F 3 "" H 3500 3350 50  0001 C CNN
	1    3500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3250 3500 3350
Wire Wire Line
	3500 2900 3700 2900
Wire Wire Line
	3900 3100 3800 3100
Wire Wire Line
	3800 3100 3800 2900
Connection ~ 3800 2900
Wire Wire Line
	3800 2900 3900 2900
$Comp
L Device:R_Small R1
U 1 1 5DC3F11C
P 5200 3150
F 0 "R1" H 5259 3196 50  0000 L CNN
F 1 "976kΩ" H 5259 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5200 3150 50  0001 C CNN
F 3 "~" H 5200 3150 50  0001 C CNN
	1    5200 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Small L1
U 1 1 5DC3F593
P 4300 2500
F 0 "L1" V 4485 2500 50  0000 C CNN
F 1 "4.7uH" V 4394 2500 50  0000 C CNN
F 2 "Inductor_SMD:L_Coilcraft_XxL4040" H 4300 2500 50  0001 C CNN
F 3 "~" H 4300 2500 50  0001 C CNN
	1    4300 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 2900 4800 2900
Wire Wire Line
	4800 2900 4800 2500
Wire Wire Line
	4800 2500 4400 2500
Wire Wire Line
	3700 2900 3700 2500
Wire Wire Line
	3700 2500 4200 2500
Connection ~ 3700 2900
Wire Wire Line
	3700 2900 3800 2900
$Comp
L Device:R_Small R2
U 1 1 5DC4D473
P 5200 3550
F 0 "R2" H 5259 3596 50  0000 L CNN
F 1 "562kΩ" H 5259 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5200 3550 50  0001 C CNN
F 3 "~" H 5200 3550 50  0001 C CNN
	1    5200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3000 5200 3050
Wire Wire Line
	4700 3200 4800 3200
Wire Wire Line
	4800 3200 4800 3350
Wire Wire Line
	5200 3350 5200 3250
Wire Wire Line
	5200 3350 5200 3450
Connection ~ 5200 3350
$Comp
L power:GND #PWR029
U 1 1 5DC70879
P 5200 3700
F 0 "#PWR029" H 5200 3450 50  0001 C CNN
F 1 "GND" H 5205 3527 50  0000 C CNN
F 2 "" H 5200 3700 50  0001 C CNN
F 3 "" H 5200 3700 50  0001 C CNN
	1    5200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3650 5200 3700
Wire Wire Line
	5200 3000 5750 3000
Wire Wire Line
	5750 3000 5750 2800
Connection ~ 5200 3000
$Comp
L Device:C_Small C5
U 1 1 5DC8EBD0
P 5750 3300
F 0 "C5" H 5842 3346 50  0000 L CNN
F 1 "10uF" H 5842 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5750 3300 50  0001 C CNN
F 3 "~" H 5750 3300 50  0001 C CNN
	1    5750 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3000 5750 3200
Connection ~ 5750 3000
$Comp
L power:GND #PWR035
U 1 1 5DCE3210
P 5750 3550
F 0 "#PWR035" H 5750 3300 50  0001 C CNN
F 1 "GND" H 5755 3377 50  0000 C CNN
F 2 "" H 5750 3550 50  0001 C CNN
F 3 "" H 5750 3550 50  0001 C CNN
	1    5750 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3400 5750 3550
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5DCF3194
P 700 1100
F 0 "#FLG02" H 700 1175 50  0001 C CNN
F 1 "PWR_FLAG" V 700 1228 50  0000 L CNN
F 2 "" H 700 1100 50  0001 C CNN
F 3 "~" H 700 1100 50  0001 C CNN
	1    700  1100
	0    1    1    0   
$EndComp
Connection ~ 700  1100
Wire Wire Line
	700  1100 700  1250
Wire Wire Line
	1600 1750 2100 1750
Wire Wire Line
	2650 1050 2650 1250
Connection ~ 2650 1250
Wire Wire Line
	2650 1250 2650 1400
Wire Wire Line
	4800 3350 5200 3350
Wire Wire Line
	1900 1250 2100 1250
Wire Wire Line
	4700 3000 5200 3000
Text GLabel 5750 2800 1    50   Input ~ 0
SMPS_out
Text GLabel 2800 1050 2    50   Input ~ 0
LDO_out
Wire Wire Line
	2650 1050 2800 1050
Text GLabel 3350 7300 3    50   Input ~ 0
LDO_out
Text GLabel 3950 7250 3    50   Input ~ 0
SMPS_out
$Comp
L Device:D_Schottky D2
U 1 1 5DDBE2BA
P 3350 7050
F 0 "D2" V 3304 7129 50  0000 L CNN
F 1 "MBR230" V 3395 7129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" H 3350 7050 50  0001 C CNN
F 3 "~" H 3350 7050 50  0001 C CNN
	1    3350 7050
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky D3
U 1 1 5DDBE39F
P 3950 7050
F 0 "D3" V 3904 7129 50  0000 L CNN
F 1 "MBR230" V 3995 7129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" H 3950 7050 50  0001 C CNN
F 3 "~" H 3950 7050 50  0001 C CNN
	1    3950 7050
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 7200 3950 7250
Wire Wire Line
	3350 7200 3350 7300
Wire Wire Line
	3350 6900 3350 6800
Wire Wire Line
	3350 6800 3650 6800
Wire Wire Line
	3950 6800 3950 6900
Wire Wire Line
	3650 6650 3650 6700
Connection ~ 3650 6800
Wire Wire Line
	3650 6800 3950 6800
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DDF788A
P 3650 6700
F 0 "#FLG0101" H 3650 6775 50  0001 C CNN
F 1 "PWR_FLAG" V 3650 6828 50  0000 L CNN
F 2 "" H 3650 6700 50  0001 C CNN
F 3 "~" H 3650 6700 50  0001 C CNN
	1    3650 6700
	0    1    1    0   
$EndComp
Connection ~ 3650 6700
Wire Wire Line
	3650 6700 3650 6800
Text Notes 5300 700  0    50   ~ 0
Power management
$Comp
L Transistor_FET:MMBF170 Q4
U 1 1 5DE3E516
P 3850 5900
F 0 "Q4" H 4055 5946 50  0000 L CNN
F 1 "MMBF170" H 4055 5855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4050 5825 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/ds30104.pdf" H 3850 5900 50  0001 L CNN
	1    3850 5900
	-1   0    0    -1  
$EndComp
Text GLabel 8600 2450 0    50   Input ~ 0
XB_SLEEP
Text GLabel 7450 3700 2    50   Input ~ 0
XB_SLEEP
$Comp
L Diode:1N4148W D4
U 1 1 5DE732A9
P 2100 1500
F 0 "D4" V 2054 1580 50  0000 L CNN
F 1 "1N4148W" V 2145 1580 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 2100 1325 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2100 1500 50  0001 C CNN
	1    2100 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 1250 2100 1350
Connection ~ 2100 1250
Wire Wire Line
	2100 1250 2650 1250
Wire Wire Line
	2100 1650 2100 1750
Connection ~ 2100 1750
Wire Wire Line
	2100 1750 2650 1750
$Comp
L Device:Battery_Cell BT1
U 1 1 5DE8F08E
P 4800 1900
F 0 "BT1" H 4918 1996 50  0000 L CNN
F 1 "Battery_Cell" H 4918 1905 50  0000 L CNN
F 2 "BatteryPack:2460" V 4800 1960 50  0001 C CNN
F 3 "~" V 4800 1960 50  0001 C CNN
	1    4800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5DE8F2A7
P 4800 2100
F 0 "#PWR011" H 4800 1850 50  0001 C CNN
F 1 "GND" H 4950 2050 50  0000 C CNN
F 2 "" H 4800 2100 50  0001 C CNN
F 3 "" H 4800 2100 50  0001 C CNN
	1    4800 2100
	1    0    0    -1  
$EndComp
$Comp
L MOSFET-P:MOSFET-P U3
U 1 1 5DE986FB
P 4600 1350
F 0 "U3" H 4693 1380 30  0000 L CNN
F 1 "DMG2301l" H 4693 1320 30  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4600 1300 60  0001 C CNN
F 3 "" H 4600 1300 60  0000 C CNN
	1    4600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1550 4600 1650
$Comp
L Device:R_Small R3
U 1 1 5DEA2128
P 4250 1350
F 0 "R3" V 4050 1350 50  0000 L CNN
F 1 "4.7kΩ" V 4150 1250 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4250 1350 50  0001 C CNN
F 3 "~" H 4250 1350 50  0001 C CNN
	1    4250 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 1350 4400 1350
Wire Wire Line
	4050 1350 4150 1350
Text GLabel 4050 1350 0    50   Input ~ 0
LDO_out
Wire Wire Line
	4600 1000 4600 1150
Connection ~ 4600 1000
Wire Wire Line
	4600 900  4600 1000
$Comp
L power:+3.3V #PWR014
U 1 1 5DBDC301
P 9750 3850
F 0 "#PWR014" H 9750 3700 50  0001 C CNN
F 1 "+3.3V" H 9765 4023 50  0000 C CNN
F 2 "" H 9750 3850 50  0001 C CNN
F 3 "" H 9750 3850 50  0001 C CNN
	1    9750 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 3850 9750 3950
Wire Wire Line
	9750 3950 9900 3950
$Comp
L power:GND #PWR032
U 1 1 5DBE5A44
P 9750 5150
F 0 "#PWR032" H 9750 4900 50  0001 C CNN
F 1 "GND" H 9755 4977 50  0000 C CNN
F 2 "" H 9750 5150 50  0001 C CNN
F 3 "" H 9750 5150 50  0001 C CNN
	1    9750 5150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Female J1
U 1 1 5DC022DA
P 10100 4250
F 0 "J1" H 10127 4276 50  0000 L CNN
F 1 "ÉXTENSION HEADER" H 10127 4185 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 10100 4250 50  0001 C CNN
F 3 "~" H 10100 4250 50  0001 C CNN
	1    10100 4250
	1    0    0    -1  
$EndComp
Text GLabel 9850 4450 0    50   Input ~ 0
RESET
Wire Wire Line
	9850 4450 9900 4450
Text GLabel 9850 4350 0    50   Input ~ 0
SDA
Wire Wire Line
	9850 4350 9900 4350
Text GLabel 9850 4250 0    50   Input ~ 0
SCL
Wire Wire Line
	9850 4250 9900 4250
Text GLabel 7450 2300 2    50   Input ~ 0
ADC1
Text GLabel 9850 4150 0    50   Input ~ 0
ADC1
Text GLabel 7450 1300 2    50   Input ~ 0
IO1
Text GLabel 9850 4050 0    50   Input ~ 0
IO1
Wire Wire Line
	9850 4150 9900 4150
Wire Wire Line
	9850 4050 9900 4050
$Comp
L Transistor_FET:MMBF170 Q5
U 1 1 5DC7810E
P 9850 4850
F 0 "Q5" H 9550 4800 50  0000 L CNN
F 1 "MMBF170" H 9400 4700 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10050 4775 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/ds30104.pdf" H 9850 4850 50  0001 L CNN
	1    9850 4850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9900 4550 9750 4550
Wire Wire Line
	9750 4550 9750 4650
Wire Wire Line
	9750 5050 9750 5150
Text GLabel 7450 2400 2    50   Input ~ 0
EXT_ENABLE
Text GLabel 10150 4850 2    50   Input ~ 0
EXT_ENABLE
Wire Wire Line
	10050 4850 10150 4850
$Comp
L Device:Battery_Cell BT2
U 1 1 5DCD1A3A
P 4350 1900
F 0 "BT2" H 4050 2000 50  0000 L CNN
F 1 "Battery_Cell" H 3850 1900 50  0000 L CNN
F 2 "BatteryPack:2460" V 4350 1960 50  0001 C CNN
F 3 "~" V 4350 1960 50  0001 C CNN
	1    4350 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1700 4350 1650
Wire Wire Line
	4350 1650 4600 1650
Wire Wire Line
	4600 1650 4800 1650
Wire Wire Line
	4800 1650 4800 1700
Connection ~ 4600 1650
Wire Wire Line
	4800 2000 4800 2100
$Comp
L power:GND #PWR036
U 1 1 5DD0DA0E
P 4350 2100
F 0 "#PWR036" H 4350 1850 50  0001 C CNN
F 1 "GND" H 4200 2050 50  0000 C CNN
F 2 "" H 4350 2100 50  0001 C CNN
F 3 "" H 4350 2100 50  0001 C CNN
	1    4350 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2000 4350 2100
$Comp
L Device:Battery_Cell BT3
U 1 1 5DD19F34
P 5450 1900
F 0 "BT3" H 5568 1996 50  0000 L CNN
F 1 "Battery_Cell" H 5568 1905 50  0000 L CNN
F 2 "BatteryPack:2460" V 5450 1960 50  0001 C CNN
F 3 "~" V 5450 1960 50  0001 C CNN
	1    5450 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 5DD19FC8
P 5450 2100
F 0 "#PWR043" H 5450 1850 50  0001 C CNN
F 1 "GND" H 5600 2050 50  0000 C CNN
F 2 "" H 5450 2100 50  0001 C CNN
F 3 "" H 5450 2100 50  0001 C CNN
	1    5450 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2000 5450 2100
Wire Wire Line
	4800 1650 5450 1650
Wire Wire Line
	5450 1650 5450 1700
Connection ~ 4800 1650
$Comp
L VEML7700-TT:VEML7700-TT IC3
U 1 1 5DC4A7F3
P 1800 6750
F 0 "IC3" H 2225 7015 50  0000 C CNN
F 1 "VEML7700-TT" H 2225 6924 50  0000 C CNN
F 2 "VEML7700:VEML7700" H 2650 6850 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/veml7700-tt/vishay" H 2650 6750 50  0001 L CNN
F 4 "16Bit Ambient Light Sensor I2C 6.8x2.3mm" H 2650 6650 50  0001 L CNN "Description"
F 5 "" H 2650 6550 50  0001 L CNN "Height"
F 6 "Vishay" H 2650 6450 50  0001 L CNN "Manufacturer_Name"
F 7 "VEML7700-TT" H 2650 6350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "78-VEML7700-TT" H 2650 6250 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=78-VEML7700-TT" H 2650 6150 50  0001 L CNN "Mouser Price/Stock"
F 10 "1226791P" H 2650 6050 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/1226791P" H 2650 5950 50  0001 L CNN "RS Price/Stock"
	1    1800 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5DC6B6E1
P 1500 6750
F 0 "C8" H 1592 6796 50  0000 L CNN
F 1 "100nF" H 1592 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1500 6750 50  0001 C CNN
F 3 "~" H 1500 6750 50  0001 C CNN
	1    1500 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5DC76B3E
P 1200 6750
F 0 "C7" H 1292 6796 50  0000 L CNN
F 1 "1uF" H 1292 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1200 6750 50  0001 C CNN
F 3 "~" H 1200 6750 50  0001 C CNN
	1    1200 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6750 1700 6750
Wire Wire Line
	1700 6750 1700 6650
Wire Wire Line
	1700 6650 1500 6650
Connection ~ 1500 6650
Wire Wire Line
	1500 6650 1400 6650
Wire Wire Line
	1400 6650 1400 6300
Connection ~ 1400 6650
Wire Wire Line
	1400 6650 1200 6650
$Comp
L power:+3.3V #PWR08
U 1 1 5DCA2F91
P 1400 6300
F 0 "#PWR08" H 1400 6150 50  0001 C CNN
F 1 "+3.3V" H 1550 6350 50  0000 C CNN
F 2 "" H 1400 6300 50  0001 C CNN
F 3 "" H 1400 6300 50  0001 C CNN
	1    1400 6300
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:MMBF170 Q3
U 1 1 5DCAE8F2
P 1850 7200
F 0 "Q3" H 1600 7400 50  0000 L CNN
F 1 "MMBF170" H 1450 7300 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2050 7125 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/ds30104.pdf" H 1850 7200 50  0001 L CNN
	1    1850 7200
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5DCBA069
P 1750 7500
F 0 "#PWR09" H 1750 7250 50  0001 C CNN
F 1 "GND" H 1900 7400 50  0000 C CNN
F 2 "" H 1750 7500 50  0001 C CNN
F 3 "" H 1750 7500 50  0001 C CNN
	1    1750 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6850 1750 6850
Wire Wire Line
	1750 6850 1750 6950
$Comp
L power:GND #PWR06
U 1 1 5DCD1827
P 1350 7050
F 0 "#PWR06" H 1350 6800 50  0001 C CNN
F 1 "GND" H 1500 6950 50  0000 C CNN
F 2 "" H 1350 7050 50  0001 C CNN
F 3 "" H 1350 7050 50  0001 C CNN
	1    1350 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 6850 1200 6950
Wire Wire Line
	1200 6950 1350 6950
Wire Wire Line
	1350 6950 1350 7050
Wire Wire Line
	1350 6950 1500 6950
Wire Wire Line
	1500 6950 1500 6850
Connection ~ 1350 6950
Text GLabel 2650 6750 2    50   Input ~ 0
SCL
Text GLabel 2650 6850 2    50   Input ~ 0
SDA
Text GLabel 2050 7200 2    50   BiDi ~ 0
APDS_IO9
$Comp
L SHT31-DIS-B:SHT31-DIS-B IC2
U 1 1 5DCF790C
P 850 2950
F 0 "IC2" H 1550 3215 50  0000 C CNN
F 1 "SHT31-DIS-B" H 1550 3124 50  0000 C CNN
F 2 "SHT31-DIS-B:SON50P250X250X90-9N-D" H 2100 3050 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/SHT31-DIS-B.pdf" H 2100 2950 50  0001 L CNN
F 4 "Temperature Humidity Sensor Digital DFN6 Sensirion SHT31-DIS-B Temperature & Humidity Sensor 8-Pin DFN, -40  +125 C" H 2100 2850 50  0001 L CNN "Description"
F 5 "0.9" H 2100 2750 50  0001 L CNN "Height"
F 6 "403-SHT31-DIS-B" H 2100 2650 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=403-SHT31-DIS-B" H 2100 2550 50  0001 L CNN "Mouser Price/Stock"
F 8 "Sensirion" H 2100 2450 50  0001 L CNN "Manufacturer_Name"
F 9 "SHT31-DIS-B" H 2100 2350 50  0001 L CNN "Manufacturer_Part_Number"
	1    850  2950
	1    0    0    -1  
$EndComp
NoConn ~ 850  3150
Wire Wire Line
	850  3050 600  3050
Wire Wire Line
	600  3050 600  3600
Wire Wire Line
	600  3600 800  3600
Wire Wire Line
	1350 3600 1350 3550
Wire Wire Line
	1850 3250 1900 3250
Wire Wire Line
	1900 3250 1900 3600
Wire Wire Line
	1900 3600 1350 3600
Connection ~ 1350 3600
$Comp
L Transistor_FET:MMBF170 Q2
U 1 1 5DD36296
P 1450 3900
F 0 "Q2" H 1200 4100 50  0000 L CNN
F 1 "MMBF170" H 1050 4000 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1650 3825 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/ds30104.pdf" H 1450 3900 50  0001 L CNN
	1    1450 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 3600 1350 3700
Text GLabel 1650 3900 2    50   BiDi ~ 0
SHT31_IO6
$Comp
L power:GND #PWR03
U 1 1 5DD4384D
P 1350 4200
F 0 "#PWR03" H 1350 3950 50  0001 C CNN
F 1 "GND" H 1500 4100 50  0000 C CNN
F 2 "" H 1350 4200 50  0001 C CNN
F 3 "" H 1350 4200 50  0001 C CNN
	1    1350 4200
	1    0    0    -1  
$EndComp
Text GLabel 850  3250 0    50   Input ~ 0
SCL
Text GLabel 850  2950 0    50   Input ~ 0
SDA
Text GLabel 1850 3150 2    50   Input ~ 0
RESET
Wire Wire Line
	1850 3050 2200 3050
Wire Wire Line
	2200 3050 2200 3600
Wire Wire Line
	2200 3600 1900 3600
Connection ~ 1900 3600
Wire Wire Line
	1850 2950 2000 2950
$Comp
L MCU_Microchip_ATmega:ATmega328P-AU U4
U 1 1 5DDFE813
P 6850 2500
F 0 "U4" H 6850 914 50  0000 C CNN
F 1 "ATmega328P-AU" H 6850 823 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 6850 2500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 6850 2500 50  0001 C CNN
	1    6850 2500
	1    0    0    -1  
$EndComp
NoConn ~ 6250 1500
NoConn ~ 6250 1600
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DE33F84
P 1750 6950
F 0 "#FLG0103" H 1750 7025 50  0001 C CNN
F 1 "PWR_FLAG" V 1750 7078 50  0000 L CNN
F 2 "" H 1750 6950 50  0001 C CNN
F 3 "~" H 1750 6950 50  0001 C CNN
	1    1750 6950
	0    1    1    0   
$EndComp
Connection ~ 1750 6950
Wire Wire Line
	1750 6950 1750 7000
Wire Wire Line
	1750 7400 1750 7500
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5DE5C241
P 3750 6150
F 0 "#FLG0104" H 3750 6225 50  0001 C CNN
F 1 "PWR_FLAG" V 3750 6278 50  0000 L CNN
F 2 "" H 3750 6150 50  0001 C CNN
F 3 "~" H 3750 6150 50  0001 C CNN
	1    3750 6150
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0106
U 1 1 5DE5C758
P 800 3600
F 0 "#FLG0106" H 800 3675 50  0001 C CNN
F 1 "PWR_FLAG" H 800 3773 50  0000 C CNN
F 2 "" H 800 3600 50  0001 C CNN
F 3 "~" H 800 3600 50  0001 C CNN
	1    800  3600
	-1   0    0    1   
$EndComp
Connection ~ 800  3600
Wire Wire Line
	800  3600 1350 3600
Wire Wire Line
	1350 4100 1350 4200
$Comp
L Device:C_Small C11
U 1 1 5DC61214
P 2150 2700
F 0 "C11" H 2242 2746 50  0000 L CNN
F 1 "100nF" H 2242 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2150 2700 50  0001 C CNN
F 3 "~" H 2150 2700 50  0001 C CNN
	1    2150 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR039
U 1 1 5DDAED80
P 2000 2400
F 0 "#PWR039" H 2000 2250 50  0001 C CNN
F 1 "+3.3V" H 2015 2573 50  0000 C CNN
F 2 "" H 2000 2400 50  0001 C CNN
F 3 "" H 2000 2400 50  0001 C CNN
	1    2000 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2550 2150 2550
Wire Wire Line
	2150 2550 2150 2600
Wire Wire Line
	2000 2550 2000 2950
Wire Wire Line
	2000 2400 2000 2550
Connection ~ 2000 2550
$Comp
L power:GND #PWR045
U 1 1 5DC7D2D5
P 2150 2850
F 0 "#PWR045" H 2150 2600 50  0001 C CNN
F 1 "GND" H 2300 2750 50  0000 C CNN
F 2 "" H 2150 2850 50  0001 C CNN
F 3 "" H 2150 2850 50  0001 C CNN
	1    2150 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2800 2150 2850
Wire Wire Line
	3750 5650 3750 5700
Connection ~ 3750 6150
Wire Wire Line
	3750 6150 3750 6200
Wire Notes Line
	3250 6350 5200 6350
Wire Notes Line
	4400 6350 4400 7700
Wire Notes Line
	550  2150 3250 2150
Wire Notes Line
	3250 2150 3250 7700
$EndSCHEMATC
