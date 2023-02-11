
#pragma once

/**
   Arduino Mega with RAMPS v1.4 pin assignments
*/
//
// Servos
//
#define SERVO0_PIN                        11
#define SERVO1_PIN                         6
#define SERVO2_PIN                         5
#define SERVO3_PIN                         4


//온도 센서
#define dht_sgl                           3

#define end_PIN                          2
#define z_min_pin                        14
#define Y_MAX_PIN                         15
#define Z_MIN_PIN                         18
#define Z_MAX_PIN                         19



//
// Steppers
//
#define X_STEP_PIN                         A0
#define X_DIR_PIN                          A1
#define X_ENABLE_PIN                       38
#define X_CS_PIN                           53

#define Y_STEP_PIN                         60
#define Y_DIR_PIN                          61
#define Y_ENABLE_PIN                       56
#define Y_CS_PIN                           49

#define Z_STEP_PIN                         46
#define Z_DIR_PIN                          48
#define Z_ENABLE_PIN                       62
#define Z_CS_PIN                           40


#define E0_STEP_PIN                        26
#define E0_DIR_PIN                         28
#define E0_ENABLE_PIN                      24
#define E0_CS_PIN                          42


#define E1_STEP_PIN                        36
#define E1_DIR_PIN                         34
#define E1_ENABLE_PIN                      30
#define E1_CS_PIN                          44


//
// Temperature Sensors
//

#define TEMP_0_PIN                         13  // Analog Input
#define TEMP_1_PIN                         15  // Analog Input
#define TEMP_BED_PIN                       14  // Analog Input

//
// Heaters / Fans
//
#define RAMPS_D8_PIN                        8
#define RAMPS_D9_PIN                        9
#define RAMPS_D10_PIN                                                                                          10


//
// I2C
//
#define SDA_PIN                           20 
#define SCL_PIN                           21 


//////////////////////////
// LCDs and Controllers //
//////////////////////////


// DOGM SPI LCD Support
#define DOGLCD_CS                       16
#define DOGLCD_MOSI                     17
#define DOGLCD_SCK                      23



// REPRAP_DISCOUNT_SMART_CONTROLLER
#define D31                             31  //BTN_EN1
#define D33                             33  // BTN_EN2
#define D35                             35  //BTN_ENC
#define BEEPER_PIN                      37 
#define SD_DETECT_PIN                   49 
#define KILL_PIN                        41
#define LCD_BACKLIGHT_PIN               39
