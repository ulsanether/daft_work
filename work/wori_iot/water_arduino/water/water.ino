  //사용 하기 전에 타이머 리셋 한번 동시에 할 것.
#include "gita.h"
#include "Water_pump.h"
#include <RTClib.h>
#include "Eeprom.h"
#define SETUP_T 1                  //타임 리셋 방식은 2
RTC_DS1307 RTC;



bool toogle_motor;
void setup() {
  Serial.begin(9600);
  Serial.println(11111);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(4, HIGH);
  encoder = new ClickEncoder(11, 10, 9);
  RTC.begin();
#if SETUP_T == 1
  Serial.println("first_debug_mode");

  EEPROMWrite(0, 0);
  EEPROMWrite(1, 1);
  EEPROMWrite(2, 2);
  EEPROMWrite(3, 3);
   RTC.adjust(DateTime(2022, 4, 1, 0, 0, 0));
#endif
#if SETUP_T == 2
  RTC.adjust(DateTime(2022, 4, 1, 0, 0, 0));  //무조선 리셋 스타일vb 
#endif
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(2221);

  ////////////////eeprom 셋업
  motor_pwm_power = EEPROMRead(0);  //모터 파워 셋업
  hours_72 = EEPROMRead(1);
  all_work_time = hours_72 * 60;
  minute_60 = EEPROMRead(2);
  now_work_time = minute_60 / 60;
  bun = minute_60 % 60;
  delay(1000);
  
  display.clearDisplay();
  display.display();
  noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = round(16000000 / 1024 / 1000);  // compare match register e.g. 16MHz/1024/100Hz
  TCCR2B |= (1 << WGM12);                 // CTC mode
  TCCR2B |= (1 << CS12) | (1 << CS10);    // 1024 prescaler
  TIMSK2 |= (1 << OCIE2A);                // enable timer compare interrupt
  interrupts();
}

ISR(TIMER2_COMPA_vect) {
  encoder->service();
}

int encoder_value() {  //엔코더 위치 값
  static int value;
  value += encoder->getValue();
  if (value < 0) {
    value = 0;
  } else if (value > 1) {
    value = 1;
    //Serial.print("button 2: ");
    //Serial.println(value);
  }
  return value;
}



void loop() {
  int now_time = getRtcTime();
  now_algo(now_time);
  int loop_set = encoder_value();
  int units = 0;
  static uint8_t menu_redraw_required = 3;  //메뉴 다시 그리기
  ClickEncoder::Button b = encoder->getButton();

  if (b != ClickEncoder::Open && memu_set_value == true) {
    switch (b) {
      case ClickEncoder::Clicked:  //클릭 함수
        // Serial.print("클릭 : ");   //값
        units = loop_set + 1;
        Running = true;
        break;
      case ClickEncoder::Pressed:
        units = loop_set + 1;
        Running = true;
        break;
      case ClickEncoder::DoubleClicked:
        units = loop_set + 1;
        Running = true;
        break;
    }
  }

  if (Running == true) {  //running가 참일때
    basic_display(0);
    //Serial.println("RunningMenu");
    switch (units) {
      case 1:
        Running = false;
        memu_set_value = false;
        //Serial.println("time_set");
        time_set();
        break;
      case 2:
        Running = false;
        memu_set_value = false;
        // Serial.println("motor_pow");
        motor_pow();
        //출력 설정 ui로
        break;
    }
  } else {
    if (menu_redraw_required != loop_set) {
      basic_display(0);
      //Serial.print("drawMenu");
      drawMenu(loop_set);               //메뉴 그리고
      menu_redraw_required = loop_set;  //메뉴값 다시 0으로
    }
  }
}





void time_set() {

  uint8_t value_act = 125;
  uint8_t value_act1 = 125;
  display.writeFillRect(1, 17, 118, 63 - 17, SSD1306_BLACK);
  bool time_set_toogle = true;
  int break_time = 2;

  while (break_time > 0) {
    value_act += encoder->getValue();
    if (value_act > value_act1) {
      if (hours_set == true) {
        hours_72++;
      } else if (hours_set == false) {
        minute_60 += 1;
      }
      value_act = 125;
    } else if (value_act < value_act1) {
      if (hours_set == true) {
        hours_72--;
      } else if (hours_set == false) {
        minute_60 -= 1;
      }
      value_act = 125;
    }

    all_work_time = hours_72 * 60;

    int sigan = minute_60 / 60;
    bun = minute_60 % 60;
    if (minute_60 > all_work_time) {
      minute_60 = 0;
    } else if (minute_60 < 0) {
      minute_60 = all_work_time;
    }
    now_work_time = minute_60 / 60;
    bun = minute_60 % 60;

    if (hours_72 < 1) {
      hours_72 = 72;
    } else if (hours_72 > 72) {
      hours_72 = 1;
    }
    basic_display(1);
    ClickEncoder::Button a = encoder->getButton();
    if (a != ClickEncoder::Open) {
      if (ClickEncoder::Clicked == a) {
        if (toogle == 1) {
          hours_set = true;
          // Serial.println(111);
          toogle = 0;
        } else {
          // Serial.println(222);
          hours_set = false;
          toogle = 1;
        }
        break_time--;
      }
    }
  }
  EEPROMWrite(1, hours_72);
  EEPROMWrite(2, minute_60);
  display.clearDisplay();
  basic_display(0);
  drawMenu(0);
  memu_set_value = true;
}


void motor_pow() {
  uint8_t value_act = 125;
  uint8_t value_act1 = 125;

  display.writeFillRect(1, 17, 118, 63 - 17, SSD1306_BLACK);
  bool break_time = true;
  
  while (break_time == true) {

    value_act += encoder->getValue();
    basic_display(2);  //반복 되면 더 그리지 말것
    if (value_act > value_act1) {
      motor_pwm_power++;
      if (motor_pwm_power > 10) {
        motor_pwm_power = 10;
      }
      value_act = 125;
    } else if (value_act < value_act1) {
      motor_pwm_power--;
      if (motor_pwm_power < 0) {
        motor_pwm_power = 0;
      }
      value_act = 125;
    }
    ClickEncoder::Button a = encoder->getButton();

    if (a != ClickEncoder::Open) {
      if (ClickEncoder::Clicked == a) {
        break_time = false;
        //파워 적재 하고 메인 메뉴로 이동
      }
    }
  }

  EEPROMWrite(0, motor_pwm_power);
  display.clearDisplay();
  basic_display(0);
  drawMenu(1);
  memu_set_value = true;
}

void basic_display(int i) {

  DateTime now = RTC.now();
  
  if (i == 0) {  //루트 디스플레이
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);  // Start at top-left corner
    display.print("Time ");   //설정 시간
    display.print(hours_72);
    display.print(" = ");         //설정 시간
    display.print(now_work_time);  //작동할 시간 단위
    display.print(":");            //설정 시간
    display.print(bun);            //작동할 분 단위
    display.print(" [");
    display.print(((now.day() * 24) * 60) + ((now.hour() * 60)) + now.minute() - 1440); //현재 시간 
    display.println("]");
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
    display.print(" Power  ");
    display.print(motor_pwm_power);
    display.drawRect(0, 16, 120, 64 - 16, WHITE);
    //display.drawLine(0,16,120,64,WHITE); //파란선 노란선 경계
    display.display();  //화면에 출력

  } else if (i == 1) {  //타임셋 디스플레이

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(SSD1306_WHITE);
    display.drawRect(0, 16, 120, 64 - 16, WHITE);
    display.drawFastHLine(0, 38, 120, WHITE);
    display.setTextSize(2);
    display.setCursor(2, 0);
    if (hours_set == true) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
      display.print(hours_72);                             //설정 시간
      display.print(" to ");                               //설정 시간
      display.print(all_work_time);                        //설정 시간
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 20);
      display.print("m|   ");
      display.print(minute_60);  //총 작동 시간 +분
      display.setCursor(10, 44);
      display.print("h| ");          //설정 시간
      display.print(now_work_time);  //작동할 시간 단위
      display.print(":");            //설정 시간
      display.print(bun);            //작동할 분 단위
    } else {
      display.setTextColor(SSD1306_WHITE);
      display.print(hours_72);       //설정 시간
      display.print(" to ");         //설정 시간
      display.print(all_work_time);  //설정 시간
      display.setCursor(10, 20);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
      display.print("m|   ");
      display.print(minute_60);  //총 작동 시간 +분
      display.setCursor(10, 44);
      display.print("h| ");          //설정 시간
      display.print(now_work_time);  //작동할 시간 단위
      display.print(":");            //설정 시간
      display.print(bun);            //작동할 분 단위
    }
  } else if (i == 2) {  //파워 디스플레이

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);  // Start at top-left corner
    display.println(F(" [Motor Power Menu]"));
    display.setTextSize(2);
    display.setCursor(5, 18);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Draw 'inverse' text
    display.print(" Pow : ");
    display.print(motor_pwm_power);
    display.drawRect(2, 37, 120, 13, WHITE);
    display.fillRect(2, 37, (motor_pwm_power * 12), 13, WHITE);
  }

  display.setTextColor(SSD1306_WHITE);
  display.display();  //화면에 출력
  display.setTextSize(1);
}


void drawMenu(int memu_item) {  //수정 전
  uint8_t i, h;
  display.writeFillRect(1, 17, 118, 63 - 17, SSD1306_BLACK);
  //Serial.println("memu_item");
  if (memu_item == 0) {
    display.setTextSize(2);
    display.setCursor(12, 30);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("Time set"));
    display.setTextSize(1);
    display.display();
  } else if (memu_item == 1) {
    display.setTextSize(2);
    display.setCursor(7, 30);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("Motor Pow"));
    display.setTextSize(1);
    display.display();
  }
}




int getRtcTime() {
  DateTime now = RTC.now();
  int all_now_minute = 60;
  if (now.month() != 4 || now.day() > 29) {
    RTC.adjust(DateTime(2022, 4, 1, 0, 0, 0));
    all_data_time = 0;
    //Serial.println("날짜 리셋");
  }
  all_now_minute = ((now.day() * 24) * 60) + ((now.hour() * 60)) + now.minute() - 1440;
  rest_time = hours_72 * 60 - minute_60;  //휴식 시간
  Serial.print("전체 시간");
  Serial.println(all_now_minute);
  return all_now_minute;
}


int now_algo(int all_now_minute) {
  int rest_time = hours_72 * 60 - minute_60;  //휴식 시간                                                                                      //작동 시간
  int array_value = 43200 / (hours_72 * 60);  //전체 반복 횟수
  static int count_value = 0;
  int val = motor_pwm_power * 24;
  if(val > 220){
    val = 255;
  }
  if(val <30){
    val = 0;
  }
//Serial.println(val);
  if (array_value > count_value) {
    if (all_now_minute > all_data_time) {
      all_data_time += all_work_time;  //60
      count_value++;
      //Serial.print("count_value : ");
      //Serial.println(count_value);
    }
    if (all_now_minute < all_data_time - rest_time) {
      Serial.println("펌프 작동");
      toogle_motor = true;
      analogWrite(6, val);

    } else if (all_now_minute > all_data_time - rest_time) {
      //펌프 휴식
      Serial.println("펌프 휴식");
      analogWrite(6, 0);
      toogle_motor = true;
    }
    if (43199 < all_data_time) {
      RTC.adjust(DateTime(2022, 4, 1, 0, 0, 0));
      Serial.println("reset");
      all_data_time = 0;
      count_value = 0;
      //리셋
    }
  }

  return count_value;
}
