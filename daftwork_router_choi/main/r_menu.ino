/*
  메모리 저장관련 코드 입니다.
  특별한 경우가 아니라면 놔둡니다.
*/

void memMenu(void) {

  while (1) {


    draw_mem(mem_setup, *(&mem_setup + 1) - mem_setup);
    ClickEncoder::Button a = encoder->getButton();

    value_act += encoder->getValue();    //
    Serial.print("휠값: ");  //휠값 업데이트 함수
    Serial.println(value_act);   //휠의 위치

    if (value_act > value_act1) {
      mem_current++;

      if ( mem_current >= MEM_ITEMS ) {
        mem_current = 0;
      }
      value_act = 125;
    }

    else if (value_act < value_act1) {

      if ( mem_current == 0 ) {
        mem_current = MEM_ITEMS;
      }
      mem_current--;
      value_act = 125;
    }

    else if (a != ClickEncoder::Open) {
      if (ClickEncoder::Clicked == a) {
        if ( mem_current == 0 ) {
          ver = router;
          //10mm이동 코드 사용시 주석 처리 할 것 
          EEPROM.put(1, ver);    
          //아래 코드 적어 놓으면 
//1번메뉴 실행 코드 

                    //10mm이동 코드
                      //stepper.setCurrentPosition(0);
              //stepper.runToNewPosition(Move_high * 20); //10mm
        }
        else if (mem_current == 1) {
          EEPROM.get(1, router);

          //2번 메뉴 실코드 
        } else if (mem_current == 2) {
          ver1 = router;
          EEPROM.put(2, ver1);

//3번 메뉴 실행 코드 
          
        } else if (mem_current == 3) {
          EEPROM.get(2, router);

          //4번 메뉴 실행 콛 ㅡ
        }
      }
      Serial.println("click");
    }

    else if (digitalRead(KILL_PIN) == LOW) {
      break;
    }

  }
}








//안쓰는 코드 
void draw_mem(const char *menu[], uint8_t menu_len) {

  uint8_t i, h;
  uint8_t w, d;

  u8g2.setFont(u8g_font_cu12);
  u8g2.firstPage();
  do {
    u8g2.setFontRefHeightText();
    u8g2.setFontPosTop();

    u8g2.drawBitmap( 10, 0, 5, 64, mem);
    u8g2.drawBitmap(73, 33, 5, 18, mem1);
    u8g2.drawBitmap(73, 1, 5, 18, mem2);
    u8g2.setCursor(80, 48);
    u8g2.print(router);
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.drawLine(60, 5, 60, 59);
    u8g2.drawLine(60, 34, 128, 34);

    h = u8g2.getFontAscent() - u8g2.getFontDescent();
    w = u8g2.getWidth();
    for ( i = 0; i < menu_len; i++ ) {
      d = (w - u8g2.getStrWidth(mem_strings[i]) / 5);
      //  u8g2.setDefaultForegroundColor();
      if ( i == mem_current) {
        u8g2.drawFrame(10, i * h + 1, w / 3 - 1, h + 2);
      }
    }
    if (mem_current == 0) {
      EEPROM.get(1, ver);
      u8g2.setCursor(77, 15);
      u8g2.print(ver);
//ver값을 step 변환
//  stepper.setCurrentPosition(0);
 //stepper.runToNewPosition(ver per step)
      
    }
    else if (mem_current == 1) {
      EEPROM.get(1, ver);
      u8g2.setCursor(77, 15);
      u8g2.print(ver);
    }
    else if (mem_current == 2) {
      EEPROM.get(2, ver1);
      u8g2.setCursor(77, 15);
      u8g2.print(ver1);
    }
    else if (mem_current == 3) {
      u8g2.setCursor(77, 15);
      u8g2.print(EEPROM.get(2, ver1));
    }
  }  while ( u8g2.nextPage() );

}
