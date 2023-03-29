#ifndef __GITA_H__
#define __GITA_H__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ClickEncoder.h"
///http://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html 그래픽 라이브러리 레퍼런스
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset p in # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ClickEncoder *encoder;

int all_data_time = 0;
bool Running = false;
bool memu_set_value = true;
uint8_t toogle = 0;
bool hours_set = true;
int hours_72 = 1;
int minute_60 = 0;
int now_work_time = 0;
int all_work_time = 0;
int work_time;
int rest_time ;
int real_now_work_time = 0;

int bun;


#endif
