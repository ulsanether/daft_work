/*
  영점을 잡는 부분이다.
  Z probe로 잡을 수 있다.
*/
int m_toogle = 0;
int ttoogle = 0;
int m_set_val = 0;
int t_set_val = 0;
int x_set_val = 0;
double p_zero;
double z_router =0;
//메뉴 수정
void zeroMenu(void) {
 z_router = router;
  while (1) {
    u8g2.setFont(u8g_font_cu12);
    u8g2.firstPage();
    do {

      u8g2.drawFrame(0, 0, 128, 64);
      u8g2.setCursor(30, 10);  //아래 tool change 위치 
      if (m_toogle == 0) {
        u8g2.println("Tool Change ");

      } else if (m_toogle == 1) {
        u8g2.println("Change Zero ");

      }  //1 == 320
      u8g2.setCursor(30, 30);  //z_router 값 프린팅 위치 
      u8g2.print(z_router);
    } while ( u8g2.nextPage() );

    ClickEncoder::Button a = encoder->getButton();

    value_act += encoder->getValue();    //
    Serial.print("휠값: ");  //휠값 업데이트 함수
    Serial.println(value_act);   //휠의 위치


    if (a != ClickEncoder::Open) {
      if (ClickEncoder::Clicked == a) {
        stepper.stop();
        Serial.println("111111");
        delay(1000);
        if ( ttoogle == 0 ) {
          if (set_val > 0) {

            m_set_val = set_val / 100;
            int k_set_val = int(set_val);
            t_set_val = k_set_val % 100;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(m_set_val * 100);
            delay(500);
            s_set_val = t_set_val / 10;
            x_set_val = t_set_val % 10;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(s_set_val * 10);
            delay(500);

            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(x_set_val);
            delay(500);
            ttoogle = 1;
          }
          else {
            m_set_val = set_val / 100.0;
            int x_set_val = int(set_val);
            t_set_val = x_set_val % 100;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(m_set_val * 100));
            delay(500);

            s_set_val = t_set_val / 10;
            x_set_val = t_set_val % 10;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(s_set_val * 10));

            delay(500);

            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(x_set_val));
            delay(500);

            ttoogle = 1;
          }
          m_toogle = 1;
          z_router = 0.0;
        } else {  //복귀

          if (set_val > 0) {

            m_set_val = set_val / 100;

            int j_set_val = int(set_val);
            t_set_val = j_set_val % 100;

            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(m_set_val * 100));
            delay(500);
            s_set_val = t_set_val / 10;
            x_set_val = t_set_val % 10;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(s_set_val * 10));
            delay(500);
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition(-(x_set_val));
            delay(500);
            ttoogle = 0;
            z_router = router;
          }
          else {
            m_set_val = int(set_val / 100);
            int i_set_val = int(set_val);
            t_set_val = i_set_val % 100;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition((m_set_val * 100));
            delay(100);

            s_set_val = t_set_val / 10;
            x_set_val = t_set_val % 10;
            stepper.setCurrentPosition(0);
            stepper.runToNewPosition((s_set_val * 10));

            delay(100);

            stepper.setCurrentPosition(0);
            stepper.runToNewPosition( x_set_val);
            delay(100);

            ttoogle = 0;
            z_router = router;
          }
          
          m_toogle = 0;
          //그리고 복귀하는 것.
        }


      }
      Serial.println("click");
    }
    else if (digitalRead(KILL_PIN) == LOW) {
      Serial.println(set_val);
      stepper.stop();
      delay(1000);
      break;
    }
  }

}
