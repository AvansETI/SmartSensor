EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
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
L power:+3.3V #PWR?
U 1 1 5F8743BF
P 1950 1350
AR Path="/5F8743BF" Ref="#PWR?"  Part="1" 
AR Path="/5F86FCBB/5F8743BF" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 1950 1200 50  0001 C CNN
F 1 "+3.3V" H 1965 1523 50  0000 C CNN
F 2 "" H 1950 1350 50  0001 C CNN
F 3 "" H 1950 1350 50  0001 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
Text Notes 2050 2650 0    50   ~ 0
Optional:\nCO2 Sensor
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
Text Notes 4600 1950 0    50   ~ 0
Light Sensor
Wire Wire Line
	4000 2100 4000 2200
Wire Wire Line
	4000 2300 4000 2350
Text GLabel 4300 2100 0    50   Input ~ 0
SCL
Text GLabel 4300 2400 0    50   Input ~ 0
SDA
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
Wire Wire Line
	3800 2300 4000 2300
$Comp
L power:+3.3V #PWR08
U 1 1 5F877100
P 4000 1950
F 0 "#PWR08" H 4000 1800 50  0001 C CNN
F 1 "+3.3V" H 4015 2123 50  0000 C CNN
F 2 "" H 4000 1950 50  0001 C CNN
F 3 "" H 4000 1950 50  0001 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
$Comp
L SmartSensor-rescue:SHTC3-SamacSys_Parts IC?
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
$Comp
L power:+3.3V #PWR010
U 1 1 5F3CB78D
P 6500 1850
F 0 "#PWR010" H 6500 1700 50  0001 C CNN
F 1 "+3.3V" H 6515 2023 50  0000 C CNN
F 2 "" H 6500 1850 50  0001 C CNN
F 3 "" H 6500 1850 50  0001 C CNN
	1    6500 1850
	1    0    0    -1  
$EndComp
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
Wire Wire Line
	7500 2100 7600 2100
Connection ~ 7600 2100
Wire Wire Line
	7600 2100 7600 2450
Text Notes 6650 2400 0    50   ~ 0
Humidity and Temp
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
	1200 5050 1400 5050
Wire Wire Line
	1200 5150 1400 5150
Text GLabel 1400 5250 2    50   Input ~ 0
RESET
Wire Wire Line
	1200 5250 1400 5250
$Comp
L SamacSys_Parts:VEML7700-TT IC1
U 1 1 6059E1A4
P 4400 2100
F 0 "IC1" H 5128 1996 50  0000 L CNN
F 1 "VEML7700-TT" H 5128 1905 50  0000 L CNN
F 2 "SamacSys_Parts:VEML7700" H 5150 2200 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/veml7700-tt/vishay" H 5150 2100 50  0001 L CNN
F 4 "16Bit Ambient Light Sensor I2C 6.8x2.3mm" H 5150 2000 50  0001 L CNN "Description"
F 5 "" H 5150 1900 50  0001 L CNN "Height"
F 6 "78-VEML7700-TT" H 5150 1800 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Vishay-Semiconductors/VEML7700-TT?qs=BcfjnG7NVaXdL6DJFdWbdw%3D%3D" H 5150 1700 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 5150 1600 50  0001 L CNN "Manufacturer_Name"
F 9 "VEML7700-TT" H 5150 1500 50  0001 L CNN "Manufacturer_Part_Number"
	1    4400 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2300 4000 2300
Connection ~ 4000 2300
Wire Wire Line
	4400 2200 4000 2200
Wire Wire Line
	4300 2400 4400 2400
Wire Wire Line
	4300 2100 4400 2100
Wire Wire Line
	1950 1350 1950 1500
Connection ~ 1950 1500
Wire Wire Line
	4000 1950 4000 2100
Connection ~ 4000 2100
Wire Wire Line
	6500 1850 6500 2000
Connection ~ 6500 2000
$EndSCHEMATC
