/*
  메모리 저장관련 코드 입니다.
  특별한 경우가 아니라면 놔둡니다.
*/

#include <U8g2lib.h>   //lcd 모듈
#include <AccelStepper.h>
#include "ClickEncoder.h"  //로타리 엔코더 
#include "pin_map.h"

extern float router;
const char *mem_strings[4];

void memMenu(void) {

  int click_value = 0;
  uint8_t i, h;
  uint8_t w, d;
  int value_act = 0;
  while (1) {
    if (digitalRead(KILL_PIN) == LOW) {
      Serial.println("kill");
      break;
    }
    u8g2.setFont(u8g_font_cu12);
    u8g2.firstPage();

    do {
      u8g2.setFontRefHeightText();
      u8g2.setFontPosTop();
      u8g2.drawFrame(0, 0, 128, 64);
      u8g2.drawLine(60, 5, 60, 59);
      u8g2.drawLine(60, 34, 128, 34);
      u8g2.drawBitmap( 10, 0, 5, 64, mem);
      u8g2.drawBitmap(73, 33, 5, 18, mem1);
      u8g2.drawBitmap(73, 1, 5, 18, mem2);
      u8g2.setCursor(80, 48);
      u8g2.print(router);

      h = u8g2.getFontAscent() - u8g2.getFontDescent();
      w = u8g2.getWidth();
      ClickEncoder::Button a = encoder->getButton();

      value_act += encoder->getValue();   //

      if (value_act < 4 && value_act > -1) {
        Serial.println(value_act);
        for ( i = 0; i < 4; i++ ) {
          d = (w - u8g2.getStrWidth(mem_strings[i]) / 5);
          //  u8g2.setDefaultForegroundColor();
          if ( i == value_act) {
            u8g2.drawFrame(0, 0, 128, 64);
            u8g2.drawFrame(10, i * h + 1, w / 3 - 1, h + 2);

            if (value_act == 0) {
              EEPROM.get(1, ver);
              u8g2.setCursor(77, 15);
              u8g2.print(ver);
            }
            else if (value_act == 1) {
              EEPROM.get(1, ver);
              u8g2.setCursor(77, 15);
              u8g2.print(ver);
            }
            else if (value_act == 2) {
              EEPROM.get(2, ver1);
              u8g2.setCursor(77, 15);
              u8g2.print(ver1);
            }
            else if (value_act == 3) {
              EEPROM.get(2, ver1);
              u8g2.setCursor(77, 15);
              u8g2.print(ver1);
            }

          }

        }
        if (a != ClickEncoder::Open) {
          if (ClickEncoder::Clicked == a) {
            switch (value_act) {
              case 0:
                ver = router;
                EEPROM.put(1, ver);
                u8g2.setCursor(77, 15);
                u8g2.print(ver);
                break;
              case 1:
                EEPROM.get(1, router);
                u8g2.setCursor(77, 15);
                u8g2.print(ver);
                break;
              case 2:
                ver1 = router;
                EEPROM.put(2, ver1);
                u8g2.setCursor(77, 15);
                u8g2.print(ver1);
                break;
              case 3:
                EEPROM.get(2, router);
                u8g2.setCursor(77, 15);
                u8g2.print(ver1);
                break;
            }
          }
        }
      }

      else {
        value_act = 0;
        for ( i = 0; i < 4; i++ ) {
          d = (w - u8g2.getStrWidth(mem_strings[i]) / 5);
          //  u8g2.setDefaultForegroundColor();
          if ( i == value_act) {
            u8g2.drawFrame(0, 0, 128, 64);
            u8g2.drawFrame(10, i * h + 1, w / 3 - 1, h + 2);
          }

        }
      }
    }
    while ( u8g2.nextPage() );


  }
}
