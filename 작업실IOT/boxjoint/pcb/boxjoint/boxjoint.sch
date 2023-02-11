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
L Driver_Motor:Pololu_Breakout_A4988 A?
U 1 1 613C6A6E
P 4575 3525
F 0 "A?" H 4550 4400 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 4375 4300 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 4850 2775 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 4675 3225 50  0001 C CNN
	1    4575 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	4175 3125 4075 3125
Wire Wire Line
	4075 3125 4075 3225
Wire Wire Line
	4075 3225 4175 3225
$Comp
L Switch:SW_Push SW?
U 1 1 613C9103
P 4575 4850
F 0 "SW?" H 4575 5135 50  0000 C CNN
F 1 "SW_Push" H 4575 5044 50  0000 C CNN
F 2 "" H 4575 5050 50  0001 C CNN
F 3 "~" H 4575 5050 50  0001 C CNN
	1    4575 4850
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 613CB04D
P 6175 3525
F 0 "J?" H 6300 3525 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 5975 3275 50  0000 L CNN
F 2 "" H 6175 3525 50  0001 C CNN
F 3 "~" H 6175 3525 50  0001 C CNN
	1    6175 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	4775 4325 4775 4400
Wire Wire Line
	5600 4400 5975 3625
Wire Wire Line
	4775 2825 5600 2825
Wire Wire Line
	5600 2825 5975 3525
$Comp
L Motor:Stepper_Motor_bipolar M?
U 1 1 613CD601
P 5600 3225
F 0 "M?" V 5568 3037 50  0000 R CNN
F 1 "Stepper_Motor_bipolar" V 5477 3037 50  0000 R CNN
F 2 "" H 5610 3215 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 5610 3215 50  0001 C CNN
	1    5600 3225
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5300 3325 5300 3525
Wire Wire Line
	5300 3525 5075 3525
Wire Wire Line
	5300 3125 5225 3125
Wire Wire Line
	5225 3125 5225 3425
Wire Wire Line
	5225 3425 5075 3425
Wire Wire Line
	5075 3725 5700 3725
Wire Wire Line
	5700 3725 5700 3525
Wire Wire Line
	5500 3525 5500 3625
Wire Wire Line
	5500 3625 5075 3625
$Comp
L Connector:Conn_01x15_Male J?
U 1 1 613D2645
P 3325 3575
F 0 "J?" H 3433 4456 50  0000 C CNN
F 1 "Conn_01x15_Male" H 3433 4365 50  0000 C CNN
F 2 "" H 3325 3575 50  0001 C CNN
F 3 "~" H 3325 3575 50  0001 C CNN
	1    3325 3575
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x15_Male J?
U 1 1 613E2588
P 2625 3600
F 0 "J?" H 2733 4481 50  0000 C CNN
F 1 "Conn_01x15_Male" H 2733 4390 50  0000 C CNN
F 2 "" H 2625 3600 50  0001 C CNN
F 3 "~" H 2625 3600 50  0001 C CNN
	1    2625 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4175 3525 3825 3525
Wire Wire Line
	3825 3525 3825 2875
Wire Wire Line
	3825 2875 3525 2875
Wire Wire Line
	3525 2975 3700 2975
Wire Wire Line
	3700 2975 3700 3625
Wire Wire Line
	3700 3625 4175 3625
Wire Wire Line
	3175 3500 2825 3500
Wire Wire Line
	4575 4650 3175 4650
Wire Wire Line
	3175 4650 3175 3500
Wire Wire Line
	4575 5050 3000 5050
Wire Wire Line
	3000 5050 3000 3600
Wire Wire Line
	3000 3600 2825 3600
Wire Wire Line
	4175 3825 4175 3925
Connection ~ 4175 3925
Wire Wire Line
	4175 3925 4175 4025
Wire Wire Line
	4175 3925 3900 3925
Wire Wire Line
	3900 3925 3900 3900
$Comp
L power:+5V #PWR?
U 1 1 613F2997
P 3900 3900
F 0 "#PWR?" H 3900 3750 50  0001 C CNN
F 1 "+5V" H 3915 4073 50  0000 C CNN
F 2 "" H 3900 3900 50  0001 C CNN
F 3 "" H 3900 3900 50  0001 C CNN
	1    3900 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4775 4400 5600 4400
Wire Wire Line
	4575 2825 4575 2575
Wire Wire Line
	4575 2575 6975 2575
Wire Wire Line
	6975 2575 6975 4525
Wire Wire Line
	6975 4525 3800 4525
Wire Wire Line
	3800 4525 3800 4175
Wire Wire Line
	3800 4175 3525 4175
Wire Wire Line
	4575 4325 3275 4325
Wire Wire Line
	3275 4325 3275 2900
Wire Wire Line
	3275 2900 2825 2900
Wire Wire Line
	2825 3700 2900 3700
Wire Wire Line
	2900 3700 2900 5425
$Comp
L Device:LED D?
U 1 1 613F8617
P 2900 5575
F 0 "D?" V 2939 5457 50  0000 R CNN
F 1 "LED" V 2848 5457 50  0000 R CNN
F 2 "" H 2900 5575 50  0001 C CNN
F 3 "~" H 2900 5575 50  0001 C CNN
	1    2900 5575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2825 3000 2500 3000
Wire Wire Line
	2500 3000 2500 5950
Wire Wire Line
	2500 5950 2900 5950
Wire Wire Line
	2900 5950 2900 5725
$EndSCHEMATC
