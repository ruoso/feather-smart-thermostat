EESchema Schematic File Version 4
LIBS:feather-smart-thermostat-cache
EELAYER 26 0
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
L Switch:SW_Push SW1
U 1 1 5F8CFD0F
P 3800 2150
F 0 "SW1" H 3800 2435 50  0000 C CNN
F 1 "Temp Up" H 3800 2344 50  0000 C CNN
F 2 "" H 3800 2350 50  0001 C CNN
F 3 "~" H 3800 2350 50  0001 C CNN
	1    3800 2150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5F8CFEF8
P 3800 1750
F 0 "SW3" H 3800 2035 50  0000 C CNN
F 1 "Function" H 3800 1944 50  0000 C CNN
F 2 "" H 3800 1950 50  0001 C CNN
F 3 "~" H 3800 1950 50  0001 C CNN
	1    3800 1750
	1    0    0    -1  
$EndComp
Entry Wire Line
	2650 2500 2750 2600
Entry Wire Line
	2650 2350 2750 2450
Entry Wire Line
	2650 2200 2750 2300
$Comp
L Switch:SW_Push SW2
U 1 1 5F8CF3EB
P 3800 2600
F 0 "SW2" H 3800 2885 50  0000 C CNN
F 1 "Temp Down" H 3800 2794 50  0000 C CNN
F 2 "" H 3800 2800 50  0001 C CNN
F 3 "~" H 3800 2800 50  0001 C CNN
	1    3800 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2600 2750 2600
Wire Wire Line
	2750 2300 3100 2300
Wire Wire Line
	3100 2300 3100 1750
Wire Wire Line
	2750 2450 3400 2450
Wire Wire Line
	3400 2450 3400 2150
Wire Wire Line
	3400 2150 3600 2150
Wire Wire Line
	3600 1750 3100 1750
Wire Wire Line
	5050 3050 2750 3050
Wire Wire Line
	6050 2750 8750 2750
Entry Wire Line
	8750 2750 8850 2850
Entry Wire Line
	2650 2950 2750 3050
$Comp
L feather-smart-thermostat-rescue:SHT3X-Adafruit_SHT31_Breakout-eagle-import U1
U 1 1 5F8F5E69
P 5550 2950
F 0 "U1" H 5579 2303 42  0000 C CNN
F 1 "SHT31-D" H 5579 2382 42  0000 C CNN
F 2 "" H 5550 2950 50  0001 C CNN
F 3 "" H 5550 2950 50  0001 C CNN
	1    5550 2950
	-1   0    0    1   
$EndComp
$Comp
L feather-smart-thermostat-rescue:FeatherHuzzahBoard-components U2
U 1 1 5F905B59
P 4700 4800
F 0 "U2" V 5915 3900 50  0000 C CNN
F 1 "FeatherHuzzahBoard" V 5824 3900 50  0000 C CNN
F 2 "" H 4800 3950 50  0001 C CNN
F 3 "" H 4250 4900 50  0001 C CNN
	1    4700 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 5100 8750 5100
Entry Wire Line
	8750 5100 8850 5200
Wire Wire Line
	5050 2950 4700 2950
Wire Wire Line
	4700 2950 4700 4000
Wire Wire Line
	4700 4000 4950 4000
Wire Wire Line
	5050 2850 4800 2850
Wire Wire Line
	4800 2850 4800 3900
Wire Wire Line
	4800 3900 4950 3900
Wire Wire Line
	6250 4800 6900 4800
Wire Wire Line
	6900 4800 6900 1950
Wire Wire Line
	6900 1950 4350 1950
Wire Wire Line
	4350 1950 4350 2600
Wire Wire Line
	4350 2600 4000 2600
Wire Wire Line
	7000 1850 4250 1850
Wire Wire Line
	4250 1850 4250 2150
Wire Wire Line
	4250 2150 4000 2150
Wire Wire Line
	7100 1750 4000 1750
$Comp
L feather-smart-thermostat-rescue:SingleRelayModuleD25-components RELAY?
U 1 1 5F91202D
P 6050 6700
F 0 "RELAY?" H 5928 6846 50  0000 L CNN
F 1 "SingleRelayModuleD25" H 5928 6755 50  0000 L CNN
F 2 "" H 6050 6700 50  0001 C CNN
F 3 "" H 6050 6700 50  0001 C CNN
	1    6050 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 6150 2750 6150
Wire Wire Line
	5750 6150 5750 6000
Wire Wire Line
	5750 6000 8750 6000
Wire Wire Line
	5850 6150 6800 6150
Wire Wire Line
	6800 6150 6800 3900
Wire Wire Line
	6800 3900 6250 3900
Entry Wire Line
	8750 6000 8850 6100
Entry Wire Line
	2650 6050 2750 6150
Text Label 5200 5250 0    50   ~ 0
BUSYSIGNAL
Wire Wire Line
	5300 5300 4700 5300
Wire Wire Line
	4700 5300 4700 4500
Wire Wire Line
	4700 4500 4950 4500
$Comp
L feather-smart-thermostat-rescue:CurrentSensor U?
U 1 1 5F8B457D
P 4400 5150
F 0 "U?" H 4528 3621 50  0000 L CNN
F 1 "CurrentSensor" H 4528 3530 50  0000 L CNN
F 2 "" H 4400 5150 50  0001 C CNN
F 3 "" H 4400 5150 50  0001 C CNN
	1    4400 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 6300 4200 5950
Wire Wire Line
	4200 5950 8750 5950
Wire Wire Line
	4400 6300 4400 6200
Wire Wire Line
	4400 6200 2750 6200
Wire Wire Line
	4300 6300 4300 5850
Wire Wire Line
	4300 5850 6700 5850
Wire Wire Line
	6700 5850 6700 4500
Wire Wire Line
	6700 4500 6250 4500
$Comp
L power:AC #PWR?
U 1 1 5F8B7DE8
P 4200 7350
F 0 "#PWR?" H 4200 7250 50  0001 C CNN
F 1 "AC" H 4200 7625 50  0000 C CNN
F 2 "" H 4200 7350 50  0001 C CNN
F 3 "" H 4200 7350 50  0001 C CNN
	1    4200 7350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 7350 4200 7150
$Comp
L feather-smart-thermostat-rescue:DiscThermostat S?
U 1 1 5F8B995B
P 5000 7400
F 0 "S?" H 5000 7515 50  0000 C CNN
F 1 "DiscThermostat" H 5000 7424 50  0000 C CNN
F 2 "" H 5000 7400 50  0001 C CNN
F 3 "" H 5000 7400 50  0001 C CNN
	1    5000 7400
	1    0    0    -1  
$EndComp
$Comp
L feather-smart-thermostat-rescue:DiscThermostat S?
U 1 1 5F8B99FD
P 6300 7400
F 0 "S?" H 6300 7515 50  0000 C CNN
F 1 "DiscThermostat" H 6300 7424 50  0000 C CNN
F 2 "" H 6300 7400 50  0001 C CNN
F 3 "" H 6300 7400 50  0001 C CNN
	1    6300 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 7550 4750 7550
Wire Wire Line
	5250 7550 5750 7550
Wire Wire Line
	5750 7550 6050 7550
Connection ~ 5750 7550
Wire Wire Line
	5650 7050 5650 7150
Wire Wire Line
	5650 7150 6750 7150
Wire Wire Line
	6750 7550 6550 7550
Wire Wire Line
	4400 7150 4400 7550
Wire Wire Line
	5750 7050 5750 7550
Wire Wire Line
	6750 7150 6750 7550
Connection ~ 6750 7150
Wire Wire Line
	6750 7000 6750 7150
$Comp
L power:AC #PWR?
U 1 1 5F8C2BAA
P 6750 7000
F 0 "#PWR?" H 6750 6900 50  0001 C CNN
F 1 "AC" H 6750 7275 50  0000 C CNN
F 2 "" H 6750 7000 50  0001 C CNN
F 3 "" H 6750 7000 50  0001 C CNN
	1    6750 7000
	1    0    0    -1  
$EndComp
Entry Wire Line
	8750 5950 8850 6050
Entry Wire Line
	2650 6100 2750 6200
Wire Wire Line
	6250 5300 6600 5300
Wire Wire Line
	6600 5300 6600 5750
Entry Wire Line
	2650 5650 2750 5750
Wire Wire Line
	2750 5750 6600 5750
Wire Wire Line
	7000 4700 7000 1850
Wire Wire Line
	6250 4700 7000 4700
Wire Wire Line
	7100 5000 6250 5000
Wire Wire Line
	7000 4700 7000 4900
Wire Wire Line
	7000 4900 6250 4900
Wire Bus Line
	8850 1700 8850 6700
Wire Bus Line
	2650 1850 2650 6500
Connection ~ 7000 4700
Wire Wire Line
	7100 1750 7100 5000
$EndSCHEMATC
