EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
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
L XB24CZ7PIT-004:XB24CZ7PIT-004 IC3
U 1 1 600613C2
P 4150 2900
F 0 "IC3" H 5350 3165 50  0000 C CNN
F 1 "XB24CZ7PIT-004" H 5350 3074 50  0000 C CNN
F 2 "XB24CZ7PIT-004:XB24CAPIT-001" H 6400 3000 50  0001 L CNN
F 3 "http://www.digi.com/pdf/ds_xbee_zigbee.pdf" H 6400 2900 50  0001 L CNN
F 4 "Zigbee / 802.15.4 Modules XBee ZB S2C TH PCB Antenna" H 6400 2800 50  0001 L CNN "Description"
F 5 "" H 6400 2700 50  0001 L CNN "Height"
F 6 "Digi International" H 6400 2600 50  0001 L CNN "Manufacturer_Name"
F 7 "XB24CZ7PIT-004" H 6400 2500 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "888-XB24CZ7PIT-004" H 6400 2400 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=888-XB24CZ7PIT-004" H 6400 2300 50  0001 L CNN "Mouser Price/Stock"
F 10 "XB24CZ7PIT-004" H 6400 2200 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/xb24cz7pit-004/digi-international" H 6400 2100 50  0001 L CNN "Arrow Price/Stock"
	1    4150 2900
	1    0    0    -1  
$EndComp
Text GLabel 4050 3000 0    50   Input ~ 0
FROM_XBEE_UART_TX
Text GLabel 4050 3100 0    50   Input ~ 0
FROM_XBEE_UART_RX
Text GLabel 6650 3700 2    50   Input ~ 0
XBEE_UART_CTS
Text GLabel 6650 3300 2    50   Input ~ 0
XBEE_UART_RTS
Text GLabel 4050 3300 0    50   Input ~ 0
XBEE_RESET
Connection ~ 3900 2600
Wire Wire Line
	3550 2600 3900 2600
Wire Wire Line
	3550 2550 3550 2600
Connection ~ 3900 2350
Wire Wire Line
	3550 2350 3900 2350
$Comp
L Device:C_Small C16
U 1 1 60078559
P 3550 2450
F 0 "C16" H 3600 2350 50  0000 L CNN
F 1 "1uF" V 3450 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3550 2450 50  0001 C CNN
F 3 "~" H 3550 2450 50  0001 C CNN
	1    3550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2550 3900 2600
$Comp
L power:GND #PWR030
U 1 1 60078560
P 3900 2600
F 0 "#PWR030" H 3900 2350 50  0001 C CNN
F 1 "GND" H 3905 2427 50  0000 C CNN
F 2 "" H 3900 2600 50  0001 C CNN
F 3 "" H 3900 2600 50  0001 C CNN
	1    3900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2350 4100 2350
$Comp
L Device:C_Small C17
U 1 1 60078567
P 3900 2450
F 0 "C17" H 3950 2350 50  0000 L CNN
F 1 "10uF" V 3800 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3900 2450 50  0001 C CNN
F 3 "~" H 3900 2450 50  0001 C CNN
	1    3900 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR032
U 1 1 60078580
P 4100 2150
F 0 "#PWR032" H 4100 2000 50  0001 C CNN
F 1 "+3.3V" H 4115 2323 50  0000 C CNN
F 2 "" H 4100 2150 50  0001 C CNN
F 3 "" H 4100 2150 50  0001 C CNN
	1    4100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2350 4100 2900
Wire Wire Line
	4100 2900 4150 2900
Connection ~ 4100 2350
Text GLabel 4050 3700 0    50   Input ~ 0
XBEE_D18
$Comp
L power:GND #PWR033
U 1 1 600856F0
P 4150 4100
F 0 "#PWR033" H 4150 3850 50  0001 C CNN
F 1 "GND" H 4155 3927 50  0000 C CNN
F 2 "" H 4150 4100 50  0001 C CNN
F 3 "" H 4150 4100 50  0001 C CNN
	1    4150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3800 4150 4100
Text GLabel 4050 3200 0    50   Input ~ 0
XBEE_SPI_MISO
Text GLabel 6650 3200 2    50   Input ~ 0
XBEE_SPI_SSEL
Text GLabel 6650 3800 2    50   Input ~ 0
XBEE_SPI_MOSI
Text GLabel 6650 3100 2    50   Input ~ 0
XBEE_SPI_CLK
Text GLabel 6650 3000 2    50   Input ~ 0
XBEE_AD1
Text GLabel 4050 3400 0    50   Input ~ 0
XBEE_PWM0
Text GLabel 4050 3500 0    50   Input ~ 0
XBEE_PWM1
NoConn ~ 4150 3600
Text GLabel 6650 3600 2    50   Input ~ 0
XBEE_SLEEP
Wire Wire Line
	4050 3000 4150 3000
Wire Wire Line
	4050 3100 4150 3100
Wire Wire Line
	4050 3200 4150 3200
Wire Wire Line
	4050 3300 4150 3300
Wire Wire Line
	4150 3400 4050 3400
Wire Wire Line
	4050 3500 4150 3500
Wire Wire Line
	4150 3700 4050 3700
Wire Wire Line
	6550 3000 6650 3000
Wire Wire Line
	6650 3100 6550 3100
Wire Wire Line
	6550 3200 6650 3200
Wire Wire Line
	6650 3300 6550 3300
Wire Wire Line
	6650 3600 6550 3600
Wire Wire Line
	6550 3700 6650 3700
Wire Wire Line
	6650 3800 6550 3800
$Comp
L Device:C_Small C15
U 1 1 600A4C34
P 3200 2450
F 0 "C15" H 3250 2350 50  0000 L CNN
F 1 "8.2pF" V 3100 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3200 2450 50  0001 C CNN
F 3 "~" H 3200 2450 50  0001 C CNN
	1    3200 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2350 3550 2350
Connection ~ 3550 2350
Wire Wire Line
	3200 2550 3200 2600
Wire Wire Line
	3200 2600 3550 2600
Connection ~ 3550 2600
$Comp
L power:GND #PWR034
U 1 1 600A7C2B
P 8000 3450
F 0 "#PWR034" H 8000 3200 50  0001 C CNN
F 1 "GND" H 8005 3277 50  0000 C CNN
F 2 "" H 8000 3450 50  0001 C CNN
F 3 "" H 8000 3450 50  0001 C CNN
	1    8000 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 600AD547
P 7550 3400
AR Path="/600AD547" Ref="R?"  Part="1" 
AR Path="/5F76931A/600AD547" Ref="R?"  Part="1" 
AR Path="/5F877B3A/600AD547" Ref="R12"  Part="1" 
F 0 "R12" V 7650 3350 50  0000 L CNN
F 1 "210" V 7450 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7550 3400 50  0001 C CNN
F 3 "~" H 7550 3400 50  0001 C CNN
	1    7550 3400
	0    1    1    0   
$EndComp
$Comp
L Device:LED_Small D?
U 1 1 600AD54D
P 7800 3400
AR Path="/600AD54D" Ref="D?"  Part="1" 
AR Path="/5F76931A/600AD54D" Ref="D?"  Part="1" 
AR Path="/5F877B3A/600AD54D" Ref="D4"  Part="1" 
F 0 "D4" H 7850 3300 50  0000 C CNN
F 1 "ASSOCIATION LED" H 7950 3200 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 7800 3400 50  0001 C CNN
F 3 "~" V 7800 3400 50  0001 C CNN
	1    7800 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7700 3400 7650 3400
Wire Wire Line
	6550 3400 7450 3400
Wire Wire Line
	7900 3400 8000 3400
Wire Wire Line
	8000 3400 8000 3450
Text Notes 3050 2750 0    50   ~ 0
Place C near pin 1
Text HLabel 3150 5350 0    50   Output ~ 0
XBEE_UART_TX
Text HLabel 3150 5450 0    50   Input ~ 0
XBEE_UART_RX
Text GLabel 4000 5350 2    50   Input ~ 0
FROM_XBEE_UART_TX
Text GLabel 4000 5450 2    50   Input ~ 0
FROM_XBEE_UART_RX
Text GLabel 1600 6000 2    50   Input ~ 0
XBEE_RESET
Text GLabel 1600 6700 2    50   Input ~ 0
XBEE_D18
Text GLabel 1600 5350 2    50   Input ~ 0
XBEE_SPI_MISO
Text GLabel 1600 6500 2    50   Input ~ 0
XBEE_PWM0
Text GLabel 1600 6600 2    50   Input ~ 0
XBEE_PWM1
Text GLabel 4000 5250 2    50   Input ~ 0
XBEE_UART_RTS
Text GLabel 1600 5650 2    50   Input ~ 0
XBEE_SPI_SSEL
Text GLabel 1600 5550 2    50   Input ~ 0
XBEE_SPI_CLK
Text GLabel 1600 6300 2    50   Input ~ 0
XBEE_AD1
Text GLabel 4000 5650 2    50   Input ~ 0
XBEE_UART_CTS
Text GLabel 1600 5450 2    50   Input ~ 0
XBEE_SPI_MOSI
Text GLabel 1600 5900 2    50   Input ~ 0
XBEE_SLEEP
Text GLabel 6650 3500 2    50   Input ~ 0
XBEE_VREF
Wire Wire Line
	6650 3500 6550 3500
Text GLabel 1600 6400 2    50   Input ~ 0
XBEE_VREF
Text HLabel 1500 5450 0    50   Input ~ 0
XBEE_RF_SPI_MOSI
Text HLabel 1500 5350 0    50   Output ~ 0
XBEE_RF_SPI_MISO
Text HLabel 1500 5550 0    50   Input ~ 0
XBEE_RF_SPI_CLK
Text HLabel 1500 5650 0    50   Input ~ 0
XBEE_SPI_SSEL
Text HLabel 1500 5900 0    50   Input ~ 0
XBEE_SLEEP
Text HLabel 1500 6000 0    50   Input ~ 0
XBEE_RESET
Text HLabel 1500 6300 0    50   BiDi ~ 0
XBEE_AD1
Text HLabel 1500 6400 0    50   UnSpc ~ 0
XBEE_VREF
Text HLabel 1500 6500 0    50   BiDi ~ 0
XBEE_PWM0
Text HLabel 1500 6600 0    50   BiDi ~ 0
XBEE_PWM1
Text HLabel 1500 6700 0    50   BiDi ~ 0
XBEE_D18
Wire Wire Line
	1500 5350 1600 5350
Wire Wire Line
	1600 5450 1500 5450
Wire Wire Line
	1500 5550 1600 5550
Wire Wire Line
	1600 5650 1500 5650
Wire Wire Line
	1500 5900 1600 5900
Wire Wire Line
	1600 6000 1500 6000
Wire Wire Line
	1600 6300 1500 6300
Wire Wire Line
	1500 6400 1600 6400
Wire Wire Line
	1500 6500 1600 6500
Wire Wire Line
	1600 6600 1500 6600
Wire Wire Line
	1500 6700 1600 6700
Text Notes 5100 4050 0    50   ~ 0
XBee S2C (Pro)
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J9
U 1 1 600DD28A
P 8750 2150
F 0 "J9" H 8800 2467 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 8800 2376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 8750 2150 50  0001 C CNN
F 3 "~" H 8750 2150 50  0001 C CNN
	1    8750 2150
	1    0    0    -1  
$EndComp
Text Notes 8450 2550 0    50   ~ 0
Module: nRF24L01
$Comp
L power:GND #PWR035
U 1 1 600DF1A1
P 9250 2550
F 0 "#PWR035" H 9250 2300 50  0001 C CNN
F 1 "GND" H 9255 2377 50  0000 C CNN
F 2 "" H 9250 2550 50  0001 C CNN
F 3 "" H 9250 2550 50  0001 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
Text HLabel 8450 2050 0    50   Output ~ 0
RF_IRQ
Text HLabel 9150 2250 2    50   Input ~ 0
RF_CE
Wire Wire Line
	8450 2050 8550 2050
Wire Wire Line
	9050 2250 9150 2250
Text Notes 7600 4300 0    50   ~ 0
NOTE: XBEE or RF can be connected!
Wire Wire Line
	9250 2550 9250 2350
Wire Wire Line
	9250 2350 9050 2350
Text GLabel 8450 2150 0    50   Input ~ 0
XBEE_SPI_MOSI
Wire Wire Line
	8450 2150 8550 2150
Text GLabel 9150 2050 2    50   Input ~ 0
XBEE_SPI_MISO
Wire Wire Line
	9150 2050 9050 2050
Text GLabel 9150 2150 2    50   Input ~ 0
XBEE_SPI_CLK
Wire Wire Line
	9150 2150 9050 2150
$Comp
L Connector:Conn_01x06_Male J8
U 1 1 60242760
P 3650 5450
F 0 "J8" H 3758 5831 50  0000 C CNN
F 1 "Conn_01x06_Male" V 3550 5400 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3650 5450 50  0001 C CNN
F 3 "~" H 3650 5450 50  0001 C CNN
	1    3650 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 60243238
P 3450 5350
F 0 "J7" H 3600 5500 50  0000 R CNN
F 1 "Conn_01x02_Male" V 3550 5150 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3450 5350 50  0001 C CNN
F 3 "~" H 3450 5350 50  0001 C CNN
	1    3450 5350
	-1   0    0    -1  
$EndComp
Text Notes 3100 4950 0    50   ~ 0
Jumper connect RX/TX
Text Notes 3650 5900 0    50   ~ 0
FTDI\n
NoConn ~ 3850 5550
$Comp
L power:GND #PWR031
U 1 1 60246815
P 4000 5750
F 0 "#PWR031" H 4000 5500 50  0001 C CNN
F 1 "GND" H 4005 5577 50  0000 C CNN
F 2 "" H 4000 5750 50  0001 C CNN
F 3 "" H 4000 5750 50  0001 C CNN
	1    4000 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5750 4000 5750
Wire Wire Line
	3850 5650 4000 5650
Wire Wire Line
	3850 5450 4000 5450
Wire Wire Line
	4000 5350 3850 5350
Wire Wire Line
	3850 5250 4000 5250
Wire Wire Line
	3150 5350 3250 5350
Wire Wire Line
	3150 5450 3250 5450
Text GLabel 8450 2250 0    50   Input ~ 0
XBEE_SPI_SSEL
Wire Wire Line
	8450 2250 8550 2250
$Comp
L SamacSys_Parts:LL3301FF065QJ S2
U 1 1 605B688A
P 8100 2900
F 0 "S2" H 8700 3165 50  0000 C CNN
F 1 "LL3301FF065QJ" H 8700 3074 50  0000 C CNN
F 2 "SamacSys_Parts:LL3301FF065QJ" H 9150 3000 50  0001 L CNN
F 3 "http://spec_sheets.e-switch.com/specs/P010456.pdf" H 9150 2900 50  0001 L CNN
F 4 "Pushbutton Switches 50mA 12VDC F065 7.0mm J-Lead" H 9150 2800 50  0001 L CNN "Description"
F 5 "7.3" H 9150 2700 50  0001 L CNN "Height"
F 6 "612-LL3301FF065QJ" H 9150 2600 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/E-Switch/LL3301FF065QJ/?qs=QtyuwXswaQgkr0cFSIRaTA%3D%3D" H 9150 2500 50  0001 L CNN "Mouser Price/Stock"
F 8 "E-Switch" H 9150 2400 50  0001 L CNN "Manufacturer_Name"
F 9 "LL3301FF065QJ" H 9150 2300 50  0001 L CNN "Manufacturer_Part_Number"
	1    8100 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2350 8550 2350
Wire Wire Line
	6550 2900 8100 2900
Wire Wire Line
	8100 3000 8000 3000
Wire Wire Line
	8000 3000 8000 3400
Connection ~ 8000 3400
NoConn ~ 9300 2900
NoConn ~ 9300 3000
Text Notes 8300 3200 0    50   ~ 0
SWITCH COMMISSION
Wire Wire Line
	4100 2150 4100 2350
NoConn ~ 7800 -150
$EndSCHEMATC
