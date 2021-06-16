EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 6
Title "SmartSensor"
Date "2021-06-14"
Rev "1.2"
Comp "Avans Hogeschool"
Comment1 "Maurice Snoeren"
Comment2 "Expertise Centrum Technische Innovatie"
Comment3 "Lectoraat Smart Energy and Datascience & ICT"
Comment4 ""
$EndDescr
Text Notes 7400 4050 0    50   ~ 0
JTAG Interface
Wire Wire Line
	8050 3700 8350 3700
Text GLabel 8350 3700 2    50   Input ~ 0
ATM_RESET
Wire Wire Line
	7500 3900 7550 3900
Wire Wire Line
	7500 3700 7550 3700
Wire Wire Line
	7500 3600 7550 3600
Wire Wire Line
	7500 3500 7550 3500
Text GLabel 7500 3900 0    50   Input ~ 0
ATM_JTAG_TDI
NoConn ~ 8050 3800
Wire Wire Line
	8050 3500 8250 3500
Wire Wire Line
	7550 3800 6750 3800
Wire Wire Line
	8050 3600 8400 3600
$Comp
L power:GND #PWR025
U 1 1 5F7BA471
P 8250 4000
F 0 "#PWR025" H 8250 3750 50  0001 C CNN
F 1 "GND" H 8255 3827 50  0000 C CNN
F 2 "" H 8250 4000 50  0001 C CNN
F 3 "" H 8250 4000 50  0001 C CNN
	1    8250 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR028
U 1 1 5F7BA477
P 8400 3600
F 0 "#PWR028" H 8400 3450 50  0001 C CNN
F 1 "+3.3V" H 8415 3773 50  0000 C CNN
F 2 "" H 8400 3600 50  0001 C CNN
F 3 "" H 8400 3600 50  0001 C CNN
	1    8400 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 5F7BA47D
P 6750 3800
F 0 "#PWR022" H 6750 3650 50  0001 C CNN
F 1 "+3.3V" H 6765 3973 50  0000 C CNN
F 2 "" H 6750 3800 50  0001 C CNN
F 3 "" H 6750 3800 50  0001 C CNN
	1    6750 3800
	1    0    0    -1  
$EndComp
Text GLabel 7500 3700 0    50   Input ~ 0
ATM_JTAG_TMS
Text GLabel 7500 3600 0    50   Input ~ 0
ATM_JTAG_TDO
Text GLabel 7500 3500 0    50   Input ~ 0
ATM_JTAG_TCK
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J5
U 1 1 5F7BA486
P 7750 3700
F 0 "J5" H 7800 4117 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 7800 4026 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical" H 7750 3700 50  0001 C CNN
F 3 "~" H 7750 3700 50  0001 C CNN
	1    7750 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3500 8250 3900
Wire Wire Line
	8050 3900 8250 3900
Connection ~ 8250 3900
Wire Wire Line
	8250 3900 8250 4000
Wire Wire Line
	5850 1550 5550 1550
Wire Wire Line
	5850 1650 5850 1550
Wire Wire Line
	5550 1650 5550 1550
$Comp
L Device:R_Small R?
U 1 1 5F7F7ECF
P 5550 1750
AR Path="/5F7F7ECF" Ref="R?"  Part="1" 
AR Path="/5F76931A/5F7F7ECF" Ref="R8"  Part="1" 
F 0 "R8" H 5609 1796 50  0000 L CNN
F 1 "2.2k" V 5450 1700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5550 1750 50  0001 C CNN
F 3 "~" H 5550 1750 50  0001 C CNN
	1    5550 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F7F7ED5
P 5850 1750
AR Path="/5F7F7ED5" Ref="R?"  Part="1" 
AR Path="/5F76931A/5F7F7ED5" Ref="R10"  Part="1" 
F 0 "R10" H 5909 1796 50  0000 L CNN
F 1 "2.2k" V 5750 1700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5850 1750 50  0001 C CNN
F 3 "~" H 5850 1750 50  0001 C CNN
	1    5850 1750
	1    0    0    -1  
$EndComp
Connection ~ 5550 1550
$Comp
L power:+3.3V #PWR?
U 1 1 5F7F7EDC
P 5550 1550
AR Path="/5F7F7EDC" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F7F7EDC" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 5550 1400 50  0001 C CNN
F 1 "+3.3V" H 5565 1723 50  0000 C CNN
F 2 "" H 5550 1550 50  0001 C CNN
F 3 "" H 5550 1550 50  0001 C CNN
	1    5550 1550
	1    0    0    -1  
$EndComp
$Comp
L Timer:MCP7940N-xSN U?
U 1 1 5F80CA60
P 2550 6100
AR Path="/5F80CA60" Ref="U?"  Part="1" 
AR Path="/5F76931A/5F80CA60" Ref="U3"  Part="1" 
F 0 "U3" H 2300 5750 50  0000 C CNN
F 1 "MCP7940N-xSN" H 2950 5750 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2550 6100 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 2550 6100 50  0001 C CNN
	1    2550 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y?
U 1 1 5F80CA66
P 3150 6000
AR Path="/5F80CA66" Ref="Y?"  Part="1" 
AR Path="/5F76931A/5F80CA66" Ref="Y2"  Part="1" 
F 0 "Y2" H 3150 6268 50  0000 C CNN
F 1 "Crystal" H 3150 6177 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_G8-2Pin_3.2x1.5mm" H 3150 6000 50  0001 C CNN
F 3 "~" H 3150 6000 50  0001 C CNN
	1    3150 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 6000 3000 6000
Wire Wire Line
	2950 6200 3300 6200
Wire Wire Line
	3300 6200 3300 6000
$Comp
L power:+3.3V #PWR?
U 1 1 5F80CA74
P 2550 5350
AR Path="/5F80CA74" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F80CA74" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 2550 5200 50  0001 C CNN
F 1 "+3.3V" H 2565 5523 50  0000 C CNN
F 2 "" H 2550 5350 50  0001 C CNN
F 3 "" H 2550 5350 50  0001 C CNN
	1    2550 5350
	1    0    0    -1  
$EndComp
Text Notes 2850 6650 0    50   ~ 0
Real-Time Clock
$Comp
L power:GND #PWR?
U 1 1 5F80CA81
P 3600 6550
AR Path="/5F80CA81" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F80CA81" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 3600 6300 50  0001 C CNN
F 1 "GND" H 3605 6377 50  0000 C CNN
F 2 "" H 3600 6550 50  0001 C CNN
F 3 "" H 3600 6550 50  0001 C CNN
	1    3600 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F80CA87
P 3900 6100
AR Path="/5F80CA87" Ref="C?"  Part="1" 
AR Path="/5F76931A/5F80CA87" Ref="C14"  Part="1" 
F 0 "C14" H 4000 6000 50  0000 L CNN
F 1 "100nF" H 3950 6200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3900 6100 50  0001 C CNN
F 3 "~" H 3900 6100 50  0001 C CNN
	1    3900 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 5350 2550 5700
Wire Wire Line
	2550 5350 3600 5350
Wire Wire Line
	3900 5350 3900 6000
Connection ~ 2550 5350
Wire Wire Line
	3900 6200 3900 6500
Text GLabel 2000 5900 0    50   Input ~ 0
SCL_MAIN
Text GLabel 2000 6000 0    50   Input ~ 0
SDA_MAIN
Text GLabel 2000 6200 0    50   Input ~ 0
RTC_MFP
$Comp
L Device:R_Small R?
U 1 1 5F85783F
P 5700 2700
AR Path="/5F85783F" Ref="R?"  Part="1" 
AR Path="/5F76931A/5F85783F" Ref="R9"  Part="1" 
F 0 "R9" V 5650 2450 50  0000 L CNN
F 1 "210" V 5600 2650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5700 2700 50  0001 C CNN
F 3 "~" H 5700 2700 50  0001 C CNN
	1    5700 2700
	0    1    1    0   
$EndComp
$Comp
L Device:LED_Small D?
U 1 1 5F857845
P 5950 2700
AR Path="/5F857845" Ref="D?"  Part="1" 
AR Path="/5F76931A/5F857845" Ref="D3"  Part="1" 
F 0 "D3" H 6000 2600 50  0000 C CNN
F 1 "RED" H 5800 2600 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 5950 2700 50  0001 C CNN
F 3 "~" V 5950 2700 50  0001 C CNN
	1    5950 2700
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F85784B
P 5400 2600
AR Path="/5F85784B" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F85784B" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 5400 2450 50  0001 C CNN
F 1 "+3.3V" H 5415 2773 50  0000 C CNN
F 2 "" H 5400 2600 50  0001 C CNN
F 3 "" H 5400 2600 50  0001 C CNN
	1    5400 2600
	1    0    0    -1  
$EndComp
Text GLabel 6100 2700 2    50   Input ~ 0
LED_1
Wire Wire Line
	6050 2700 6100 2700
Wire Wire Line
	5400 2600 5400 2700
Wire Wire Line
	5600 2700 5400 2700
Wire Wire Line
	5850 2700 5800 2700
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J?
U 1 1 5F865D95
P 7800 2600
AR Path="/5F865D95" Ref="J?"  Part="1" 
AR Path="/5F76931A/5F865D95" Ref="J6"  Part="1" 
F 0 "J6" H 7850 3017 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 7850 2926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical" H 7800 2600 50  0001 C CNN
F 3 "~" H 7800 2600 50  0001 C CNN
	1    7800 2600
	1    0    0    -1  
$EndComp
Text GLabel 7550 2400 0    50   Input ~ 0
ATM_MOSI
Text GLabel 7550 2600 0    50   Input ~ 0
ATM_RESET
Text GLabel 7550 2700 0    50   Input ~ 0
ATM_SCK
Text GLabel 7550 2800 0    50   Input ~ 0
ATM_MISO
$Comp
L power:+3.3V #PWR?
U 1 1 5F865D9F
P 8350 2400
AR Path="/5F865D9F" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F865D9F" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 8350 2250 50  0001 C CNN
F 1 "+3.3V" H 8365 2573 50  0000 C CNN
F 2 "" H 8350 2400 50  0001 C CNN
F 3 "" H 8350 2400 50  0001 C CNN
	1    8350 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F865DA5
P 8350 2800
AR Path="/5F865DA5" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F865DA5" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 8350 2550 50  0001 C CNN
F 1 "GND" H 8355 2627 50  0000 C CNN
F 2 "" H 8350 2800 50  0001 C CNN
F 3 "" H 8350 2800 50  0001 C CNN
	1    8350 2800
	1    0    0    -1  
$EndComp
NoConn ~ 7600 2500
Wire Wire Line
	7550 2400 7600 2400
Wire Wire Line
	7550 2600 7600 2600
Wire Wire Line
	7550 2700 7600 2700
Wire Wire Line
	7550 2800 7600 2800
Wire Wire Line
	8100 2400 8350 2400
Wire Wire Line
	8350 2800 8350 2700
Wire Wire Line
	8350 2500 8100 2500
Wire Wire Line
	8100 2600 8350 2600
Connection ~ 8350 2600
Wire Wire Line
	8350 2600 8350 2500
Wire Wire Line
	8100 2700 8350 2700
Connection ~ 8350 2700
Wire Wire Line
	8350 2700 8350 2600
Wire Wire Line
	8100 2800 8350 2800
Connection ~ 8350 2800
Text Notes 7350 3000 0    50   ~ 0
ATMEGA Programming
Text GLabel 7950 1250 2    50   Input ~ 0
ATM_RXD_0
Text GLabel 7950 1150 2    50   Input ~ 0
ATM_TXD_0
Text HLabel 5950 2200 2    50   BiDi ~ 0
SDA
Text HLabel 5950 1950 2    50   Output ~ 0
SCL
Wire Wire Line
	5950 1850 5850 1850
Text GLabel 5950 2100 2    50   Input ~ 0
SDA_MAIN
Text GLabel 5950 1850 2    50   Input ~ 0
SCL_MAIN
Wire Wire Line
	5950 1950 5850 1950
Wire Wire Line
	5850 1950 5850 1850
Connection ~ 5850 1850
Wire Wire Line
	5950 2100 5550 2100
Wire Wire Line
	5550 1850 5550 2100
Wire Wire Line
	5950 2200 5550 2200
Wire Wire Line
	5550 2200 5550 2100
Connection ~ 5550 2100
Text GLabel 5550 5600 2    50   Input ~ 0
ATM_MOSI
Text GLabel 5550 5800 2    50   Input ~ 0
ATM_SCK
Text GLabel 5550 5700 2    50   Input ~ 0
ATM_MISO
Text HLabel 5450 5600 0    50   Output ~ 0
ATM_MOSI
Text HLabel 5450 5700 0    50   Input ~ 0
ATM_MISO
Text HLabel 5450 5800 0    50   Output ~ 0
ATM_CLK
Wire Wire Line
	5450 5800 5550 5800
Wire Wire Line
	5550 5700 5450 5700
Wire Wire Line
	5450 5600 5550 5600
Text GLabel 5550 6000 2    50   Input ~ 0
ATM_RXD_0
Text GLabel 5550 6100 2    50   Input ~ 0
ATM_TXD_0
Text GLabel 5550 6200 2    50   Input ~ 0
ATM_RXD_1
Text GLabel 5550 6300 2    50   Input ~ 0
ATM_TXD_1
Text HLabel 5450 6100 0    50   Output ~ 0
ATM_TXD_0
Text HLabel 5450 6300 0    50   Output ~ 0
ATM_TXD_1
Text HLabel 5450 6000 0    50   Input ~ 0
ATM_RXD_0
Text HLabel 5450 6200 0    50   Input ~ 0
ATM_RXD_1
Wire Wire Line
	5450 6000 5550 6000
Wire Wire Line
	5550 6100 5450 6100
Wire Wire Line
	5450 6200 5550 6200
Wire Wire Line
	5550 6300 5450 6300
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 6025C465
P 7650 1250
AR Path="/5F877B3A/6025C465" Ref="J?"  Part="1" 
AR Path="/5F76931A/6025C465" Ref="J4"  Part="1" 
F 0 "J4" H 7758 1631 50  0000 C CNN
F 1 "Conn_01x06_Male" V 7550 1200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7650 1250 50  0001 C CNN
F 3 "~" H 7650 1250 50  0001 C CNN
	1    7650 1250
	1    0    0    -1  
$EndComp
Text Notes 7650 1700 0    50   ~ 0
FTDI\n
NoConn ~ 7850 1350
$Comp
L power:GND #PWR?
U 1 1 6025C46D
P 8000 1550
AR Path="/5F877B3A/6025C46D" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/6025C46D" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 8000 1300 50  0001 C CNN
F 1 "GND" H 8005 1377 50  0000 C CNN
F 2 "" H 8000 1550 50  0001 C CNN
F 3 "" H 8000 1550 50  0001 C CNN
	1    8000 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1550 8000 1550
NoConn ~ 7850 1050
NoConn ~ 7850 1450
Wire Wire Line
	7850 1150 7950 1150
Wire Wire Line
	7950 1250 7850 1250
$Comp
L Device:CP C18
U 1 1 604E980E
P 3600 6100
F 0 "C18" H 3718 6146 50  0000 L CNN
F 1 "1F" H 3718 6055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D14.0mm_P5.00mm" H 3638 5950 50  0001 C CNN
F 3 "~" H 3600 6100 50  0001 C CNN
	1    3600 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 6500 3600 6500
Wire Wire Line
	3600 6550 3600 6500
Connection ~ 3600 6500
Wire Wire Line
	3600 6500 3900 6500
Wire Wire Line
	3600 6250 3600 6500
$Comp
L Device:D_Small D5
U 1 1 605045D4
P 3600 5550
F 0 "D5" V 3554 5618 50  0000 L CNN
F 1 "D_Small" H 3450 5450 50  0000 L CNN
F 2 "Diode_SMD:D_0805_2012Metric" V 3600 5550 50  0001 C CNN
F 3 "~" V 3600 5550 50  0001 C CNN
	1    3600 5550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 5450 3600 5350
Connection ~ 3600 5350
Wire Wire Line
	3600 5350 3900 5350
Wire Wire Line
	3600 5650 3600 5950
Wire Wire Line
	3600 5650 2650 5650
Wire Wire Line
	2650 5650 2650 5700
Connection ~ 3600 5650
$Comp
L ATECC608B-SSHDA-B:ATECC608B-SSHDA-B IC4
U 1 1 600EB096
P 7400 5350
F 0 "IC4" H 7950 5615 50  0000 C CNN
F 1 "ATECC608B-SSHDA-B" H 7950 5524 50  0000 C CNN
F 2 "ATECC608B-SSHDA-B:SOIC127P600X175-8N" H 8350 5450 50  0001 L CNN
F 3 "https://www.mouser.de/datasheet/2/268/ATECC608B_CryptoAuthentication_Device_Summary_Data-1917867.pdf" H 8350 5350 50  0001 L CNN
F 4 "IC AUTHENTICATION CHIP" H 8350 5250 50  0001 L CNN "Description"
F 5 "1.75" H 8350 5150 50  0001 L CNN "Height"
F 6 "579-TECC608B-SSHDA-B" H 8350 5050 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/ATECC608B-SSHDA-B/?qs=W%2FMpXkg%252BdQ5IvpsOYxIilQ%3D%3D" H 8350 4950 50  0001 L CNN "Mouser Price/Stock"
F 8 "Microchip" H 8350 4850 50  0001 L CNN "Manufacturer_Name"
F 9 "ATECC608B-SSHDA-B" H 8350 4750 50  0001 L CNN "Manufacturer_Part_Number"
	1    7400 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR029
U 1 1 600F7431
P 8500 5000
F 0 "#PWR029" H 8500 4850 50  0001 C CNN
F 1 "+3.3V" H 8515 5173 50  0000 C CNN
F 2 "" H 8500 5000 50  0001 C CNN
F 3 "" H 8500 5000 50  0001 C CNN
	1    8500 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 600F79CE
P 7400 5750
F 0 "#PWR023" H 7400 5500 50  0001 C CNN
F 1 "GND" H 7405 5577 50  0000 C CNN
F 2 "" H 7400 5750 50  0001 C CNN
F 3 "" H 7400 5750 50  0001 C CNN
	1    7400 5750
	1    0    0    -1  
$EndComp
Text GLabel 8600 5550 2    50   Input ~ 0
SCL_MAIN
Text GLabel 8600 5650 2    50   Input ~ 0
SDA_MAIN
$Comp
L Device:C_Small C?
U 1 1 6010ACB9
P 7150 5250
AR Path="/6010ACB9" Ref="C?"  Part="1" 
AR Path="/5F76931A/6010ACB9" Ref="C19"  Part="1" 
F 0 "C19" H 7200 5150 50  0000 L CNN
F 1 "100nF" H 7200 5350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7150 5250 50  0001 C CNN
F 3 "~" H 7150 5250 50  0001 C CNN
	1    7150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5350 7150 5650
Wire Wire Line
	7150 5650 7400 5650
Wire Wire Line
	7400 5750 7400 5650
Connection ~ 7400 5650
Wire Wire Line
	8500 5350 8500 5000
Wire Wire Line
	7150 5150 7150 5000
Wire Wire Line
	7150 5000 8500 5000
Connection ~ 8500 5000
Wire Wire Line
	8500 5550 8600 5550
Wire Wire Line
	8500 5650 8600 5650
Text Notes 7800 5850 0    50   ~ 0
SECURITY
NoConn ~ 7400 5350
NoConn ~ 7400 5450
NoConn ~ 7400 5550
NoConn ~ 8500 5450
$Comp
L SamacSys_Parts:LL3301FF065QJ S1
U 1 1 605C6A6C
P 700 1500
F 0 "S1" H 1300 1765 50  0000 C CNN
F 1 "LL3301FF065QJ" H 1300 1674 50  0000 C CNN
F 2 "SamacSys_Parts:LL3301FF065QJ" H 1750 1600 50  0001 L CNN
F 3 "http://spec_sheets.e-switch.com/specs/P010456.pdf" H 1750 1500 50  0001 L CNN
F 4 "Pushbutton Switches 50mA 12VDC F065 7.0mm J-Lead" H 1750 1400 50  0001 L CNN "Description"
F 5 "7.3" H 1750 1300 50  0001 L CNN "Height"
F 6 "612-LL3301FF065QJ" H 1750 1200 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/E-Switch/LL3301FF065QJ/?qs=QtyuwXswaQgkr0cFSIRaTA%3D%3D" H 1750 1100 50  0001 L CNN "Mouser Price/Stock"
F 8 "E-Switch" H 1750 1000 50  0001 L CNN "Manufacturer_Name"
F 9 "LL3301FF065QJ" H 1750 900 50  0001 L CNN "Manufacturer_Part_Number"
	1    700  1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2700 4000 2700
Wire Wire Line
	4000 2100 3950 2100
Text HLabel 4000 2100 2    50   Input ~ 0
RF_IRQ
Wire Wire Line
	4000 2300 3950 2300
Wire Wire Line
	4000 2400 3950 2400
Wire Wire Line
	2750 4100 2700 4100
Text HLabel 3950 3000 2    50   Output ~ 0
ATM_PB4
Text HLabel 3950 2900 2    50   Output ~ 0
ATM_PB3
Wire Wire Line
	4000 2000 3950 2000
Text HLabel 4000 2000 2    50   3State ~ 0
ATM_PA3
Text Notes 1250 850  0    50   ~ 0
tau = R x C = 10K x 100nF = 0.001 s\ntau = R x C = 100K x 100nF = 0.01 s
Wire Wire Line
	3000 1200 3350 1200
Connection ~ 3000 1200
Wire Wire Line
	3000 1100 3000 1200
Wire Wire Line
	2350 1200 2650 1200
Connection ~ 2350 1200
Wire Wire Line
	2350 1250 2350 1200
Connection ~ 2650 1200
Wire Wire Line
	2050 1200 2350 1200
Wire Wire Line
	2050 1250 2050 1200
Wire Wire Line
	2350 1500 2050 1500
Connection ~ 2350 1500
Wire Wire Line
	2350 1450 2350 1500
Connection ~ 2050 1500
Wire Wire Line
	2050 1450 2050 1500
Connection ~ 2700 1700
Wire Wire Line
	2450 1500 2350 1500
Wire Wire Line
	2450 1700 2450 1500
Wire Wire Line
	2700 1700 2450 1700
$Comp
L Device:C_Small C?
U 1 1 604352B7
P 2050 1600
AR Path="/604352B7" Ref="C?"  Part="1" 
AR Path="/5F76931A/604352B7" Ref="C10"  Part="1" 
F 0 "C10" H 2150 1500 50  0000 L CNN
F 1 "100nF" H 2150 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2050 1600 50  0001 C CNN
F 3 "~" H 2050 1600 50  0001 C CNN
	1    2050 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D2
U 1 1 6042C5C6
P 2050 1350
F 0 "D2" V 2004 1418 50  0000 L CNN
F 1 "D_Small" H 1750 1250 50  0000 L CNN
F 2 "Diode_SMD:D_0805_2012Metric" V 2050 1350 50  0001 C CNN
F 3 "~" V 2050 1350 50  0001 C CNN
	1    2050 1350
	0    1    1    0   
$EndComp
Connection ~ 3350 1200
Wire Wire Line
	2650 1200 3000 1200
Wire Wire Line
	2750 3200 2700 3200
Wire Wire Line
	2700 3100 2750 3100
Text HLabel 2700 3200 0    50   Output ~ 0
ATM_SCL_1
Text HLabel 2700 3100 0    50   BiDi ~ 0
ATM_SDA_1
Wire Wire Line
	2750 2900 2700 2900
Wire Wire Line
	2700 2800 2750 2800
Wire Wire Line
	2750 4200 2700 4200
Text HLabel 2700 4200 0    50   Output ~ 0
ATM_SCK_1
Text HLabel 2700 2900 0    50   Output ~ 0
ATM_MOSI_1_TXD_2
Text HLabel 2700 2800 0    50   Input ~ 0
ATM_MISO_1_RXD_2
Wire Wire Line
	4000 1900 3950 1900
Wire Wire Line
	3950 1800 4000 1800
Wire Wire Line
	4000 1700 3950 1700
Text HLabel 4000 1900 2    50   3State ~ 0
ATM_PA2
Text HLabel 4000 1800 2    50   3State ~ 0
ATM_PA1
Text HLabel 4000 1700 2    50   3State ~ 0
ATM_PA0
Wire Wire Line
	3950 2600 4000 2600
Text HLabel 4000 2700 2    50   Output ~ 0
XBEE_SLEEP
Text HLabel 4000 2600 2    50   Output ~ 0
XBEE_SS
Wire Wire Line
	2700 3700 2750 3700
Wire Wire Line
	2700 3800 2750 3800
Text GLabel 2700 3800 0    50   Input ~ 0
ATM_TXD_1
Text GLabel 2700 3700 0    50   Input ~ 0
ATM_RXD_1
Wire Wire Line
	3950 2800 4000 2800
Connection ~ 2700 1800
Wire Wire Line
	2700 1900 2700 1800
Text GLabel 2700 1900 0    50   Input ~ 0
ATM_RESET
Text HLabel 2700 4100 0    50   Output ~ 0
CO2_WAKE
Text HLabel 4000 2400 2    50   Output ~ 0
CO2_INT
Wire Wire Line
	2700 1700 2750 1700
Wire Wire Line
	2700 1800 2700 1700
Wire Wire Line
	2600 1800 2700 1800
Text HLabel 2600 1800 0    50   Output ~ 0
RESET
Text HLabel 4000 2300 2    50   Input ~ 0
ADAPTER_IN_USE
Wire Wire Line
	2700 3900 2750 3900
Text GLabel 2700 3900 0    50   Input ~ 0
LED_1
Wire Wire Line
	3350 4500 3350 4550
$Comp
L power:GND #PWR?
U 1 1 5F8578DE
P 3350 4550
AR Path="/5F8578DE" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F8578DE" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 3350 4300 50  0001 C CNN
F 1 "GND" H 3355 4377 50  0000 C CNN
F 2 "" H 3350 4550 50  0001 C CNN
F 3 "" H 3350 4550 50  0001 C CNN
	1    3350 4550
	1    0    0    -1  
$EndComp
Text GLabel 4000 2800 2    50   Input ~ 0
RTC_MFP
Text Notes 2300 4550 0    50   ~ 0
Main controller
Wire Wire Line
	2700 3600 2750 3600
Wire Wire Line
	2700 3500 2750 3500
Text GLabel 2700 3600 0    50   Input ~ 0
ATM_TXD_0
Text GLabel 2700 3500 0    50   Input ~ 0
ATM_RXD_0
Wire Wire Line
	4000 4000 3950 4000
Wire Wire Line
	4000 3900 3950 3900
Wire Wire Line
	4000 3800 3950 3800
Wire Wire Line
	4000 3700 3950 3700
Text GLabel 4000 4000 2    50   Input ~ 0
ATM_JTAG_TDI
Text GLabel 4000 3900 2    50   Input ~ 0
ATM_JTAG_TDO
Text GLabel 4000 3800 2    50   Input ~ 0
ATM_JTAG_TMS
Text GLabel 4000 3700 2    50   Input ~ 0
ATM_JTAG_TCK
Wire Wire Line
	4000 3300 3950 3300
Wire Wire Line
	3950 3200 4000 3200
Wire Wire Line
	4000 3100 3950 3100
$Comp
L power:GND #PWR?
U 1 1 5F8578A8
P 1900 1700
AR Path="/5F8578A8" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F8578A8" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 1900 1450 50  0001 C CNN
F 1 "GND" H 1905 1527 50  0000 C CNN
F 2 "" H 1900 1700 50  0001 C CNN
F 3 "" H 1900 1700 50  0001 C CNN
	1    1900 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F857894
P 2350 1350
AR Path="/5F857894" Ref="R?"  Part="1" 
AR Path="/5F76931A/5F857894" Ref="R7"  Part="1" 
F 0 "R7" H 2409 1396 50  0000 L CNN
F 1 "10k" V 2250 1300 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2350 1350 50  0001 C CNN
F 3 "~" H 2350 1350 50  0001 C CNN
	1    2350 1350
	1    0    0    -1  
$EndComp
Text GLabel 4000 3200 2    50   Input ~ 0
ATM_MISO
Text GLabel 4000 3300 2    50   Input ~ 0
ATM_SCK
Text GLabel 4000 3100 2    50   Input ~ 0
ATM_MOSI
Wire Wire Line
	3950 3600 4000 3600
Wire Wire Line
	4000 3500 3950 3500
Wire Wire Line
	2700 3000 2750 3000
Connection ~ 1850 2000
Wire Wire Line
	1550 2700 2750 2700
Wire Wire Line
	1550 2000 1850 2000
Wire Wire Line
	1550 2700 1550 2000
Wire Wire Line
	1850 2000 1950 2000
Connection ~ 2100 2250
Wire Wire Line
	1850 2250 2100 2250
Wire Wire Line
	1850 2200 1850 2250
Wire Wire Line
	2350 2250 2100 2250
Wire Wire Line
	2350 2200 2350 2250
Connection ~ 2350 2000
Wire Wire Line
	2250 2000 2350 2000
Wire Wire Line
	2750 2000 2350 2000
Wire Wire Line
	2750 2600 2750 2000
Wire Wire Line
	2650 1400 2650 1450
Wire Wire Line
	3700 1100 3700 1200
Wire Wire Line
	3750 1100 3700 1100
Wire Wire Line
	3700 1200 4100 1200
Connection ~ 3700 1200
Wire Wire Line
	3700 1500 3700 1200
Wire Wire Line
	3450 1500 3700 1500
Wire Wire Line
	4100 1400 4100 1450
Wire Wire Line
	3550 1200 3700 1200
Wire Wire Line
	3350 1500 3350 1200
$Comp
L SmartSensor-rescue:ATmega324PB-AU-MCU_Microchip_ATmega U?
U 1 1 5F85786B
P 3350 3000
AR Path="/5F85786B" Ref="U?"  Part="1" 
AR Path="/5F76931A/5F85786B" Ref="U4"  Part="1" 
F 0 "U4" H 3050 1500 50  0000 C CNN
F 1 "ATmega324PB-AU" H 3800 1500 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 3350 3000 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001908A.pdf" H 3350 3000 50  0001 C CNN
	1    3350 3000
	1    0    0    -1  
$EndComp
Text GLabel 4000 3600 2    50   Input ~ 0
SDA_MAIN
Text GLabel 4000 3500 2    50   Input ~ 0
SCL_MAIN
$Comp
L power:GND #PWR?
U 1 1 5F857839
P 2650 1450
AR Path="/5F857839" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F857839" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 2650 1200 50  0001 C CNN
F 1 "GND" H 2655 1277 50  0000 C CNN
F 2 "" H 2650 1450 50  0001 C CNN
F 3 "" H 2650 1450 50  0001 C CNN
	1    2650 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F857833
P 4100 1300
AR Path="/5F857833" Ref="C?"  Part="1" 
AR Path="/5F76931A/5F857833" Ref="C13"  Part="1" 
F 0 "C13" H 4200 1200 50  0000 L CNN
F 1 "100nF" H 4200 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4100 1300 50  0001 C CNN
F 3 "~" H 4100 1300 50  0001 C CNN
	1    4100 1300
	1    0    0    -1  
$EndComp
Text GLabel 3750 1100 2    50   Input ~ 0
ATM_AREF
Text GLabel 2700 3000 0    50   Input ~ 0
ATM_AREF
$Comp
L power:GND #PWR?
U 1 1 5F85782B
P 2100 2250
AR Path="/5F85782B" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F85782B" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 2100 2000 50  0001 C CNN
F 1 "GND" H 2105 2077 50  0000 C CNN
F 2 "" H 2100 2250 50  0001 C CNN
F 3 "" H 2100 2250 50  0001 C CNN
	1    2100 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F857825
P 2350 2100
AR Path="/5F857825" Ref="C?"  Part="1" 
AR Path="/5F76931A/5F857825" Ref="C11"  Part="1" 
F 0 "C11" H 2442 2146 50  0000 L CNN
F 1 "22pF" H 2442 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2350 2100 50  0001 C CNN
F 3 "~" H 2350 2100 50  0001 C CNN
	1    2350 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F85781F
P 1850 2100
AR Path="/5F85781F" Ref="C?"  Part="1" 
AR Path="/5F76931A/5F85781F" Ref="C9"  Part="1" 
F 0 "C9" H 1650 2150 50  0000 L CNN
F 1 "22pF" H 1600 2050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1850 2100 50  0001 C CNN
F 3 "~" H 1850 2100 50  0001 C CNN
	1    1850 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y?
U 1 1 5F857819
P 2100 2000
AR Path="/5F857819" Ref="Y?"  Part="1" 
AR Path="/5F76931A/5F857819" Ref="Y1"  Part="1" 
F 0 "Y1" H 1950 2100 50  0000 C CNN
F 1 "20MHz" H 2100 1850 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_Abracon_ABM3-2Pin_5.0x3.2mm" H 2100 2000 50  0001 C CNN
F 3 "~" H 2100 2000 50  0001 C CNN
	1    2100 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F857813
P 4100 1450
AR Path="/5F857813" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F857813" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 4100 1200 50  0001 C CNN
F 1 "GND" H 4105 1277 50  0000 C CNN
F 2 "" H 4100 1450 50  0001 C CNN
F 3 "" H 4100 1450 50  0001 C CNN
	1    4100 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F85780D
P 2650 1300
AR Path="/5F85780D" Ref="C?"  Part="1" 
AR Path="/5F76931A/5F85780D" Ref="C12"  Part="1" 
F 0 "C12" H 2750 1200 50  0000 L CNN
F 1 "100nF" H 2750 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2650 1300 50  0001 C CNN
F 3 "~" H 2650 1300 50  0001 C CNN
	1    2650 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Small L?
U 1 1 5F857807
P 3450 1200
AR Path="/5F857807" Ref="L?"  Part="1" 
AR Path="/5F76931A/5F857807" Ref="L2"  Part="1" 
F 0 "L2" V 3635 1200 50  0000 C CNN
F 1 "4.7uH" V 3544 1200 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3450 1200 50  0001 C CNN
F 3 "~" H 3450 1200 50  0001 C CNN
	1    3450 1200
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F857801
P 3000 1100
AR Path="/5F857801" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/5F857801" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 3000 950 50  0001 C CNN
F 1 "+3.3V" H 3015 1273 50  0000 C CNN
F 2 "" H 3000 1100 50  0001 C CNN
F 3 "" H 3000 1100 50  0001 C CNN
	1    3000 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 1700 1900 1700
Wire Wire Line
	1900 1600 1900 1700
Connection ~ 1900 1700
Wire Wire Line
	1900 1500 2050 1500
Text Notes 1050 1800 0    50   ~ 0
SWITCH RESET
NoConn ~ 700  1500
NoConn ~ 700  1600
$Comp
L SamacSys_Parts:LL3301FF065QJ S3
U 1 1 6062102C
P 5150 3400
F 0 "S3" H 5750 3665 50  0000 C CNN
F 1 "LL3301FF065QJ" H 5750 3574 50  0000 C CNN
F 2 "SamacSys_Parts:LL3301FF065QJ" H 6200 3500 50  0001 L CNN
F 3 "http://spec_sheets.e-switch.com/specs/P010456.pdf" H 6200 3400 50  0001 L CNN
F 4 "Pushbutton Switches 50mA 12VDC F065 7.0mm J-Lead" H 6200 3300 50  0001 L CNN "Description"
F 5 "7.3" H 6200 3200 50  0001 L CNN "Height"
F 6 "612-LL3301FF065QJ" H 6200 3100 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/E-Switch/LL3301FF065QJ/?qs=QtyuwXswaQgkr0cFSIRaTA%3D%3D" H 6200 3000 50  0001 L CNN "Mouser Price/Stock"
F 8 "E-Switch" H 6200 2900 50  0001 L CNN "Manufacturer_Name"
F 9 "LL3301FF065QJ" H 6200 2800 50  0001 L CNN "Manufacturer_Part_Number"
	1    5150 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 60622C55
P 5150 3600
F 0 "#PWR041" H 5150 3350 50  0001 C CNN
F 1 "GND" H 5155 3427 50  0000 C CNN
F 2 "" H 5150 3600 50  0001 C CNN
F 3 "" H 5150 3600 50  0001 C CNN
	1    5150 3600
	1    0    0    -1  
$EndComp
Text HLabel 5050 3400 0    50   Output ~ 0
ATM_PB4
Wire Wire Line
	5050 3400 5150 3400
Wire Wire Line
	5150 3500 5150 3600
Text Notes 5450 3700 0    50   ~ 0
SWITCH GENERAL
Text GLabel 2700 4000 0    50   Input ~ 0
LED_2
Wire Wire Line
	2700 4000 2750 4000
$Comp
L Device:R_Small R?
U 1 1 60C57333
P 5700 2900
AR Path="/60C57333" Ref="R?"  Part="1" 
AR Path="/5F76931A/60C57333" Ref="R4"  Part="1" 
F 0 "R4" V 5650 2650 50  0000 L CNN
F 1 "210" V 5600 2850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5700 2900 50  0001 C CNN
F 3 "~" H 5700 2900 50  0001 C CNN
	1    5700 2900
	0    1    1    0   
$EndComp
$Comp
L Device:LED_Small D?
U 1 1 60C57339
P 5950 2900
AR Path="/60C57339" Ref="D?"  Part="1" 
AR Path="/5F76931A/60C57339" Ref="D6"  Part="1" 
F 0 "D6" H 6000 2800 50  0000 C CNN
F 1 "GREEN" H 5800 2800 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 5950 2900 50  0001 C CNN
F 3 "~" V 5950 2900 50  0001 C CNN
	1    5950 2900
	-1   0    0    1   
$EndComp
Text GLabel 6100 2900 2    50   Input ~ 0
LED_2
Wire Wire Line
	6050 2900 6100 2900
Wire Wire Line
	5600 2900 5400 2900
Wire Wire Line
	5850 2900 5800 2900
Wire Wire Line
	5400 2700 5400 2900
Connection ~ 5400 2700
$Comp
L Device:R_Small R?
U 1 1 60C733DE
P 2100 5550
AR Path="/60C733DE" Ref="R?"  Part="1" 
AR Path="/5F76931A/60C733DE" Ref="R5"  Part="1" 
F 0 "R5" H 2159 5596 50  0000 L CNN
F 1 "100k" V 2000 5500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2100 5550 50  0001 C CNN
F 3 "~" H 2100 5550 50  0001 C CNN
	1    2100 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5900 2150 5900
Wire Wire Line
	2000 6000 2150 6000
Wire Wire Line
	2000 6200 2100 6200
Wire Wire Line
	2100 5650 2100 6200
Connection ~ 2100 6200
Wire Wire Line
	2100 6200 2150 6200
Wire Wire Line
	2100 5450 2100 5350
Wire Wire Line
	2100 5350 2550 5350
NoConn ~ 6350 3400
NoConn ~ 6350 3500
NoConn ~ 3950 4100
NoConn ~ 3950 4200
NoConn ~ 3950 2200
$EndSCHEMATC
