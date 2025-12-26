EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L Connector:DIN-5 MIDI_IN1
U 1 1 5CD18EFB
P -8150 -3550
F 0 "MIDI_IN1" V -8104 -3779 50  0000 R CNN
F 1 "DIN-5" V -8195 -3779 50  0000 R CNN
F 2 "CLRLibrary:DIN5_KCDX-5S-S2" H -8150 -3550 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H -8150 -3550 50  0001 C CNN
	1    -8150 -3550
	0    -1   1    0   
$EndComp
$Comp
L Isolator:6N138 U2
U 1 1 5CD1902B
P -6050 -3750
F 0 "U2" H -6050 -3283 50  0000 C CNN
F 1 "6N138" H -6050 -3374 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H -5760 -4050 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/HCPL2731-D.pdf" H -5760 -4050 50  0001 C CNN
	1    -6050 -3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5CD19228
P -7300 -4000
F 0 "R6" V -7507 -4000 50  0000 C CNN
F 1 "220" V -7416 -4000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V -7370 -4000 50  0001 C CNN
F 3 "~" H -7300 -4000 50  0001 C CNN
	1    -7300 -4000
	0    1    1    0   
$EndComp
Wire Wire Line
	-8250 -3850 -8250 -4000
Wire Wire Line
	-6350 -4000 -6350 -3850
Wire Wire Line
	-6350 -3650 -6350 -3100
Wire Wire Line
	-8250 -3100 -8250 -3250
$Comp
L SeeedOPL-Connector-2016:MICRO-USB-SMD-B-_10118193-0001LF_ USB1
U 1 1 5CD223C3
P -10350 -4600
F 0 "USB1" H -10325 -4146 45  0000 C CNN
F 1 "MICRO-USB-SMD-B-_10118193-0001LF_" H -10325 -4230 45  0000 C CNN
F 2 "SeeedOPL-Connector-2016:MICRO-USB5+6P-SMD-0.65-B" H -10350 -4600 50  0001 C CNN
F 3 "" H -10350 -4600 50  0001 C CNN
F 4 "10118193-0001LF" H -10320 -4450 20  0001 C CNN "MPN"
F 5 "320010003" H -10320 -4450 20  0001 C CNN "SKU"
	1    -10350 -4600
	1    0    0    -1  
$EndComp
$Comp
L SeeedOPL-Connector-2016:DIP-USB-B-TYPE-FMAL_4+2P-2.0-90D_ JP1
U 1 1 5CD22583
P -10000 -3600
F 0 "JP1" H -9272 -3642 45  0000 L CNN
F 1 "DIP-USB-B-TYPE-FMAL_4+2P-2.0-90D_" H -9272 -3558 45  0000 L CNN
F 2 "SeeedOPL-Connector-2016:USB4+2-2.5-90D-15.8X12MM" H -10000 -3600 50  0001 C CNN
F 3 "" H -10000 -3600 50  0001 C CNN
F 4 "320010018" H -9970 -3450 20  0001 C CNN "SKU"
	1    -10000 -3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	-10850 -4750 -10850 -4650
Wire Wire Line
	-10850 -4000 -10400 -4000
Connection ~ -10850 -4650
Wire Wire Line
	-10850 -4650 -10850 -4550
Connection ~ -10850 -4550
Wire Wire Line
	-10850 -4550 -10850 -4450
Connection ~ -10850 -4450
Wire Wire Line
	-10850 -4450 -10850 -4000
Wire Wire Line
	-10400 -4000 -9900 -4000
Wire Wire Line
	-9900 -4000 -9900 -3750
Connection ~ -10400 -4000
Wire Wire Line
	-10400 -3200 -10850 -3200
Wire Wire Line
	-10850 -3200 -10850 -4000
Connection ~ -10850 -4000
Wire Wire Line
	-9800 -4400 -9800 -4000
Wire Wire Line
	-9800 -4000 -9900 -4000
Connection ~ -9900 -4000
Wire Wire Line
	-9800 -4800 -9550 -4800
Wire Wire Line
	-9550 -4800 -9550 -3500
Wire Wire Line
	-9550 -3450 -9900 -3450
Wire Wire Line
	-9550 -4800 -8950 -4800
Wire Wire Line
	-5300 -4800 -5300 -4700
Connection ~ -9550 -4800
$Comp
L Device:R R10
U 1 1 5CD2370B
P -5300 -4550
F 0 "R10" V -5507 -4550 50  0000 C CNN
F 1 "1K" V -5416 -4550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V -5370 -4550 50  0001 C CNN
F 3 "~" H -5300 -4550 50  0001 C CNN
	1    -5300 -4550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 5CD23779
P -4950 -4550
F 0 "R11" V -5157 -4550 50  0000 C CNN
F 1 "220" V -5066 -4550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V -5020 -4550 50  0001 C CNN
F 3 "~" H -4950 -4550 50  0001 C CNN
	1    -4950 -4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	-5300 -4400 -5300 -3950
Wire Wire Line
	-5300 -3950 -5750 -3950
Wire Wire Line
	-4950 -4400 -4950 -3650
Wire Wire Line
	-4950 -3650 -5750 -3650
Wire Wire Line
	-5750 -2850 -8750 -2850
Wire Wire Line
	-10850 -2850 -10850 -3200
Connection ~ -10850 -3200
Text Label -9100 -4800 0    50   ~ 0
5V
Text Label -5450 -3650 0    50   ~ 0
MIDIIN
Text Label -9250 -2850 0    50   ~ 0
GND
$Comp
L Device:R R4
U 1 1 5CD302EC
P -8450 -2250
F 0 "R4" V -8657 -2250 50  0000 C CNN
F 1 "220" V -8566 -2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V -8520 -2250 50  0001 C CNN
F 3 "~" H -8450 -2250 50  0001 C CNN
	1    -8450 -2250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5CD302FA
P -8650 -1200
F 0 "R3" V -8857 -1200 50  0000 C CNN
F 1 "220" V -8766 -1200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V -8720 -1200 50  0001 C CNN
F 3 "~" H -8650 -1200 50  0001 C CNN
	1    -8650 -1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-8900 -1200 -8800 -1200
Wire Wire Line
	-8500 -1200 -8450 -1200
Wire Wire Line
	-8450 -2100 -8450 -2050
Wire Wire Line
	-8450 -2400 -10150 -2400
Text Label -10150 -2400 0    50   ~ 0
5V
$Comp
L power:GND #PWR01
U 1 1 5CD36A3D
P -5750 -2850
F 0 "#PWR01" H -5750 -3100 50  0001 C CNN
F 1 "GND" H -5745 -3023 50  0000 C CNN
F 2 "" H -5750 -2850 50  0001 C CNN
F 3 "" H -5750 -2850 50  0001 C CNN
	1    -5750 -2850
	1    0    0    -1  
$EndComp
Connection ~ -5750 -2850
$Comp
L Device:C C1
U 1 1 5CD36AA8
P -9550 -3300
F 0 "C1" H -9435 -3254 50  0000 L CNN
F 1 "C" H -9435 -3345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H -9512 -3450 50  0001 C CNN
F 3 "~" H -9550 -3300 50  0001 C CNN
	1    -9550 -3300
	1    0    0    -1  
$EndComp
Connection ~ -9550 -3450
$Comp
L Device:C C2
U 1 1 5CD36D77
P -9250 -3300
F 0 "C2" H -9135 -3254 50  0000 L CNN
F 1 "C" H -9135 -3345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H -9212 -3450 50  0001 C CNN
F 3 "~" H -9250 -3300 50  0001 C CNN
	1    -9250 -3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	-9550 -3500 -9250 -3500
Wire Wire Line
	-9250 -3500 -9250 -3450
Connection ~ -9550 -3500
Wire Wire Line
	-9550 -3500 -9550 -3450
Wire Wire Line
	-9550 -3150 -9550 -2850
Connection ~ -9550 -2850
Wire Wire Line
	-9550 -2850 -10850 -2850
Wire Wire Line
	-9250 -3150 -9250 -2850
Connection ~ -9250 -2850
Wire Wire Line
	-9250 -2850 -9550 -2850
Text Label -8350 -2850 0    50   ~ 0
Gnd
Text Label -7900 -4800 0    50   ~ 0
Vcc
Wire Wire Line
	-7150 -4000 -6350 -4000
$Comp
L Connector_Generic:Conn_02x03_Counter_Clockwise CHAN1
U 1 1 5CDB337A
P -4700 -850
F 0 "CHAN1" H -4650 -533 50  0000 C CNN
F 1 "JBlock" H -4650 -624 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H2X3-2.54" H -4700 -850 50  0001 C CNN
F 3 "~" H -4700 -850 50  0001 C CNN
	1    -4700 -850
	0    1    1    0   
$EndComp
$Comp
L Interface_UART:ST485EBDR U1
U 1 1 5FBE46F3
P -4250 -2050
F 0 "U1" H -4250 -1472 50  0000 C CNN
F 1 "ST485EBDR" H -4250 -1563 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H -4250 -2950 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H -4250 -2000 50  0001 C CNN
	1    -4250 -2050
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J1
U 1 1 5FC062E5
P -6700 -800
F 0 "J1" H -6645 -133 50  0000 C CNN
F 1 "RJ45" H -6645 -224 50  0000 C CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V -6700 -775 50  0001 C CNN
F 3 "~" V -6700 -775 50  0001 C CNN
	1    -6700 -800
	1    0    0    -1  
$EndComp
Wire Wire Line
	-4800 -1050 -4800 -1200
Wire Wire Line
	-4800 -1200 -5350 -1200
Wire Wire Line
	-5900 -1200 -5900 -700
Wire Wire Line
	-5900 -700 -6300 -700
Wire Wire Line
	-6300 -900 -5950 -900
Wire Wire Line
	-5950 -900 -5950 -1250
Wire Wire Line
	-5950 -1250 -5300 -1250
Wire Wire Line
	-4600 -1250 -4600 -1050
Wire Wire Line
	-4800 -550 -4800 -450
Wire Wire Line
	-4800 -450 -5750 -450
Wire Wire Line
	-5750 -450 -5750 -800
Wire Wire Line
	-5750 -800 -6300 -800
Wire Wire Line
	-6300 -1000 -5700 -1000
Wire Wire Line
	-5700 -1000 -5700 -500
Wire Wire Line
	-5700 -500 -4600 -500
Wire Wire Line
	-4600 -500 -4600 -550
Wire Wire Line
	-4700 -1050 -4700 -1350
Wire Wire Line
	-3600 -1350 -3600 -1850
Wire Wire Line
	-3600 -1850 -3850 -1850
Wire Wire Line
	-3850 -2150 -3450 -2150
Wire Wire Line
	-3450 -2150 -3450 -350
Wire Wire Line
	-3450 -350 -4700 -350
Wire Wire Line
	-4700 -350 -4700 -550
Wire Wire Line
	-4950 -1850 -4650 -1850
Connection ~ -4950 -3650
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5FC27C4B
P -9450 -500
F 0 "Q1" H -9245 -454 50  0000 L CNN
F 1 "2N7002" H -9245 -545 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H -9250 -575 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H -9450 -500 50  0001 L CNN
	1    -9450 -500
	1    0    0    -1  
$EndComp
Text Label -6200 -500 0    50   ~ 0
5V
Text Label -6200 -600 0    50   ~ 0
GND
$Comp
L Regulator_Linear:AP1117-33 U3
U 1 1 5FC28620
P -3600 -3150
F 0 "U3" H -3600 -2908 50  0000 C CNN
F 1 "AP1117-33" H -3600 -2999 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H -3600 -2950 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/AP1117.pdf" H -3500 -3400 50  0001 C CNN
	1    -3600 -3150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 5V1
U 1 1 5FC28A0C
P -8400 -5250
F 0 "5V1" H -8320 -5208 50  0000 L CNN
F 1 "Conn_01x01" H -8320 -5299 50  0000 L CNN
F 2 "CLRLibrary:KK156-1" H -8400 -5250 50  0001 C CNN
F 3 "~" H -8400 -5250 50  0001 C CNN
	1    -8400 -5250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 GND1
U 1 1 5FC28AE8
P -8400 -5100
F 0 "GND1" H -8320 -5058 50  0000 L CNN
F 1 "Conn_01x01" H -8320 -5149 50  0000 L CNN
F 2 "CLRLibrary:KK156-1" H -8400 -5100 50  0001 C CNN
F 3 "~" H -8400 -5100 50  0001 C CNN
	1    -8400 -5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	-7750 -4000 -7450 -4000
Connection ~ -7750 -4000
Connection ~ -7650 -3100
Wire Wire Line
	-7650 -4250 -7650 -3100
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 5CD19114
P -7650 -4450
F 0 "J10" V -7590 -4410 50  0000 L CNN
F 1 "Conn_01x02_Male" V -7499 -4410 50  0000 L CNN
F 2 "SeeedOPL-Connector-2016:H2-2.54" H -7650 -4450 50  0001 C CNN
F 3 "~" H -7650 -4450 50  0001 C CNN
	1    -7650 -4450
	0    1    1    0   
$EndComp
Wire Wire Line
	-7650 -3100 -6350 -3100
Wire Wire Line
	-7750 -4250 -7750 -4000
Wire Wire Line
	-5100 -2050 -4650 -2050
Wire Wire Line
	-4650 -1950 -5100 -1950
Wire Wire Line
	-5100 -1950 -5100 -2050
Connection ~ -5100 -2050
$Comp
L power:GND #PWR03
U 1 1 5FC51124
P -4250 -1550
F 0 "#PWR03" H -4250 -1800 50  0001 C CNN
F 1 "GND" H -4245 -1723 50  0000 C CNN
F 2 "" H -4250 -1550 50  0001 C CNN
F 3 "" H -4250 -1550 50  0001 C CNN
	1    -4250 -1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	-6300 -600 -5900 -600
Wire Wire Line
	-6300 -500 -5900 -500
Wire Wire Line
	-3300 -3150 -3100 -3150
Wire Wire Line
	-3100 -3150 -3100 -2450
Wire Wire Line
	-3100 -2450 -4250 -2450
Connection ~ -4250 -2450
Text Label -4000 -3150 0    50   ~ 0
5V
Wire Wire Line
	-3900 -3150 -4200 -3150
Wire Wire Line
	-5750 -3550 -5750 -2850
Wire Wire Line
	-3100 -4700 -3100 -3650
Connection ~ -3100 -3150
$Comp
L Device:C C3
U 1 1 5FC7B1DD
P -3000 -2300
F 0 "C3" H -2885 -2254 50  0000 L CNN
F 1 "C" H -2885 -2345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H -2962 -2450 50  0001 C CNN
F 3 "~" H -3000 -2300 50  0001 C CNN
	1    -3000 -2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5FC7B1E3
P -2700 -2300
F 0 "C4" H -2585 -2254 50  0000 L CNN
F 1 "C" H -2585 -2345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H -2662 -2450 50  0001 C CNN
F 3 "~" H -2700 -2300 50  0001 C CNN
	1    -2700 -2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	-3000 -2150 -3000 -1450
Wire Wire Line
	-2700 -1350 -3000 -1350
Wire Wire Line
	-2700 -2150 -2700 -1350
Wire Wire Line
	-3000 -2450 -3100 -2450
Connection ~ -3100 -2450
Connection ~ -3000 -2450
Wire Wire Line
	-2700 -2450 -3000 -2450
Wire Wire Line
	-4950 -4700 -3100 -4700
$Comp
L Connector_Generic:Conn_01x03 Pol1
U 1 1 5FC900CD
P -8050 -650
F 0 "Pol1" H -8130 -333 50  0000 C CNN
F 1 "Conn_01x03" H -8130 -424 50  0000 C CNN
F 2 "CLRConnector:H3-2.54" H -8050 -650 50  0001 C CNN
F 3 "~" H -8050 -650 50  0001 C CNN
	1    -8050 -650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	-7550 -750 -7850 -750
Wire Wire Line
	-7850 -650 -7600 -650
Wire Wire Line
	-7600 -650 -7600 -350
Wire Wire Line
	-7600 -350 -8900 -350
Wire Wire Line
	-8900 -350 -8900 -1200
Wire Wire Line
	-7850 -550 -7850 -400
Wire Wire Line
	-7850 -400 -8650 -400
Wire Wire Line
	-8650 -400 -8650 -700
Wire Wire Line
	-8650 -700 -9350 -700
Wire Wire Line
	-7550 -1000 -9050 -1000
Wire Wire Line
	-9650 -1000 -9650 -500
Wire Wire Line
	-7550 -1000 -7550 -750
$Comp
L power:GND #PWR02
U 1 1 5FCAD2AB
P -9350 -300
F 0 "#PWR02" H -9350 -550 50  0001 C CNN
F 1 "GND" H -9345 -473 50  0000 C CNN
F 2 "" H -9350 -300 50  0001 C CNN
F 3 "" H -9350 -300 50  0001 C CNN
	1    -9350 -300
	1    0    0    -1  
$EndComp
Wire Wire Line
	-8450 -1450 -8450 -1200
$Comp
L power:GND #PWR04
U 1 1 5FCBEBE2
P -3600 -2850
F 0 "#PWR04" H -3600 -3100 50  0001 C CNN
F 1 "GND" H -3595 -3023 50  0000 C CNN
F 2 "" H -3600 -2850 50  0001 C CNN
F 3 "" H -3600 -2850 50  0001 C CNN
	1    -3600 -2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	-8600 -5250 -8950 -5250
Wire Wire Line
	-8950 -5250 -8950 -4800
Connection ~ -8950 -4800
Wire Wire Line
	-8950 -4800 -5300 -4800
Wire Wire Line
	-8600 -5100 -8750 -5100
Wire Wire Line
	-8750 -5100 -8750 -2850
Connection ~ -8750 -2850
Wire Wire Line
	-8750 -2850 -9250 -2850
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5FCC794B
P -3500 -3850
F 0 "J2" V -3440 -3810 50  0000 L CNN
F 1 "Conn_01x02_Male" V -3349 -3810 50  0000 L CNN
F 2 "SeeedOPL-Connector-2016:H2-2.54" H -3500 -3850 50  0001 C CNN
F 3 "~" H -3500 -3850 50  0001 C CNN
	1    -3500 -3850
	0    1    1    0   
$EndComp
Wire Wire Line
	-4200 -3650 -3600 -3650
Wire Wire Line
	-4200 -3650 -4200 -3150
Wire Wire Line
	-3500 -3650 -3100 -3650
Connection ~ -3100 -3650
Wire Wire Line
	-3100 -3650 -3100 -3150
$Comp
L power:GND #PWR0101
U 1 1 5FCDABBA
P -3000 -1350
F 0 "#PWR0101" H -3000 -1600 50  0001 C CNN
F 1 "GND" H -2995 -1523 50  0000 C CNN
F 2 "" H -3000 -1350 50  0001 C CNN
F 3 "" H -3000 -1350 50  0001 C CNN
	1    -3000 -1350
	1    0    0    -1  
$EndComp
Connection ~ -3000 -1350
Wire Wire Line
	-3600 -1350 -4700 -1350
$Comp
L Connector_Generic:Conn_02x03_Counter_Clockwise CHAN2
U 1 1 5FBDAAC4
P -6800 0
F 0 "CHAN2" H -6750 317 50  0000 C CNN
F 1 "JBlock" H -6750 226 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H2X3-2.54" H -6800 0   50  0001 C CNN
F 3 "~" H -6800 0   50  0001 C CNN
	1    -6800 0   
	-1   0    0    1   
$EndComp
Wire Wire Line
	-6600 100  -5300 100 
Wire Wire Line
	-5300 100  -5300 -1250
Connection ~ -5300 -1250
Wire Wire Line
	-5300 -1250 -4600 -1250
Wire Wire Line
	-5350 -1200 -5350 -100
Wire Wire Line
	-5350 -100 -6600 -100
Connection ~ -5350 -1200
Wire Wire Line
	-5350 -1200 -5900 -1200
Wire Wire Line
	-7100 -100 -7100 -300
Wire Wire Line
	-7100 -300 -5750 -300
Wire Wire Line
	-5750 -300 -5750 -450
Connection ~ -5750 -450
Wire Wire Line
	-5700 -500 -5700 -350
Wire Wire Line
	-5700 -350 -7200 -350
Wire Wire Line
	-7200 -350 -7200 100 
Wire Wire Line
	-7200 100  -7100 100 
Connection ~ -5700 -500
$Comp
L Interface_UART:ST485EBDR U4
U 1 1 5FBF51ED
P -7950 650
F 0 "U4" H -7950 1228 50  0000 C CNN
F 1 "ST485EBDR" H -7950 1137 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H -7950 -250 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H -7950 700 50  0001 C CNN
	1    -7950 650 
	1    0    0    -1  
$EndComp
Wire Wire Line
	-7550 850  -6550 850 
Wire Wire Line
	-6550 850  -6550 0   
Wire Wire Line
	-6550 0    -6600 0   
Wire Wire Line
	-7550 550  -7350 550 
Wire Wire Line
	-7350 550  -7350 0   
Wire Wire Line
	-7350 0    -7100 0   
Wire Wire Line
	-4950 -3650 -4950 -1850
Wire Wire Line
	-4650 -2150 -5100 -2150
Connection ~ -5100 -2150
Wire Wire Line
	-5100 -2150 -5100 -2050
Wire Wire Line
	-5100 -2450 -5100 -2150
Wire Wire Line
	-5100 -2450 -4250 -2450
$Comp
L Device:C C5
U 1 1 5FC1BE59
P -2300 -2300
F 0 "C5" H -2185 -2254 50  0000 L CNN
F 1 "C" H -2185 -2345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H -2262 -2450 50  0001 C CNN
F 3 "~" H -2300 -2300 50  0001 C CNN
	1    -2300 -2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	-2300 -2450 -2700 -2450
Connection ~ -2700 -2450
Wire Wire Line
	-2300 -2150 -2300 -1350
Wire Wire Line
	-2300 -1350 -2700 -1350
Connection ~ -2700 -1350
Wire Wire Line
	-7950 1150 -8500 1150
Wire Wire Line
	-8500 1150 -8500 850 
Wire Wire Line
	-8500 750  -8350 750 
Wire Wire Line
	-8350 650  -8500 650 
Wire Wire Line
	-8500 650  -8500 750 
Connection ~ -8500 750 
Wire Wire Line
	-8350 850  -8500 850 
Connection ~ -8500 850 
Wire Wire Line
	-8500 850  -8500 750 
$Comp
L power:GND #PWR0102
U 1 1 5FC37967
P -7950 1150
F 0 "#PWR0102" H -7950 900 50  0001 C CNN
F 1 "GND" H -7945 977 50  0000 C CNN
F 2 "" H -7950 1150 50  0001 C CNN
F 3 "" H -7950 1150 50  0001 C CNN
	1    -7950 1150
	1    0    0    -1  
$EndComp
Connection ~ -7950 1150
Wire Wire Line
	-8350 550  -9650 550 
Wire Wire Line
	-9650 550  -9650 -500
Connection ~ -9650 -500
$Comp
L Connector:DIN-5 MIDI_OUT1
U 1 1 5FC43BF7
P -7100 -2000
F 0 "MIDI_OUT1" V -7054 -2229 50  0000 R CNN
F 1 "DIN-5" V -7145 -2229 50  0000 R CNN
F 2 "CLRLibrary:DIN5_KCDX-5S-S2" H -7100 -2000 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H -7100 -2000 50  0001 C CNN
	1    -7100 -2000
	0    -1   1    0   
$EndComp
Wire Wire Line
	-8250 -4000 -7750 -4000
Wire Wire Line
	-7200 -2300 -8000 -2300
Wire Wire Line
	-8000 -2300 -8000 -2050
Wire Wire Line
	-8000 -2050 -8450 -2050
Wire Wire Line
	-8250 -3100 -7650 -3100
Wire Wire Line
	-7200 -1450 -7200 -1700
Wire Wire Line
	-8450 -1450 -7200 -1450
$Comp
L power:GND #PWR0103
U 1 1 5FC554C0
P -7400 -2000
F 0 "#PWR0103" H -7400 -2250 50  0001 C CNN
F 1 "GND" H -7395 -2173 50  0000 C CNN
F 2 "" H -7400 -2000 50  0001 C CNN
F 3 "" H -7400 -2000 50  0001 C CNN
	1    -7400 -2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	-7950 250  -7950 200 
Wire Wire Line
	-7950 200  -2000 200 
Wire Wire Line
	-2000 200  -2000 -2450
Wire Wire Line
	-2000 -2450 -2300 -2450
Connection ~ -2300 -2450
$Comp
L Connector_Generic:Conn_02x06_Odd_Even SERIN?
U 1 1 600B5F78
P -5950 -2000
F 0 "SERIN?" H -5900 -1583 50  0000 C CNN
F 1 "Conn_02x06_Odd_Even" H -5900 -1674 50  0000 C CNN
F 2 "CLRLibrary:RibbonCableSocket_12_OddEven" H -5950 -2000 50  0001 C CNN
F 3 "~" H -5950 -2000 50  0001 C CNN
	1    -5950 -2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 600B6934
P -5100 -2650
F 0 "J?" V -5040 -2610 50  0000 L CNN
F 1 "Conn_01x02_Male" V -4949 -2610 50  0000 L CNN
F 2 "SeeedOPL-Connector-2016:H2-2.54" H -5100 -2650 50  0001 C CNN
F 3 "~" H -5100 -2650 50  0001 C CNN
	1    -5100 -2650
	0    1    1    0   
$EndComp
Connection ~ -5100 -2450
Wire Wire Line
	-5200 -1900 -5200 -2450
Wire Wire Line
	-5650 -1900 -5200 -1900
$Comp
L Connector_Generic:Conn_02x03_Counter_Clockwise SER?
U 1 1 600C5304
P -9350 -1750
F 0 "SER?" H -9300 -1433 50  0000 C CNN
F 1 "JBlock" H -9300 -1524 50  0000 C CNN
F 2 "SeeedOPL-Connector-2016:H2X3-2.54" H -9350 -1750 50  0001 C CNN
F 3 "~" H -9350 -1750 50  0001 C CNN
	1    -9350 -1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	-5650 -2100 -5350 -2100
Wire Wire Line
	-5650 -2200 -5500 -2200
Wire Wire Line
	-5500 -2200 -5500 -1450
Wire Wire Line
	-5500 -1450 -3000 -1450
Connection ~ -3000 -1450
Wire Wire Line
	-3000 -1450 -3000 -1350
Wire Wire Line
	-5650 -2000 -5350 -2000
Wire Wire Line
	-5650 -1800 -5350 -1800
Wire Wire Line
	-5650 -1700 -5350 -1700
Text Label -5400 -2100 0    50   ~ 0
RX4
Text Label -5400 -2000 0    50   ~ 0
TX4
Text Label -5400 -1800 0    50   ~ 0
RX5
Text Label -5400 -1700 0    50   ~ 0
TX5
Wire Wire Line
	-9150 -1650 -8850 -1650
Text Label -9100 -1850 0    50   ~ 0
RX5
Text Label -9850 -1850 0    50   ~ 0
TX5
Wire Wire Line
	-9950 -1750 -9650 -1750
Wire Wire Line
	-9950 -1650 -9650 -1650
Wire Wire Line
	-9650 -1850 -9950 -1850
Wire Wire Line
	-9150 -1850 -8850 -1850
Text Label -9100 -1650 0    50   ~ 0
RX4
Text Label -9850 -1650 0    50   ~ 0
TX4
Text Label -9950 -1750 0    50   ~ 0
MIDIIN
Wire Wire Line
	-9050 -1000 -9050 -1450
Wire Wire Line
	-9050 -1450 -8650 -1450
Wire Wire Line
	-8650 -1450 -8650 -1750
Wire Wire Line
	-9150 -1750 -8650 -1750
Connection ~ -9050 -1000
Wire Wire Line
	-9050 -1000 -9650 -1000
$EndSCHEMATC
