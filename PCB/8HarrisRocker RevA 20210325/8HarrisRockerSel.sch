EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
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
L Device:D_x2_Serial_AKC D11
U 1 1 5E2845DC
P -4700 900
F 0 "D11" V -4654 978 50  0000 L CNN
F 1 "BAV23S" V -4745 978 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H -4700 900 50  0001 C CNN
F 3 "~" H -4700 900 50  0001 C CNN
	1    -4700 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-3650 1400 -3600 1400
Wire Wire Line
	-3600 1400 -3600 1900
Wire Wire Line
	-3600 1900 -3650 1900
Wire Wire Line
	-4350 1400 -4650 1400
Text Label -4600 1400 0    50   ~ 0
DRVn
Wire Wire Line
	-4350 1900 -4650 1900
Text Label -4600 1900 0    50   ~ 0
DRVf
$Comp
L power:GND #PWR?
U 1 1 5E2D5534
P -3600 1900
AR Path="/5CFC7757/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E2D5534" Ref="#PWR?"  Part="1" 
AR Path="/5E2D5534" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H -3600 1650 50  0001 C CNN
F 1 "GND" H -3600 1750 50  0000 C CNN
F 2 "" H -3600 1900 50  0001 C CNN
F 3 "" H -3600 1900 50  0001 C CNN
	1    -3600 1900
	0    -1   -1   0   
$EndComp
Connection ~ -3600 1900
$Comp
L CLRLibrary:DMN3135LVT Q6
U 1 1 5E2D553D
P -4150 1200
F 0 "Q6" H -4000 1347 60  0000 C CNN
F 1 "DMN3135LVT" H -4000 1241 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H -4150 1200 60  0001 C CNN
F 3 "" H -4150 1200 60  0001 C CNN
	1    -4150 1200
	1    0    0    -1  
$EndComp
$Comp
L CLRLibrary:DMN3135LVT Q6
U 2 1 5E2D5544
P -4150 1700
F 0 "Q6" H -4000 1847 60  0000 C CNN
F 1 "DMN3135LVT" H -4000 1741 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H -4150 1700 60  0001 C CNN
F 3 "" H -4150 1700 60  0001 C CNN
	2    -4150 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Pack04 NCR6
U 1 1 5E328D8F
P -2800 1500
F 0 "NCR6" V -3217 1500 50  0000 C CNN
F 1 "3K3" V -3126 1500 50  0000 C CNN
F 2 "CLRLibrary:RA2012-8" V -2525 1500 50  0001 C CNN
F 3 "~" H -2800 1500 50  0001 C CNN
	1    -2800 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	-3650 1300 -3350 1300
Wire Wire Line
	-3650 1800 -3400 1800
$Comp
L Device:Q_PMOS_GSD NCnQ6
U 1 1 5E3A5AEF
P -2600 850
F 0 "NCnQ6" V -2600 1100 50  0000 C CNN
F 1 "AO3407A" V -2700 1150 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H -2400 950 50  0001 C CNN
F 3 "~" H -2600 850 50  0001 C CNN
	1    -2600 850 
	0    1    -1   0   
$EndComp
Wire Wire Line
	-2400 750  -2150 750 
Text Label -3100 750  0    50   ~ 0
SAMPWR
Wire Wire Line
	-2600 1300 -2600 1050
Wire Wire Line
	-3150 750  -3100 750 
Wire Wire Line
	-3000 1400 -3100 1400
Wire Wire Line
	-3100 1400 -3100 750 
Connection ~ -3100 750 
Wire Wire Line
	-3100 750  -2800 750 
Wire Wire Line
	-2600 1300 -2600 1400
Connection ~ -2600 1300
Wire Wire Line
	-3100 1400 -3100 1600
Wire Wire Line
	-3100 1600 -3000 1600
Connection ~ -3100 1400
Wire Wire Line
	-3300 1800 -3300 1500
Wire Wire Line
	-3300 1500 -3000 1500
$Comp
L Device:Q_PMOS_GSD NCfQ6
U 1 1 5E6A7E1D
P -3800 850
F 0 "NCfQ6" V -3800 1100 50  0000 C CNN
F 1 "AO3407A" V -3900 1150 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H -3600 950 50  0001 C CNN
F 3 "~" H -3800 850 50  0001 C CNN
	1    -3800 850 
	0    1    -1   0   
$EndComp
Wire Wire Line
	-3600 750  -3350 750 
Connection ~ -4000 750 
Text Label -4300 750  0    50   ~ 0
SAMPWR
Wire Wire Line
	-4350 750  -4000 750 
Wire Wire Line
	-3800 1050 -3800 1100
Wire Wire Line
	-3800 1100 -2500 1100
Wire Wire Line
	-2500 1100 -2500 1500
Wire Wire Line
	-2500 1500 -2600 1500
Wire Wire Line
	-2500 1500 -2500 1600
Wire Wire Line
	-2500 1600 -2600 1600
Connection ~ -2500 1500
$Comp
L Connector_Generic:Conn_01x03 J32
U 1 1 5E78C34D
P -3550 400
F 0 "J32" H -3630 75  50  0000 C CNN
F 1 "NC PC" H -3630 166 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H3-2.54" H -3550 400 50  0001 C CNN
F 3 "~" H -3550 400 50  0001 C CNN
	1    -3550 400 
	-1   0    0    1   
$EndComp
Wire Wire Line
	-3350 750  -3350 500 
Wire Wire Line
	-3350 300  -3300 300 
Wire Wire Line
	-3300 300  -3300 1500
Connection ~ -3300 1500
$Comp
L Connector_Generic:Conn_01x03 J38
U 1 1 5E8148D6
P -2400 400
F 0 "J38" H -2480 75  50  0000 C CNN
F 1 "NC PC" H -2480 166 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H3-2.54" H -2400 400 50  0001 C CNN
F 3 "~" H -2400 400 50  0001 C CNN
	1    -2400 400 
	-1   0    0    1   
$EndComp
Wire Wire Line
	-2150 750  -2150 500 
Wire Wire Line
	-2150 500  -2200 500 
Wire Wire Line
	-2100 300  -2100 1150
Wire Wire Line
	-2100 1150 -3000 1150
Wire Wire Line
	-3000 1150 -3000 1300
Connection ~ -3000 1300
Wire Wire Line
	-2200 400  -1950 400 
Text Notes -7900 5500 0    98   ~ 0
NEG common, short 1/2. POS common, short 2/3\nNEG common, install NCxx\nPOS common, install PCxx\nxxfx=off drive, xxnx=on drive\n26 pin ribbon:AWP26-7240-T\n
Wire Wire Line
	-4700 450  -4700 600 
$Comp
L power:GND #PWR?
U 1 1 5E8FE727
P -4700 1200
AR Path="/5CFC7757/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E8FE727" Ref="#PWR?"  Part="1" 
AR Path="/5E8FE727" Ref="#PWR060"  Part="1" 
F 0 "#PWR060" H -4700 950 50  0001 C CNN
F 1 "GND" H -4700 1050 50  0000 C CNN
F 2 "" H -4700 1200 50  0001 C CNN
F 3 "" H -4700 1200 50  0001 C CNN
	1    -4700 1200
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_x2_Serial_AKC D14
U 1 1 5E8FE80A
P -2150 1600
F 0 "D14" V -2104 1678 50  0000 L CNN
F 1 "BAV23S" V -2195 1678 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H -2150 1600 50  0001 C CNN
F 3 "~" H -2150 1600 50  0001 C CNN
	1    -2150 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-1950 1600 -1950 400 
Connection ~ -1950 400 
$Comp
L power:GND #PWR?
U 1 1 5E95D61C
P -2150 1900
AR Path="/5CFC7757/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E95D61C" Ref="#PWR?"  Part="1" 
AR Path="/5E95D61C" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H -2150 1650 50  0001 C CNN
F 1 "GND" H -2150 1750 50  0000 C CNN
F 2 "" H -2150 1900 50  0001 C CNN
F 3 "" H -2150 1900 50  0001 C CNN
	1    -2150 1900
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J35
U 1 1 5E95E324
P -3150 2000
F 0 "J35" H -3230 1675 50  0000 C CNN
F 1 "PC NC" H -3230 1766 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H3-2.54" H -3150 2000 50  0001 C CNN
F 3 "~" H -3150 2000 50  0001 C CNN
	1    -3150 2000
	-1   0    0    1   
$EndComp
Text Label -2900 1900 0    50   ~ 0
SAMPWR
$Comp
L power:GND #PWR?
U 1 1 5E95E751
P -2950 2100
AR Path="/5CFC7757/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E95E751" Ref="#PWR?"  Part="1" 
AR Path="/5E95E751" Ref="#PWR075"  Part="1" 
F 0 "#PWR075" H -2950 1850 50  0001 C CNN
F 1 "GND" H -2950 1950 50  0000 C CNN
F 2 "" H -2950 2100 50  0001 C CNN
F 3 "" H -2950 2100 50  0001 C CNN
	1    -2950 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-2950 1900 -2550 1900
$Comp
L Connector_Generic:Conn_01x01 PWR6
U 1 1 5EA84B58
P -5300 2850
F 0 "PWR6" H -5400 2950 50  0000 C CNN
F 1 "kk1" H -5400 2750 50  0000 C CNN
F 2 "CLRLibrary:KK156-1" H -5300 2850 50  0001 C CNN
F 3 "~" H -5300 2850 50  0001 C CNN
	1    -5300 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	-5100 2850 -4700 2850
$Comp
L Connector_Generic:Conn_01x01 GND6
U 1 1 5EAB6DE5
P -5350 2600
F 0 "GND6" H -5500 2700 50  0000 C CNN
F 1 "kk1" H -5500 2500 50  0000 C CNN
F 2 "CLRLibrary:KK156-1" H -5350 2600 50  0001 C CNN
F 3 "~" H -5350 2600 50  0001 C CNN
	1    -5350 2600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EAB6E9B
P -5150 2600
AR Path="/5CFC7757/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5EAB6E9B" Ref="#PWR?"  Part="1" 
AR Path="/5EAB6E9B" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H -5150 2350 50  0001 C CNN
F 1 "GND" H -5150 2450 50  0000 C CNN
F 2 "" H -5150 2600 50  0001 C CNN
F 3 "" H -5150 2600 50  0001 C CNN
	1    -5150 2600
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J41
U 1 1 5EAE855B
P -1350 1050
F 0 "J41" H -1550 1500 50  0000 L CNN
F 1 "SAM_KK6" H -1550 1400 50  0000 L CNN
F 2 "CLRLibrary:KK156-6" H -1350 1050 50  0001 C CNN
F 3 "~" H -1350 1050 50  0001 C CNN
	1    -1350 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	-1750 2000 -1750 1350
Wire Wire Line
	-1750 1350 -1550 1350
Wire Wire Line
	-2950 2000 -1750 2000
Wire Wire Line
	-1650 1250 -1550 1250
Wire Wire Line
	-1950 400  -1650 400 
Wire Wire Line
	-1750 950  -1550 950 
Wire Wire Line
	-3350 400  -3000 400 
Text Notes -1300 1400 0    63   ~ 0
NC\nOFF COIL\nSENSECOM\nSENSE\nON COIL\nCOIL COMMON\n
Wire Wire Line
	-1650 400  -1650 1250
Wire Wire Line
	-1550 1050 -1850 1050
Wire Wire Line
	-1850 1050 -1850 2250
Text Label -2650 2250 0    50   ~ 0
SENSECOMMON
Wire Wire Line
	-1550 1150 -1700 1150
Wire Wire Line
	-1700 1150 -1700 2350
Text Label -2650 2350 0    50   ~ 0
SENSE
Wire Wire Line
	-4700 450  -4000 450 
Wire Wire Line
	-4200 900  -4200 200 
Wire Wire Line
	-4200 200  -3000 200 
Wire Wire Line
	-4500 900  -4200 900 
Wire Wire Line
	-2150 1300 -2150 1200
Wire Wire Line
	-2150 1200 -2000 1200
Wire Wire Line
	-2000 1200 -2000 100 
Wire Wire Line
	-2000 100  -4000 100 
Wire Wire Line
	-4000 100  -4000 450 
Connection ~ -4000 450 
Wire Wire Line
	-4000 450  -4000 750 
$Comp
L Device:R R32
U 1 1 5ECB4F47
P -4650 1550
F 0 "R32" H -4600 1600 50  0000 L CNN
F 1 "1K" V -4650 1450 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -4720 1550 50  0001 C CNN
F 3 "~" H -4650 1550 50  0001 C CNN
	1    -4650 1550
	1    0    0    -1  
$EndComp
Connection ~ -4650 1400
Wire Wire Line
	-4650 1400 -4700 1400
$Comp
L Device:R R33
U 1 1 5ECB52A6
P -4650 2050
F 0 "R33" H -4600 2150 50  0000 L CNN
F 1 "1K" V -4650 1950 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -4720 2050 50  0001 C CNN
F 3 "~" H -4650 2050 50  0001 C CNN
	1    -4650 2050
	1    0    0    -1  
$EndComp
Connection ~ -4650 1900
Wire Wire Line
	-4650 1900 -4700 1900
$Comp
L Device:R R41
U 1 1 5ECB66E3
P -1850 2350
F 0 "R41" V -1750 2300 50  0000 L CNN
F 1 "P15KN330" V -1850 2250 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -1920 2350 50  0001 C CNN
F 3 "~" H -1850 2350 50  0001 C CNN
	1    -1850 2350
	0    1    1    0   
$EndComp
$Comp
L Device:R PR38
U 1 1 5ECEA5F5
P -3150 2350
F 0 "PR38" V -3050 2300 50  0000 L CNN
F 1 "P3K3" V -3150 2250 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -3220 2350 50  0001 C CNN
F 3 "~" H -3150 2350 50  0001 C CNN
	1    -3150 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	-3000 2350 -2000 2350
Text Label -6300 650  0    50   ~ 0
DRVn0
Text Label -5400 650  0    50   ~ 0
DRVf0
Text Label -6300 750  0    50   ~ 0
SENSE0
Text Label -5400 750  0    50   ~ 0
SENSE1
Text Label -6300 850  0    50   ~ 0
DRVn1
Text Label -5400 850  0    50   ~ 0
DRVf1
Wire Wire Line
	-6000 650  -6350 650 
Wire Wire Line
	-6000 750  -6350 750 
Wire Wire Line
	-6000 850  -6350 850 
Wire Wire Line
	-5150 650  -5500 650 
Wire Wire Line
	-5150 750  -5500 750 
Wire Wire Line
	-5150 850  -5500 850 
Text Label -6300 950  0    50   ~ 0
DRVn2
Text Label -6300 1050 0    50   ~ 0
SENSE2
Text Label -6300 1150 0    50   ~ 0
DRVn3
Wire Wire Line
	-6000 950  -6350 950 
Wire Wire Line
	-6000 1050 -6350 1050
Wire Wire Line
	-6000 1150 -6350 1150
Text Label -5400 950  0    50   ~ 0
DRVf2
Text Label -5400 1050 0    50   ~ 0
SENSE3
Text Label -5400 1150 0    50   ~ 0
DRVf3
Wire Wire Line
	-5150 950  -5500 950 
Wire Wire Line
	-5150 1050 -5500 1050
Wire Wire Line
	-5150 1150 -5500 1150
Text Label -6300 1250 0    50   ~ 0
DRVn4
Text Label -6300 1350 0    50   ~ 0
SENSE4
Text Label -6300 1450 0    50   ~ 0
DRVn5
Wire Wire Line
	-6000 1250 -6350 1250
Wire Wire Line
	-6000 1350 -6350 1350
Wire Wire Line
	-6000 1450 -6350 1450
Text Label -6300 1550 0    50   ~ 0
DRVn6
Text Label -6300 1650 0    50   ~ 0
SENSE6
Wire Wire Line
	-6000 1550 -6350 1550
Wire Wire Line
	-6000 1650 -6350 1650
Text Label -5400 1250 0    50   ~ 0
DRVf4
Text Label -5400 1350 0    50   ~ 0
SENSE5
Text Label -5400 1450 0    50   ~ 0
DRVf5
Wire Wire Line
	-5150 1250 -5500 1250
Wire Wire Line
	-5150 1350 -5500 1350
Wire Wire Line
	-5150 1450 -5500 1450
Text Label -5400 1550 0    50   ~ 0
DRVf6
Text Label -5400 1650 0    50   ~ 0
SENSE7
Text Label -5400 1750 0    50   ~ 0
DRVf7
Wire Wire Line
	-5150 1550 -5500 1550
Wire Wire Line
	-5150 1650 -5500 1650
Wire Wire Line
	-5150 1750 -5500 1750
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J28
U 1 1 5EF6D151
P -5800 1150
F 0 "J28" H -5750 1967 50  0000 C CNN
F 1 "302-S261" H -5750 1876 50  0000 C CNN
F 2 "CLRLibrary:2x13_2.54mmShrouded" H -5800 1150 50  0001 C CNN
F 3 "~" H -5800 1150 50  0001 C CNN
	1    -5800 1150
	1    0    0    -1  
$EndComp
Text Label -6300 1750 0    50   ~ 0
DRVn7
Wire Wire Line
	-6000 1750 -6350 1750
Text Label -5450 550  0    50   ~ 0
SENSECOMMON
Wire Wire Line
	-5150 550  -5500 550 
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5E929597
P -3700 3750
F 0 "J2" H -3780 3425 50  0000 C CNN
F 1 "SEL" H -3780 3516 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -3700 3750 50  0001 C CNN
F 3 "~" H -3700 3750 50  0001 C CNN
	1    -3700 3750
	-1   0    0    1   
$EndComp
Text Label -3400 3650 0    50   ~ 0
DRVf0
Wire Wire Line
	-3150 3650 -3500 3650
Text Label -3400 3850 0    50   ~ 0
DRVf1
Wire Wire Line
	-3150 3850 -3500 3850
Text Label -3400 3750 0    50   ~ 0
DRVf
Wire Wire Line
	-3150 3750 -3500 3750
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 5E93AB52
P -2950 3750
F 0 "J4" H -3030 3425 50  0000 C CNN
F 1 "SEL" H -3030 3516 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2950 3750 50  0001 C CNN
F 3 "~" H -2950 3750 50  0001 C CNN
	1    -2950 3750
	-1   0    0    1   
$EndComp
Text Label -2650 3650 0    50   ~ 0
DRVf2
Wire Wire Line
	-2400 3650 -2750 3650
Text Label -2650 3850 0    50   ~ 0
DRVf3
Wire Wire Line
	-2400 3850 -2750 3850
Text Label -2650 3750 0    50   ~ 0
DRVf
Wire Wire Line
	-2400 3750 -2750 3750
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 5E940C8F
P -2250 3750
F 0 "J7" H -2330 3425 50  0000 C CNN
F 1 "SEL" H -2330 3516 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2250 3750 50  0001 C CNN
F 3 "~" H -2250 3750 50  0001 C CNN
	1    -2250 3750
	-1   0    0    1   
$EndComp
Text Label -1950 3650 0    50   ~ 0
DRVf4
Wire Wire Line
	-1700 3650 -2050 3650
Text Label -1950 3850 0    50   ~ 0
DRVf5
Wire Wire Line
	-1700 3850 -2050 3850
Text Label -1950 3750 0    50   ~ 0
DRVf
Wire Wire Line
	-1700 3750 -2050 3750
$Comp
L Connector_Generic:Conn_01x03 J10
U 1 1 5E940C9B
P -1500 3750
F 0 "J10" H -1580 3425 50  0000 C CNN
F 1 "SEL" H -1580 3516 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -1500 3750 50  0001 C CNN
F 3 "~" H -1500 3750 50  0001 C CNN
	1    -1500 3750
	-1   0    0    1   
$EndComp
Text Label -1200 3650 0    50   ~ 0
DRVf6
Wire Wire Line
	-950 3650 -1300 3650
Text Label -1200 3850 0    50   ~ 0
DRVf7
Wire Wire Line
	-950 3850 -1300 3850
Text Label -1200 3750 0    50   ~ 0
DRVf
Wire Wire Line
	-950 3750 -1300 3750
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5E947739
P -3700 4300
F 0 "J3" H -3780 3975 50  0000 C CNN
F 1 "SEL" H -3780 4066 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -3700 4300 50  0001 C CNN
F 3 "~" H -3700 4300 50  0001 C CNN
	1    -3700 4300
	-1   0    0    1   
$EndComp
Text Label -3400 4200 0    50   ~ 0
DRVn0
Wire Wire Line
	-3150 4200 -3500 4200
Text Label -3400 4400 0    50   ~ 0
DRVn1
Wire Wire Line
	-3150 4400 -3500 4400
Text Label -3400 4300 0    50   ~ 0
DRVn
Wire Wire Line
	-3150 4300 -3500 4300
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5E94E540
P -2950 4300
F 0 "J5" H -3030 3975 50  0000 C CNN
F 1 "SEL" H -3030 4066 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2950 4300 50  0001 C CNN
F 3 "~" H -2950 4300 50  0001 C CNN
	1    -2950 4300
	-1   0    0    1   
$EndComp
Text Label -2650 4200 0    50   ~ 0
DRVn2
Wire Wire Line
	-2400 4200 -2750 4200
Text Label -2650 4400 0    50   ~ 0
DRVn3
Wire Wire Line
	-2400 4400 -2750 4400
Text Label -2650 4300 0    50   ~ 0
DRVn
Wire Wire Line
	-2400 4300 -2750 4300
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 5E9557C6
P -2250 4300
F 0 "J8" H -2330 3975 50  0000 C CNN
F 1 "SEL" H -2330 4066 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2250 4300 50  0001 C CNN
F 3 "~" H -2250 4300 50  0001 C CNN
	1    -2250 4300
	-1   0    0    1   
$EndComp
Text Label -1950 4200 0    50   ~ 0
DRVn4
Wire Wire Line
	-1700 4200 -2050 4200
Text Label -1950 4400 0    50   ~ 0
DRVn5
Wire Wire Line
	-1700 4400 -2050 4400
Text Label -1950 4300 0    50   ~ 0
DRVn
Wire Wire Line
	-1700 4300 -2050 4300
$Comp
L Connector_Generic:Conn_01x03 J11
U 1 1 5E9557D2
P -1500 4300
F 0 "J11" H -1580 3975 50  0000 C CNN
F 1 "SEL" H -1580 4066 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -1500 4300 50  0001 C CNN
F 3 "~" H -1500 4300 50  0001 C CNN
	1    -1500 4300
	-1   0    0    1   
$EndComp
Text Label -1200 4200 0    50   ~ 0
DRVn6
Wire Wire Line
	-950 4200 -1300 4200
Text Label -1200 4400 0    50   ~ 0
DRVn7
Wire Wire Line
	-950 4400 -1300 4400
Text Label -1200 4300 0    50   ~ 0
DRVn
Wire Wire Line
	-950 4300 -1300 4300
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5E95D3D7
P -3750 4900
F 0 "J1" H -3830 4575 50  0000 C CNN
F 1 "SEL" H -3830 4666 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -3750 4900 50  0001 C CNN
F 3 "~" H -3750 4900 50  0001 C CNN
	1    -3750 4900
	-1   0    0    1   
$EndComp
Text Label -3450 4800 0    50   ~ 0
SENSE0
Wire Wire Line
	-3200 4800 -3550 4800
Text Label -3450 5000 0    50   ~ 0
SENSE1
Wire Wire Line
	-3200 5000 -3550 5000
Text Label -3450 4900 0    50   ~ 0
SENSE
Wire Wire Line
	-3200 4900 -3550 4900
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 5E978BD9
P -2950 4900
F 0 "J6" H -3030 4575 50  0000 C CNN
F 1 "SEL" H -3030 4666 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2950 4900 50  0001 C CNN
F 3 "~" H -2950 4900 50  0001 C CNN
	1    -2950 4900
	-1   0    0    1   
$EndComp
Text Label -2650 4800 0    50   ~ 0
SENSE2
Wire Wire Line
	-2400 4800 -2750 4800
Text Label -2650 5000 0    50   ~ 0
SENSE3
Wire Wire Line
	-2400 5000 -2750 5000
Text Label -2650 4900 0    50   ~ 0
SENSE
Wire Wire Line
	-2400 4900 -2750 4900
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 5E98119C
P -2250 4900
F 0 "J9" H -2330 4575 50  0000 C CNN
F 1 "SEL" H -2330 4666 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2250 4900 50  0001 C CNN
F 3 "~" H -2250 4900 50  0001 C CNN
	1    -2250 4900
	-1   0    0    1   
$EndComp
Text Label -1950 4800 0    50   ~ 0
SENSE4
Wire Wire Line
	-1700 4800 -2050 4800
Text Label -1950 5000 0    50   ~ 0
SENSE5
Wire Wire Line
	-1700 5000 -2050 5000
Text Label -1950 4900 0    50   ~ 0
SENSE
Wire Wire Line
	-1700 4900 -2050 4900
$Comp
L Connector_Generic:Conn_01x03 J12
U 1 1 5E9811A8
P -1450 4900
F 0 "J12" H -1530 4575 50  0000 C CNN
F 1 "SEL" H -1530 4666 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -1450 4900 50  0001 C CNN
F 3 "~" H -1450 4900 50  0001 C CNN
	1    -1450 4900
	-1   0    0    1   
$EndComp
Text Label -1150 4800 0    50   ~ 0
SENSE6
Wire Wire Line
	-900 4800 -1250 4800
Text Label -1150 5000 0    50   ~ 0
SENSE7
Wire Wire Line
	-900 5000 -1250 5000
Text Label -1150 4900 0    50   ~ 0
SENSE
Wire Wire Line
	-900 4900 -1250 4900
$Comp
L Connector_Generic:Conn_01x02 J13
U 1 1 5E2ACE99
P -3700 2500
F 0 "J13" H -3620 2492 50  0000 L CNN
F 1 "Conn_01x02" H -3620 2401 50  0000 L CNN
F 2 "Connectors_Molex:Molex_Microfit3_Header_02x01_Angled_43045-020x" H -3700 2500 50  0001 C CNN
F 3 "~" H -3700 2500 50  0001 C CNN
	1    -3700 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	-4300 2600 -3900 2600
Wire Wire Line
	-3900 2500 -4650 2500
Wire Wire Line
	-4650 2500 -4650 2400
$Comp
L Device:CP C1
U 1 1 5E2BF4F6
P -5250 2250
F 0 "C1" H -5132 2296 50  0000 L CNN
F 1 "CP" H -5132 2205 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P2.50mm_P5.00mm" H -5212 2100 50  0001 C CNN
F 3 "~" H -5250 2250 50  0001 C CNN
	1    -5250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	-5250 2400 -4650 2400
Wire Wire Line
	-5650 2100 -5250 2100
$Comp
L Connector_Generic:Conn_01x03 J14
U 1 1 5E6FBD03
P -1350 2000
F 0 "J14" H -1430 1675 50  0000 C CNN
F 1 "SEL" H -1430 1766 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -1350 2000 50  0001 C CNN
F 3 "~" H -1350 2000 50  0001 C CNN
	1    -1350 2000
	1    0    0    1   
$EndComp
Wire Wire Line
	-1550 1900 -2050 1900
Wire Wire Line
	-2050 1900 -2050 1950
Wire Wire Line
	-2050 1950 -2100 1950
Wire Wire Line
	-2550 1950 -2550 1900
Wire Wire Line
	-1750 2000 -1550 2000
Connection ~ -1750 2000
$Comp
L power:GND #PWR?
U 1 1 5E730C77
P -1550 2100
AR Path="/5CFC7757/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5E730C77" Ref="#PWR?"  Part="1" 
AR Path="/5E730C77" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H -1550 1850 50  0001 C CNN
F 1 "GND" H -1550 1950 50  0000 C CNN
F 2 "" H -1550 2100 50  0001 C CNN
F 3 "" H -1550 2100 50  0001 C CNN
	1    -1550 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J15
U 1 1 5E730E3D
P -3850 400
F 0 "J15" H -3930 75  50  0000 C CNN
F 1 "SEL" H -3930 166 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -3850 400 50  0001 C CNN
F 3 "~" H -3850 400 50  0001 C CNN
	1    -3850 400 
	-1   0    0    1   
$EndComp
Wire Wire Line
	-3650 300  -3350 300 
Connection ~ -3350 300 
Wire Wire Line
	-3650 400  -3350 400 
Connection ~ -3350 400 
Wire Wire Line
	-3650 500  -3350 500 
Connection ~ -3350 500 
$Comp
L Connector_Generic:Conn_01x03 J16
U 1 1 5E74D380
P -2700 400
F 0 "J16" H -2780 75  50  0000 C CNN
F 1 "SEL" H -2780 166 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -2700 400 50  0001 C CNN
F 3 "~" H -2700 400 50  0001 C CNN
	1    -2700 400 
	-1   0    0    1   
$EndComp
Wire Wire Line
	-2500 300  -2200 300 
Connection ~ -2200 300 
Wire Wire Line
	-2200 300  -2100 300 
Wire Wire Line
	-2500 400  -2200 400 
Connection ~ -2200 400 
Wire Wire Line
	-2500 500  -2200 500 
Connection ~ -2200 500 
Wire Wire Line
	-3000 200  -1750 200 
Connection ~ -3000 200 
Wire Wire Line
	-3000 200  -3000 400 
Wire Wire Line
	-1750 200  -1750 950 
$Comp
L Device:LED D1
U 1 1 5E77B140
P -2400 2700
F 0 "D1" H -2409 2916 50  0000 C CNN
F 1 "LED" H -2409 2825 50  0000 C CNN
F 2 "LEDs:LED_0603" H -2400 2700 50  0001 C CNN
F 3 "~" H -2400 2700 50  0001 C CNN
	1    -2400 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E77B247
P -2700 2700
F 0 "R1" V -2600 2650 50  0000 L CNN
F 1 "3K3" V -2700 2600 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -2770 2700 50  0001 C CNN
F 3 "~" H -2700 2700 50  0001 C CNN
	1    -2700 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	-2250 2700 -2100 2700
Wire Wire Line
	-2100 2700 -2100 1950
Connection ~ -2100 1950
Wire Wire Line
	-2100 1950 -2550 1950
$Comp
L Device:LED D2
U 1 1 5E791C7A
P -2400 3000
F 0 "D2" H -2409 3216 50  0000 C CNN
F 1 "LED" H -2409 3125 50  0000 C CNN
F 2 "LEDs:LED_0603" H -2400 3000 50  0001 C CNN
F 3 "~" H -2400 3000 50  0001 C CNN
	1    -2400 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E791C80
P -2700 3000
F 0 "R2" V -2600 2950 50  0000 L CNN
F 1 "3K3" V -2700 2900 50  0000 L CNN
F 2 "SeeedOPL-Resistor-2016:R0603" V -2770 3000 50  0001 C CNN
F 3 "~" H -2700 3000 50  0001 C CNN
	1    -2700 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	-2100 2700 -2100 3000
Wire Wire Line
	-2100 3000 -2250 3000
Connection ~ -2100 2700
Wire Wire Line
	-2850 2700 -3350 2700
Wire Wire Line
	-3350 2700 -3350 1300
Connection ~ -3350 1300
Wire Wire Line
	-3350 1300 -3000 1300
Wire Wire Line
	-2850 3000 -3400 3000
Wire Wire Line
	-3400 3000 -3400 1800
Connection ~ -3400 1800
Wire Wire Line
	-3400 1800 -3300 1800
$Comp
L Connector_Generic:Conn_01x03 J17
U 1 1 5E7C1E9A
P -3950 2250
F 0 "J17" H -4030 1925 50  0000 C CNN
F 1 "SEL" H -4030 2016 50  0000 C CNN
F 2 "CLRLibrary:0603Jumper" H -3950 2250 50  0001 C CNN
F 3 "~" H -3950 2250 50  0001 C CNN
	1    -3950 2250
	-1   0    0    1   
$EndComp
Text Label -3700 2150 0    50   ~ 0
SAMPWR
Wire Wire Line
	-3750 2150 -3550 2150
Wire Wire Line
	-3750 2250 -1850 2250
Wire Wire Line
	-3500 2850 -3500 2350
Wire Wire Line
	-3500 2350 -3750 2350
Wire Wire Line
	-3300 2350 -3500 2350
Connection ~ -3500 2350
$Comp
L power:GNDS #PWR0101
U 1 1 5EBB8DAC
P -6800 600
F 0 "#PWR0101" H -6800 350 50  0001 C CNN
F 1 "GNDS" H -6795 427 50  0000 C CNN
F 2 "" H -6800 600 50  0001 C CNN
F 3 "" H -6800 600 50  0001 C CNN
	1    -6800 600 
	1    0    0    -1  
$EndComp
Wire Wire Line
	-6000 550  -6800 550 
Wire Wire Line
	-6800 550  -6800 600 
$Comp
L power:GND #PWR?
U 1 1 5EBC2284
P -4650 2500
AR Path="/5CFC7757/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5CFEE74D/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5CE81FF5/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5CE982AE/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5BA655A7/5D01C728/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5D01CD70/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5D08CCAD/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5D117FD0/5EBC2284" Ref="#PWR?"  Part="1" 
AR Path="/5EBC2284" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H -4650 2250 50  0001 C CNN
F 1 "GND" H -4650 2350 50  0000 C CNN
F 2 "" H -4650 2500 50  0001 C CNN
F 3 "" H -4650 2500 50  0001 C CNN
	1    -4650 2500
	1    0    0    -1  
$EndComp
Connection ~ -4650 2500
$Comp
L power:GNDS #PWR0103
U 1 1 5EBC2307
P -4650 1700
F 0 "#PWR0103" H -4650 1450 50  0001 C CNN
F 1 "GNDS" H -4645 1527 50  0000 C CNN
F 2 "" H -4650 1700 50  0001 C CNN
F 3 "" H -4650 1700 50  0001 C CNN
	1    -4650 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GNDS #PWR0104
U 1 1 5EBC238B
P -4650 2200
F 0 "#PWR0104" H -4650 1950 50  0001 C CNN
F 1 "GNDS" H -4645 2027 50  0000 C CNN
F 2 "" H -4650 2200 50  0001 C CNN
F 3 "" H -4650 2200 50  0001 C CNN
	1    -4650 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDS #PWR0105
U 1 1 5EBC254F
P -3500 2850
F 0 "#PWR0105" H -3500 2600 50  0001 C CNN
F 1 "GNDS" H -3495 2677 50  0000 C CNN
F 2 "" H -3500 2850 50  0001 C CNN
F 3 "" H -3500 2850 50  0001 C CNN
	1    -3500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	-5650 2100 -5650 3150
Wire Wire Line
	-5650 3150 -4700 3150
Wire Wire Line
	-4700 3150 -4700 2850
Wire Wire Line
	-4700 2850 -4300 2850
Wire Wire Line
	-4300 2850 -4300 2600
Connection ~ -4700 2850
$Comp
L Device:R R3
U 1 1 5EBD5D7E
P -4150 2850
F 0 "R3" V -4050 2800 50  0000 L CNN
F 1 "FUSE" V -4150 2750 50  0000 L CNN
F 2 "OPL_Resistor:R0603" V -4220 2850 50  0001 C CNN
F 3 "~" H -4150 2850 50  0001 C CNN
	1    -4150 2850
	0    1    1    0   
$EndComp
Connection ~ -4300 2850
Wire Wire Line
	-4000 2850 -3700 2850
Text Label -3900 2850 0    50   ~ 0
SAMPWR
$EndSCHEMATC
