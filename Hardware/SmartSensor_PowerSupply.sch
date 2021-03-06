EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
Title "SmartSensor"
Date "2021-06-14"
Rev "1.2"
Comp "Avans Hogeschool"
Comment1 "Maurice Snoeren"
Comment2 "Expertise Centrum Technische Innovatie"
Comment3 "Lectoraat Smart Energy and Datascience & ICT"
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR02
U 1 1 5F3DAA86
P 3600 4300
F 0 "#PWR02" H 3600 4050 50  0001 C CNN
F 1 "GND" H 3605 4127 50  0000 C CNN
F 2 "" H 3600 4300 50  0001 C CNN
F 3 "" H 3600 4300 50  0001 C CNN
	1    3600 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5F3DAB39
P 4450 3000
F 0 "J2" H 4450 3100 50  0000 C CNN
F 1 "BAT_1" V 4650 3150 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4450 3000 50  0001 C CNN
F 3 "~" H 4450 3000 50  0001 C CNN
	1    4450 3000
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5F3DAB3F
P 4750 3000
F 0 "J3" H 4750 3100 50  0000 C CNN
F 1 "BAT_2" V 4950 2750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4750 3000 50  0001 C CNN
F 3 "~" H 4750 3000 50  0001 C CNN
	1    4750 3000
	0    -1   1    0   
$EndComp
Text Notes 5050 2950 2    50   ~ 0
Battery (one/two cells)\n1.8V - 3.0V
Text Notes 4350 3100 0    50   ~ 0
+
Text Notes 4550 3100 0    50   ~ 0
-
$Comp
L SmartSensor-rescue:USB_B_Micro-Connector J1
U 1 1 5F3DAB52
P 3700 3850
AR Path="/5F3DAB52" Ref="J1"  Part="1" 
AR Path="/5F2DAD2E/5F3DAB52" Ref="J1"  Part="1" 
F 0 "J1" H 3757 4317 50  0000 C CNN
F 1 "USB_B_Micro" H 3757 4226 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Amphenol_10103594-0001LF_Horizontal" H 3850 3800 50  0001 C CNN
F 3 "~" H 3850 3800 50  0001 C CNN
	1    3700 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4300 3600 4250
Wire Wire Line
	3700 4250 3700 4300
NoConn ~ 4000 3850
NoConn ~ 4000 3950
Wire Wire Line
	4000 4050 4000 4300
Wire Wire Line
	4000 4300 3700 4300
Connection ~ 3700 4300
$Comp
L Device:R_Small R1
U 1 1 5F3DAB69
P 4250 3800
F 0 "R1" H 4050 3750 50  0000 L CNN
F 1 "100k" V 4350 3700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4250 3800 50  0001 C CNN
F 3 "~" H 4250 3800 50  0001 C CNN
	1    4250 3800
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5F3DAB6F
P 4250 4050
F 0 "R2" H 4050 4000 50  0000 L CNN
F 1 "200k" V 4350 3950 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4250 4050 50  0001 C CNN
F 3 "~" H 4250 4050 50  0001 C CNN
	1    4250 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 3900 4250 3950
Wire Wire Line
	4250 3700 4250 3650
Wire Wire Line
	4250 4150 4250 4300
Wire Wire Line
	4250 4300 4000 4300
Connection ~ 4000 4300
Connection ~ 4250 3650
Text Notes 4650 3100 0    50   ~ 0
+
Text Notes 4850 3100 0    50   ~ 0
-
Wire Wire Line
	4550 3200 4750 3200
Wire Wire Line
	4450 3200 4450 3350
$Comp
L power:GND #PWR03
U 1 1 5F3DAB8F
P 4850 3250
F 0 "#PWR03" H 4850 3000 50  0001 C CNN
F 1 "GND" H 4855 3077 50  0000 C CNN
F 2 "" H 4850 3250 50  0001 C CNN
F 3 "" H 4850 3250 50  0001 C CNN
	1    4850 3250
	1    0    0    -1  
$EndComp
Text GLabel 4250 3500 2    50   Input ~ 0
V_USB
Wire Wire Line
	4000 3650 4250 3650
Wire Wire Line
	4850 3200 4850 3250
$Comp
L Regulator_Switching:TPS63001 U1
U 1 1 5F3DAD01
P 7600 3650
F 0 "U1" H 7600 4317 50  0000 C CNN
F 1 "TPS63001" H 7600 4226 50  0000 C CNN
F 2 "Package_SON:Texas_DRC0010J_ThermalVias" H 8450 3100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps63000.pdf" H 7300 4200 50  0001 C CNN
	1    7600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4300 3700 4300
$Comp
L Device:L_Small L1
U 1 1 5F46AE8F
P 7600 2900
F 0 "L1" V 7785 2900 50  0000 C CNN
F 1 "2.2uH @ 2,5A" V 7694 2900 50  0000 C CNN
F 2 "Inductor_SMD:L_Vishay_IHLP-2020" H 7600 2900 50  0001 C CNN
F 3 "~" H 7600 2900 50  0001 C CNN
	1    7600 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5F46BAEC
P 6700 3700
F 0 "C1" H 6550 3850 50  0000 L CNN
F 1 "10uF" V 6600 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6700 3700 50  0001 C CNN
F 3 "~" H 6700 3700 50  0001 C CNN
	1    6700 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5F46C1BC
P 8500 3700
F 0 "C3" H 8350 3850 50  0000 L CNN
F 1 "10uF" V 8400 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8500 3700 50  0001 C CNN
F 3 "~" H 8500 3700 50  0001 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5F46C42B
P 8750 3700
F 0 "C4" H 8600 3850 50  0000 L CNN
F 1 "10uF" V 8650 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8750 3700 50  0001 C CNN
F 3 "~" H 8750 3700 50  0001 C CNN
	1    8750 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5F46C692
P 6850 3550
F 0 "R3" H 6700 3500 50  0000 L CNN
F 1 "100" H 6650 3600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6850 3550 50  0001 C CNN
F 3 "~" H 6850 3550 50  0001 C CNN
	1    6850 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F46CE2A
P 6850 4000
F 0 "C2" H 6700 4150 50  0000 L CNN
F 1 "100nF" V 6750 3850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6850 4000 50  0001 C CNN
F 3 "~" H 6850 4000 50  0001 C CNN
	1    6850 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 4350 6850 4350
Wire Wire Line
	7500 4350 7500 4250
Wire Wire Line
	7500 4350 7600 4350
Wire Wire Line
	7600 4350 7600 4250
Connection ~ 7500 4350
Wire Wire Line
	7200 3450 6850 3450
Wire Wire Line
	7200 3850 7100 3850
Wire Wire Line
	7100 3850 7100 3650
Wire Wire Line
	7100 3550 7200 3550
Wire Wire Line
	7200 3650 7100 3650
Connection ~ 7100 3650
Wire Wire Line
	7100 3650 7100 3550
Wire Wire Line
	6850 3650 7100 3650
Wire Wire Line
	6850 3900 6850 3650
Connection ~ 6850 3650
Wire Wire Line
	6850 4100 6850 4350
Connection ~ 6850 4350
Wire Wire Line
	6850 4350 7500 4350
Wire Wire Line
	7200 3250 7150 3250
Wire Wire Line
	7150 3250 7150 2900
Wire Wire Line
	7150 2900 7500 2900
Wire Wire Line
	8000 3250 8050 3250
Wire Wire Line
	8050 3250 8050 2900
Wire Wire Line
	8050 2900 7700 2900
Wire Wire Line
	8000 3450 8100 3450
Wire Wire Line
	8750 3450 8750 3600
Wire Wire Line
	8500 3600 8500 3450
Connection ~ 8500 3450
Wire Wire Line
	8500 3450 8750 3450
Wire Wire Line
	8000 3650 8100 3650
Wire Wire Line
	8100 3650 8100 3450
Connection ~ 8100 3450
Wire Wire Line
	8100 3450 8500 3450
$Comp
L power:GND #PWR04
U 1 1 5F4867E9
P 7600 4350
F 0 "#PWR04" H 7600 4100 50  0001 C CNN
F 1 "GND" H 7605 4177 50  0000 C CNN
F 2 "" H 7600 4350 50  0001 C CNN
F 3 "" H 7600 4350 50  0001 C CNN
	1    7600 4350
	1    0    0    -1  
$EndComp
Connection ~ 7600 4350
Wire Wire Line
	8500 3800 8500 4350
Wire Wire Line
	8500 4350 7600 4350
Wire Wire Line
	8750 3800 8750 4350
Wire Wire Line
	8750 4350 8500 4350
Connection ~ 8500 4350
Wire Wire Line
	6850 3450 6700 3450
Wire Wire Line
	6700 3450 6700 3600
Connection ~ 6850 3450
Wire Wire Line
	6700 3800 6700 4350
Text GLabel 4950 3850 2    50   Input ~ 0
V_IN
Wire Wire Line
	4250 3650 4250 3500
Connection ~ 3600 4300
Text GLabel 5900 3450 0    50   Input ~ 0
V_USB
Connection ~ 8750 3450
Text GLabel 5900 3550 0    50   Input ~ 0
V_IN
Wire Wire Line
	5900 3550 6000 3550
Text HLabel 5900 3700 0    50   Output ~ 0
V_IN
Wire Wire Line
	5900 3700 6000 3700
Wire Wire Line
	6000 3700 6000 3550
Text HLabel 4650 3950 2    50   Output ~ 0
ADAPTER_IN_USE
Wire Wire Line
	4650 3950 4250 3950
Connection ~ 4250 3950
Text HLabel 8900 3450 2    50   Output ~ 0
V_OUT_3.3V
Wire Wire Line
	8750 3450 8900 3450
$Comp
L Device:D_Small D1
U 1 1 5F888B42
P 6050 3450
F 0 "D1" H 6050 3245 50  0000 C CNN
F 1 "D_Small" H 6050 3336 50  0000 C CNN
F 2 "Diode_SMD:D_0805_2012Metric" V 6050 3450 50  0001 C CNN
F 3 "~" V 6050 3450 50  0001 C CNN
	1    6050 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 3450 5950 3450
$Comp
L power:+3.3V #PWR05
U 1 1 5F3775B0
P 8750 3350
F 0 "#PWR05" H 8750 3200 50  0001 C CNN
F 1 "+3.3V" H 8765 3523 50  0000 C CNN
F 2 "" H 8750 3350 50  0001 C CNN
F 3 "" H 8750 3350 50  0001 C CNN
	1    8750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3350 8750 3450
$Comp
L Device:Polyfuse_Small F1
U 1 1 5F3BCE33
P 6500 3450
F 0 "F1" V 6295 3450 50  0000 C CNN
F 1 "Polyfuse_Small" V 6386 3450 50  0000 C CNN
F 2 "Fuse:Fuse_1812_4532Metric" H 6550 3250 50  0001 L CNN
F 3 "~" H 6500 3450 50  0001 C CNN
	1    6500 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 3450 6250 3450
Wire Wire Line
	6600 3450 6700 3450
Connection ~ 6700 3450
Wire Wire Line
	6000 3550 6250 3550
Wire Wire Line
	6250 3550 6250 3450
Connection ~ 6000 3550
Connection ~ 6250 3450
Wire Wire Line
	6250 3450 6400 3450
Text HLabel 4250 3350 0    50   UnSpc ~ 0
V_BAT
Wire Wire Line
	4250 3350 4450 3350
Connection ~ 4450 3350
Wire Wire Line
	4450 3350 4450 3400
Text Notes 8900 3600 0    50   ~ 0
3.3V @ 1200mA
Text Notes 5650 3850 0    50   ~ 0
Range: 1.5 - 5.5V
$Comp
L Transistor_FET:DMG2301L Q1
U 1 1 5F3DAB7D
P 4600 3650
F 0 "Q1" H 4804 3696 50  0000 L CNN
F 1 "DMG2301L" H 4804 3605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4800 3575 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 4600 3650 50  0001 L CNN
	1    4600 3650
	1    0    0    1   
$EndComp
Wire Wire Line
	4400 3650 4250 3650
Wire Wire Line
	4700 3450 4700 3400
Wire Wire Line
	4700 3400 4450 3400
Wire Wire Line
	4950 3850 4700 3850
$EndSCHEMATC
