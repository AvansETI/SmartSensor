EESchema Schematic File Version 4
LIBS:SmartSensor-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 6
Title "SmartSensor"
Date "2020-08-03"
Rev "1.0"
Comp "Avans Hogeschool"
Comment1 "Maurice Snoeren"
Comment2 "Expertise Centrum Technische Innovatie"
Comment3 "Lectoraat Smart Energy and Datascience & ICT"
Comment4 ""
$EndDescr
$Comp
L Sensor_Gas:CCS811 U?
U 1 1 5F8743B3
P 1950 2050
AR Path="/5F8743B3" Ref="U?"  Part="1" 
AR Path="/5F86FCBB/5F8743B3" Ref="U2"  Part="1" 
F 0 "U2" H 1700 2500 50  0000 C CNN
F 1 "CCS811" H 2150 2500 50  0000 C CNN
F 2 "Package_LGA:AMS_LGA-10-1EP_2.7x4mm_P0.6mm" H 1950 1450 50  0001 C CNN
F 3 "http://ams.com/eng/Products/Environmental-Sensors/Air-Quality-Sensors/CCS811" H 1950 1850 50  0001 C CNN
	1    1950 2050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:DMG2301L Q?
U 1 1 5F8743B9
P 1850 1300
AR Path="/5F8743B9" Ref="Q?"  Part="1" 
AR Path="/5F86FCBB/5F8743B9" Ref="Q2"  Part="1" 
F 0 "Q2" H 2054 1346 50  0000 L CNN
F 1 "DMG2301L" H 2054 1255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2050 1225 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 1850 1300 50  0001 L CNN
	1    1850 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F8743BF
P 1950 1050
AR Path="/5F8743BF" Ref="#PWR?"  Part="1" 
AR Path="/5F86FCBB/5F8743BF" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 1950 900 50  0001 C CNN
F 1 "+3.3V" H 1965 1223 50  0000 C CNN
F 2 "" H 1950 1050 50  0001 C CNN
F 3 "" H 1950 1050 50  0001 C CNN
	1    1950 1050
	1    0    0    -1  
$EndComp
Text Notes 2050 2650 0    50   ~ 0
Optional:\nCO2 Sensor
Wire Wire Line
	1950 1050 1950 1100
Wire Wire Line
	1950 1500 1950 1550
$Comp
L power:GND #PWR?
U 1 1 5F8743C8
P 1950 2600
AR Path="/5F8743C8" Ref="#PWR?"  Part="1" 
AR Path="/5F86FCBB/5F8743C8" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 1950 2350 50  0001 C CNN
F 1 "GND" H 1955 2427 50  0000 C CNN
F 2 "" H 1950 2600 50  0001 C CNN
F 3 "" H 1950 2600 50  0001 C CNN
	1    1950 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2550 1950 2600
$Comp
L Device:C_Small C?
U 1 1 5F8743CF
P 900 1600
AR Path="/5F8743CF" Ref="C?"  Part="1" 
AR Path="/5F86FCBB/5F8743CF" Ref="C5"  Part="1" 
F 0 "C5" H 700 1500 50  0000 L CNN
F 1 "100nF" H 650 1700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 900 1600 50  0001 C CNN
F 3 "~" H 900 1600 50  0001 C CNN
	1    900  1600
	1    0    0    -1  
$EndComp
Text GLabel 1600 1300 0    50   Input ~ 0
CO2_ENABLE
Wire Wire Line
	1600 1300 1650 1300
Text GLabel 1500 2050 0    50   Input ~ 0
SCL
Text GLabel 1500 1950 0    50   Input ~ 0
SDA
Wire Wire Line
	1500 1950 1550 1950
Wire Wire Line
	1500 2050 1550 2050
Text GLabel 1500 1850 0    50   Input ~ 0
CO2_INT
Text GLabel 1500 2350 0    50   Input ~ 0
CO2_WAKE
Wire Wire Line
	1500 2350 1550 2350
Wire Wire Line
	1500 1850 1550 1850
Wire Wire Line
	1950 1500 1150 1500
Connection ~ 1950 1500
Wire Wire Line
	900  1700 900  1750
Wire Wire Line
	900  2600 1950 2600
Connection ~ 1950 2600
Wire Wire Line
	1550 1750 1150 1750
Connection ~ 900  1750
Wire Wire Line
	900  1750 900  2600
Text GLabel 1500 2250 0    50   Input ~ 0
RESET
Wire Wire Line
	1500 2250 1550 2250
Wire Wire Line
	2350 1850 2450 1850
Wire Wire Line
	2450 1850 2450 1950
Wire Wire Line
	2450 1950 2350 1950
NoConn ~ 2350 2150
$Comp
L Device:C_Small C?
U 1 1 5F8743ED
P 1150 1600
AR Path="/5F8743ED" Ref="C?"  Part="1" 
AR Path="/5F86FCBB/5F8743ED" Ref="C6"  Part="1" 
F 0 "C6" H 950 1500 50  0000 L CNN
F 1 "1uF" H 1250 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1150 1600 50  0001 C CNN
F 3 "~" H 1150 1600 50  0001 C CNN
	1    1150 1600
	1    0    0    -1  
$EndComp
Connection ~ 1150 1500
Wire Wire Line
	1150 1500 900  1500
Wire Wire Line
	1150 1700 1150 1750
Connection ~ 1150 1750
Wire Wire Line
	1150 1750 900  1750
$Comp
L Device:R_Small R?
U 1 1 5F8743F8
P 1650 1150
AR Path="/5F8743F8" Ref="R?"  Part="1" 
AR Path="/5F86FCBB/5F8743F8" Ref="R4"  Part="1" 
F 0 "R4" H 1500 1100 50  0000 L CNN
F 1 "100k" V 1750 1050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1650 1150 50  0001 C CNN
F 3 "~" H 1650 1150 50  0001 C CNN
	1    1650 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	1650 1250 1650 1300
Connection ~ 1650 1300
$Comp
L Transistor_FET:DMG2301L Q3
U 1 1 5F8770D5
P 3900 1900
F 0 "Q3" H 4128 1946 50  0000 L CNN
F 1 "DMG2301L" H 4128 1855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4100 1825 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 3900 1900 50  0001 L CNN
	1    3900 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F8770DB
P 4000 2350
F 0 "#PWR09" H 4000 2100 50  0001 C CNN
F 1 "GND" H 4005 2177 50  0000 C CNN
F 2 "" H 4000 2350 50  0001 C CNN
F 3 "" H 4000 2350 50  0001 C CNN
	1    4000 2350
	1    0    0    -1  
$EndComp
$Comp
L VEML7700-TT:VEML7700-TT IC1
U 1 1 5F8770E9
P 3950 2200
F 0 "IC1" H 4150 2350 50  0000 L CNN
F 1 "VEML7700-TT" H 4400 2350 50  0000 L CNN
F 2 "SmartSensor:VEML7700" H 4800 2300 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/veml7700-tt/vishay" H 4800 2200 50  0001 L CNN
F 4 "16Bit Ambient Light Sensor I2C 6.8x2.3mm" H 4800 2100 50  0001 L CNN "Description"
F 5 "" H 4800 2000 50  0001 L CNN "Height"
F 6 "Vishay" H 4800 1900 50  0001 L CNN "Manufacturer_Name"
F 7 "VEML7700-TT" H 4800 1800 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "78-VEML7700-TT" H 4800 1700 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=78-VEML7700-TT" H 4800 1600 50  0001 L CNN "Mouser Price/Stock"
F 10 "1226791P" H 4800 1500 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/1226791P" H 4800 1400 50  0001 L CNN "RS Price/Stock"
	1    3950 2200
	1    0    0    -1  
$EndComp
Text Notes 4150 2500 0    50   ~ 0
Light Sensor
Wire Wire Line
	4000 2100 4000 2200
Wire Wire Line
	4000 2300 4000 2350
Text GLabel 4950 2200 2    50   Input ~ 0
SCL
Text GLabel 4950 2300 2    50   Input ~ 0
SDA
Wire Wire Line
	4900 2200 4950 2200
Wire Wire Line
	4900 2300 4950 2300
$Comp
L Device:C_Small C7
U 1 1 5F8770F6
P 3800 2200
F 0 "C7" H 3600 2100 50  0000 L CNN
F 1 "100nF" H 3550 2300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3800 2200 50  0001 C CNN
F 3 "~" H 3800 2200 50  0001 C CNN
	1    3800 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2100 4000 2100
Connection ~ 4000 2100
Wire Wire Line
	3800 2300 4000 2300
Connection ~ 4000 2300
$Comp
L power:+3.3V #PWR08
U 1 1 5F877100
P 4000 1650
F 0 "#PWR08" H 4000 1500 50  0001 C CNN
F 1 "+3.3V" H 4015 1823 50  0000 C CNN
F 2 "" H 4000 1650 50  0001 C CNN
F 3 "" H 4000 1650 50  0001 C CNN
	1    4000 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1650 4000 1700
Text GLabel 3650 1900 0    50   Input ~ 0
LS_ENABLE
Wire Wire Line
	3650 1900 3700 1900
$Comp
L Device:R_Small R5
U 1 1 5F877109
P 3700 1750
F 0 "R5" H 3550 1700 50  0000 L CNN
F 1 "100k" V 3800 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3700 1750 50  0001 C CNN
F 3 "~" H 3700 1750 50  0001 C CNN
	1    3700 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 1850 3700 1900
Connection ~ 3700 1900
Wire Wire Line
	3700 1650 4000 1650
Connection ~ 4000 1650
$Comp
L SamacSys_Parts:SHTC3 IC?
U 1 1 5F36BCF9
P 6500 2000
AR Path="/5F36BCF9" Ref="IC?"  Part="1" 
AR Path="/5F86FCBB/5F36BCF9" Ref="IC2"  Part="1" 
F 0 "IC2" H 7000 2265 50  0000 C CNN
F 1 "SHTC3" H 7000 2174 50  0000 C CNN
F 2 "Package_DFN_QFN:AMS_QFN-4-1EP_2x2mm_P0.95mm_EP0.7x1.6mm" H 7350 2100 50  0001 L CNN
F 3 "https://www.glynshop.com/erp/owweb/Daten/Datenblaetter/Sensirion/SHTC3.pdf" H 7350 2000 50  0001 L CNN
F 4 "Humidity and Temperature Sensor IC" H 7350 1900 50  0001 L CNN "Description"
F 5 "0.75" H 7350 1800 50  0001 L CNN "Height"
F 6 "Sensirion" H 7350 1700 50  0001 L CNN "Manufacturer_Name"
F 7 "SHTC3" H 7350 1600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "SHTC3" H 7350 1500 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/shtc3/sensirion-ag" H 7350 1400 50  0001 L CNN "Arrow Price/Stock"
F 10 "403-SHTC3" H 7350 1300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Sensirion/SHTC3?qs=y6ZabgHbY%252Bx3LlA87fqBwg%3D%3D" H 7350 1200 50  0001 L CNN "Mouser Price/Stock"
	1    6500 2000
	1    0    0    -1  
$EndComp
Connection ~ 1950 1050
Wire Wire Line
	1650 1050 1950 1050
$Comp
L Transistor_FET:DMG2301L Q4
U 1 1 5F3CB783
P 6400 1550
F 0 "Q4" H 6628 1596 50  0000 L CNN
F 1 "DMG2301L" H 6628 1505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6600 1475 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 6400 1550 50  0001 L CNN
	1    6400 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR010
U 1 1 5F3CB78D
P 6500 1300
F 0 "#PWR010" H 6500 1150 50  0001 C CNN
F 1 "+3.3V" H 6515 1473 50  0000 C CNN
F 2 "" H 6500 1300 50  0001 C CNN
F 3 "" H 6500 1300 50  0001 C CNN
	1    6500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1300 6500 1350
Text GLabel 6150 1550 0    50   Input ~ 0
HT_ENABLE
Wire Wire Line
	6150 1550 6200 1550
$Comp
L Device:R_Small R6
U 1 1 5F3CB79A
P 6200 1400
F 0 "R6" H 6050 1350 50  0000 L CNN
F 1 "100k" V 6300 1300 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6200 1400 50  0001 C CNN
F 3 "~" H 6200 1400 50  0001 C CNN
	1    6200 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6200 1500 6200 1550
Connection ~ 6200 1550
Wire Wire Line
	6200 1300 6500 1300
Connection ~ 6500 1300
Wire Wire Line
	6500 1750 6500 2000
$Comp
L power:GND #PWR011
U 1 1 5F3CEE80
P 7600 2500
F 0 "#PWR011" H 7600 2250 50  0001 C CNN
F 1 "GND" H 7605 2327 50  0000 C CNN
F 2 "" H 7600 2500 50  0001 C CNN
F 3 "" H 7600 2500 50  0001 C CNN
	1    7600 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5F3CF8D6
P 6000 2100
F 0 "C8" H 5800 2000 50  0000 L CNN
F 1 "100nF" H 5750 2200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6000 2100 50  0001 C CNN
F 3 "~" H 6000 2100 50  0001 C CNN
	1    6000 2100
	1    0    0    -1  
$EndComp
Text GLabel 6400 2200 0    50   Input ~ 0
SDA
Text GLabel 6400 2100 0    50   Input ~ 0
SCL
Wire Wire Line
	6400 2100 6500 2100
Wire Wire Line
	6400 2200 6500 2200
Wire Wire Line
	7500 2000 7600 2000
Wire Wire Line
	7600 2000 7600 2100
Wire Wire Line
	6000 2200 6000 2450
Wire Wire Line
	6000 2450 7600 2450
Connection ~ 7600 2450
Wire Wire Line
	7600 2450 7600 2500
Wire Wire Line
	6000 2000 6500 2000
Connection ~ 6500 2000
Wire Wire Line
	7500 2100 7600 2100
Connection ~ 7600 2100
Wire Wire Line
	7600 2100 7600 2450
Text Notes 6650 2400 0    50   ~ 0
Humidity and Temp
Text HLabel 1200 4750 0    50   Input ~ 0
CO2_ENABLE
Text HLabel 1200 4850 0    50   Input ~ 0
LS_ENABLE
Text HLabel 1200 4950 0    50   Input ~ 0
HT_ENABLE
Text GLabel 1400 4750 2    50   Input ~ 0
CO2_ENABLE
Text GLabel 1400 4850 2    50   Input ~ 0
LS_ENABLE
Text GLabel 1400 4950 2    50   Input ~ 0
HT_ENABLE
Text HLabel 1200 5050 0    50   BiDi ~ 0
SDA
Text HLabel 1200 5150 0    50   Input ~ 0
SCL
Text GLabel 1400 5050 2    50   Input ~ 0
SDA
Text GLabel 1400 5150 2    50   Input ~ 0
SCL
Text HLabel 1200 5250 0    50   Input ~ 0
RESET
Text HLabel 1200 4650 0    50   Output ~ 0
CO2_INT
Text HLabel 1200 4550 0    50   Output ~ 0
CO2_WAKE
Text GLabel 1400 4650 2    50   Input ~ 0
CO2_INT
Text GLabel 1400 4550 2    50   Input ~ 0
CO2_WAKE
Wire Wire Line
	1200 4550 1400 4550
Wire Wire Line
	1200 4650 1400 4650
Wire Wire Line
	1200 4750 1400 4750
Wire Wire Line
	1200 4850 1400 4850
Wire Wire Line
	1200 4950 1400 4950
Wire Wire Line
	1200 5050 1400 5050
Wire Wire Line
	1200 5150 1400 5150
Text GLabel 1400 5250 2    50   Input ~ 0
RESET
Wire Wire Line
	1200 5250 1400 5250
$EndSCHEMATC
