/*
  영점을 잡는 부분이다.
  Z probe로 잡을 수 있다.
*/

#include <U8g2lib.h>   //lcd 모듈
#include <AccelStepper.h>
#include "ClickEncoder.h"  //로타리 엔코더 
#include "step_motor.h"
extern U8G2_ST7920_128X64_1_SW_SPI u8g2;
extern ClickEncoder *encoder;

extern float router;

extern uint8_t value_act;
extern uint8_t value_act1;

float ver = 0;
float ver1 = 0;//
float ver2 = 0;

void zeroMenu(void) {

  while (1) {
    u8g2.setFont(u8g_font_cu12);
    u8g2.firstPage();
    do {
      u8g2.drawFrame(0, 0, 128, 64);
      u8g2.drawBitmap( 10, 10, 5, 52, zero);
      u8g2.drawBitmap( 83, 3, 3, 59, zero1);
      u8g2.setCursor(15, 10);
      u8g2.print(router);
    } while ( u8g2.nextPage() );

    ClickEncoder::Button a = encoder->getButton();

    value_act += encoder->getValue();    //
    Serial.print("휠값: ");  //휠값 업데이트 함수
    Serial.println(value_act);   //휠의 위치

    if (value_act > value_act1) {
      router += 1;
      step_up(1);
      value_act = 125;
    }

    else if (value_act < value_act1) {
      router -= 1;
      step_down(1);
      value_act = 125;
    }

    else if (a != ClickEncoder::Open) {
      if (ClickEncoder::Clicked == a) {
        router = 0;
        stepper.stop(); //멈춤인데

        delay(1000);
      }
      Serial.println("click");
    }
    else if (digitalRead(KILL_PIN) == LOW) {  //핀다 핀으로 바꿔 보자.
      stepper.stop();  //동작 방식에 대해서는 한번 확인하자.
      delay(1000);
      step_down(1);
      delay(500);
      step_up(1);
      break;
    }
  }

}
