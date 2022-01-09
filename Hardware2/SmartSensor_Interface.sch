EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x12 J?
U 1 1 60156A74
P 5050 2550
AR Path="/60156A74" Ref="J?"  Part="1" 
AR Path="/5F76931A/60156A74" Ref="J?"  Part="1" 
AR Path="/5F375837/60156A74" Ref="J10"  Part="1" 
F 0 "J10" H 5150 1950 50  0000 L CNN
F 1 "PANTS_1" V 5150 2100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 5050 2550 50  0001 C CNN
F 3 "~" H 5050 2550 50  0001 C CNN
	1    5050 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J?
U 1 1 60156A80
P 6250 2550
AR Path="/60156A80" Ref="J?"  Part="1" 
AR Path="/5F76931A/60156A80" Ref="J?"  Part="1" 
AR Path="/5F375837/60156A80" Ref="J11"  Part="1" 
F 0 "J11" H 6350 1950 50  0000 L CNN
F 1 "PANTS_3" V 6350 2100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 6250 2550 50  0001 C CNN
F 3 "~" H 6250 2550 50  0001 C CNN
	1    6250 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J?
U 1 1 60156A86
P 6250 4400
AR Path="/60156A86" Ref="J?"  Part="1" 
AR Path="/5F76931A/60156A86" Ref="J?"  Part="1" 
AR Path="/5F375837/60156A86" Ref="J12"  Part="1" 
F 0 "J12" H 6350 3800 50  0000 L CNN
F 1 "PANTS_4" V 6350 3950 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 6250 4400 50  0001 C CNN
F 3 "~" H 6250 4400 50  0001 C CNN
	1    6250 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60156A9A
P 4600 3150
AR Path="/60156A9A" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/60156A9A" Ref="#PWR?"  Part="1" 
AR Path="/5F375837/60156A9A" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 4600 2900 50  0001 C CNN
F 1 "GND" H 4605 2977 50  0000 C CNN
F 2 "" H 4600 3150 50  0001 C CNN
F 3 "" H 4600 3150 50  0001 C CNN
	1    4600 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60156AB8
P 5850 5000
AR Path="/60156AB8" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/60156AB8" Ref="#PWR?"  Part="1" 
AR Path="/5F375837/60156AB8" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 5850 4750 50  0001 C CNN
F 1 "GND" H 5855 4827 50  0000 C CNN
F 2 "" H 5850 5000 50  0001 C CNN
F 3 "" H 5850 5000 50  0001 C CNN
	1    5850 5000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60156ABE
P 5800 3900
AR Path="/60156ABE" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/60156ABE" Ref="#PWR?"  Part="1" 
AR Path="/5F375837/60156ABE" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 5800 3750 50  0001 C CNN
F 1 "+3.3V" H 5815 4073 50  0000 C CNN
F 2 "" H 5800 3900 50  0001 C CNN
F 3 "" H 5800 3900 50  0001 C CNN
	1    5800 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 5000 5950 5000
$Comp
L power:GND #PWR?
U 1 1 60156AD7
P 5850 3150
AR Path="/60156AD7" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/60156AD7" Ref="#PWR?"  Part="1" 
AR Path="/5F375837/60156AD7" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 5850 2900 50  0001 C CNN
F 1 "GND" H 5855 2977 50  0000 C CNN
F 2 "" H 5850 3150 50  0001 C CNN
F 3 "" H 5850 3150 50  0001 C CNN
	1    5850 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60156ADD
P 5800 2050
AR Path="/60156ADD" Ref="#PWR?"  Part="1" 
AR Path="/5F76931A/60156ADD" Ref="#PWR?"  Part="1" 
AR Path="/5F375837/60156ADD" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 5800 1900 50  0001 C CNN
F 1 "+3.3V" H 5815 2223 50  0000 C CNN
F 2 "" H 5800 2050 50  0001 C CNN
F 3 "" H 5800 2050 50  0001 C CNN
	1    5800 2050
	1    0    0    -1  
$EndComp
Text HLabel 4650 2050 0    50   UnSpc ~ 0
V_BAT
Text HLabel 4650 2250 0    50   UnSpc ~ 0
V_IN
Text HLabel 4750 2450 0    50   Input ~ 0
ADAPTER_IN_USE
Text HLabel 5950 2550 0    50   Input ~ 0
RESET
Text HLabel 5950 2250 0    50   Input ~ 0
ATM_TX0
Text HLabel 5950 2350 0    50   Output ~ 0
ATM_RX0
Text HLabel 5900 4000 0    50   3State ~ 0
ATM_PA0
Text HLabel 5900 4100 0    50   3State ~ 0
ATM_PA1
Text HLabel 5900 4200 0    50   3State ~ 0
ATM_PA2
Text HLabel 4750 2550 0    50   Input ~ 0
ATM_MOSI_1_TXD_2
Text HLabel 4750 2650 0    50   Output ~ 0
ATM_MISO_1_RXD_2
Text HLabel 4750 2750 0    50   Input ~ 0
ATM_SCK_1
Text HLabel 4750 2850 0    50   BiDi ~ 0
SDA
Text HLabel 4750 2950 0    50   Input ~ 0
SCL
Text HLabel 5900 4500 0    50   UnSpc ~ 0
XBEE_AD1
Text HLabel 5900 4400 0    50   UnSpc ~ 0
XBEE_VREF
Text HLabel 5900 4800 0    50   Input ~ 0
XBEE_PWM0
Text HLabel 5900 4700 0    50   Input ~ 0
XBEE_PWM1
Text HLabel 5900 4600 0    50   BiDi ~ 0
XBEE_D18
Wire Wire Line
	4650 2050 4750 2050
Wire Wire Line
	4750 2050 4750 2150
Connection ~ 4750 2050
Wire Wire Line
	4750 2050 4850 2050
Wire Wire Line
	4850 2150 4750 2150
Wire Wire Line
	4600 3150 4750 3150
Connection ~ 4750 3150
Wire Wire Line
	4750 3150 4850 3150
Wire Wire Line
	4850 3050 4750 3050
Wire Wire Line
	4750 3050 4750 3150
Wire Wire Line
	5800 2050 5950 2050
Wire Wire Line
	6050 2150 5950 2150
Wire Wire Line
	5950 2150 5950 2050
Connection ~ 5950 2050
Wire Wire Line
	5950 2050 6050 2050
Wire Wire Line
	5950 4900 5950 5000
Wire Wire Line
	5950 4900 6050 4900
Connection ~ 5950 5000
Wire Wire Line
	5950 5000 6050 5000
Wire Wire Line
	4650 2250 4750 2250
Wire Wire Line
	4850 2350 4750 2350
Wire Wire Line
	4750 2350 4750 2250
Connection ~ 4750 2250
Wire Wire Line
	4750 2250 4850 2250
Wire Wire Line
	4750 2450 4850 2450
Wire Wire Line
	4750 2850 4850 2850
Wire Wire Line
	4850 2950 4750 2950
Wire Wire Line
	5950 2850 6050 2850
Wire Wire Line
	6050 2950 5950 2950
Text HLabel 5950 2950 0    50   BiDi ~ 0
ATM_SDA_1
Text HLabel 5950 2850 0    50   Input ~ 0
ATM_SCL_1
Wire Wire Line
	5900 4600 6050 4600
Wire Wire Line
	6050 2650 5950 2650
Wire Wire Line
	5950 2750 6050 2750
Wire Wire Line
	6050 4700 5900 4700
Wire Wire Line
	5900 4800 6050 4800
Text HLabel 5900 4300 0    50   3State ~ 0
ATM_PA3
Wire Wire Line
	5900 4200 6050 4200
Wire Wire Line
	6050 4300 5900 4300
Wire Wire Line
	5800 3900 6050 3900
Wire Wire Line
	5900 4100 6050 4100
Wire Wire Line
	5900 4000 6050 4000
Wire Wire Line
	5950 2250 6050 2250
Wire Wire Line
	6050 2350 5950 2350
Connection ~ 5850 3150
Wire Wire Line
	5850 3150 6050 3150
Wire Wire Line
	6050 3050 5850 3050
Connection ~ 5850 3050
Wire Wire Line
	5850 3050 5850 3150
Wire Wire Line
	4850 2550 4750 2550
Wire Wire Line
	4750 2650 4850 2650
Wire Wire Line
	4850 2750 4750 2750
Wire Wire Line
	6050 4400 5900 4400
Wire Wire Line
	5900 4500 6050 4500
Text HLabel 5950 2750 0    50   Input ~ 0
ATM_PB3
Text HLabel 5950 2650 0    50   Input ~ 0
ATM_PB4
Wire Wire Line
	6050 2450 5850 2450
Wire Wire Line
	5850 2450 5850 3050
Wire Wire Line
	5950 2550 6050 2550
$EndSCHEMATC
