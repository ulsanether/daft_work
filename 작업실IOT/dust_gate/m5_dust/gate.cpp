#include "Adafruit_PWMServoDriver.h"
#include "M5Stack.h"
#include "pin.h"
#include "gate.h"

extern Adafruit_PWMServoDriver pwm;

void btn::relay() {  //작동은 됨.
  for (int i = 0; i < 10; i++) {
    if (gate_state[i] == 1 or fire_state[i] == 1 or bluetooth_state[i] == 1 or button_toogle[i] == 1) {
      if (digitalRead(relay_sgl) == LOW) {
        digitalWrite(relay_sgl, HIGH);
      }//버튼 스테이트는 블루투스로 교
    }
  }
  for (int j = 0; j < 10; j++) {
    if (gate_state[j] == 0 and fire_state[j] == 0 and bluetooth_state[j] == 0 and button_toogle[j] == 0) {
      if (digitalRead(relay_sgl) == HIGH) {
        digitalWrite(relay_sgl, LOW);
      }
    }
  }
}

void btn::bt_gate(String text) {
Serial.print("블루 투스 함수 : ");
Serial.println(text);

  if (text == "GA01") {
    bluetooth_state[0] = 1;
    gate_play(0, 0, 0, 1, 0);
    gate_print(1, 1, 2);
  }  else if (text == "GA00") {
    bluetooth_state[0] = 0;
    gate_play(0, 0, 0, 0, 0);
    gate_print(1, 0, 2);
  }
  else if (text == "GA11") {
    bluetooth_state[1] = 1;
    gate_play(1, 0, 0, 1, 0);
    gate_print(2, 1, 2);
  }  else if (text == "GA10") {
    bluetooth_state[1] = 0;
    gate_play(1, 0, 0, 0, 0);
    gate_print(2, 0, 2);
  }

  else if (text == "GA21") {
    bluetooth_state[2] = 1;
    gate_play(2, 0, 0, 1, 0);
    gate_print(3, 1, 2);
  }  else if (text == "GA20") {
    bluetooth_state[2] = 0;
    gate_play(2, 0, 0, 0, 0);
    gate_print(3, 0, 2);
  }
  else if (text == "GA31") {
    bluetooth_state[3] = 1;
    gate_play(3, 0, 0, 1, 0);
    gate_print(4, 1, 2);
  }  else if (text == "GA30") {
    bluetooth_state[3] = 0;
    gate_play(3, 0, 0, 0, 0);
    gate_print(4, 0, 2);
  }

  else if (text == "GA41") {
    bluetooth_state[4] = 1;
    gate_play(4, 0, 0, 1, 0);
    gate_print(5, 1, 2);
  }  else if (text == "GA40") {
    bluetooth_state[4] = 0;
    gate_play(4, 0, 0, 0, 0);
    gate_print(5, 0, 2);
  }

  else if (text == "GA51") {
    bluetooth_state[5] = 1;
    gate_play(5, 0, 0, 1, 0);
    gate_print(6, 1, 2);
  }  else if (text == "GA50") {
    bluetooth_state[5] = 0;
    gate_play(5, 0, 0, 0, 0);
    gate_print(6, 0, 2);
  }

  else if (text == "GA61") {
    bluetooth_state[6] = 1;
    gate_play(6, 0, 0, 1, 0);
    gate_print(7, 1, 2);
  }  else if (text == "GA60") {
    bluetooth_state[5] = 0;
    gate_play(6, 0, 0, 0, 0);
    gate_print(7, 0, 2);
  }

  else if (text == "GA71") {
    bluetooth_state[7] = 1;
    gate_play(7, 0, 0, 1, 0);
    gate_print(8, 1, 2);
  }  else if (text == "GA70") {
    bluetooth_state[7] = 0;
    gate_play(7, 0, 0, 0, 0);
    gate_print(8, 0, 2);
  }

  else if (text == "GA81") {
    bluetooth_state[8] = 1;
    gate_play(8, 0, 0, 1, 0);
    gate_print(9, 1, 2);
  }  else if (text == "GA80") {
    bluetooth_state[8] = 0;
     
    gate_print(9, 0, 2);
  }


  else if (text == "GA91") {
    bluetooth_state[9] = 1;
    gate_play(9, 0, 0, 1, 0);
    gate_print(10, 1, 2);
  }  else if (text == "GA90") {
    bluetooth_state[9] = 0;
    gate_play(9, 0, 0, 0, 0);
    gate_print(10, 0, 2);
  }
}




void btn::firebase_get(String value) {
  //게이트 값 방식은 좀 수정할 것
  String gate_string[10] = "";

 // for(int i=0; i<10; i++){
   gate_string[0] = value.substring(11, 15);
  gate_string[1] = value.substring(27, 31);
  gate_string[2] = value.substring(43, 47);
   gate_string[3] = value.substring(59, 63);
   gate_string[4] = value.substring(75, 79);
   gate_string[5] = value.substring(91, 95);
   gate_string[6] = value.substring(107, 111);
   gate_string[7] = value.substring(123, 127);
   gate_string[8] = value.substring(139, 143);
  gate_string[9] = value.substring(155, 159);
  //}
  
for(int i=0; i<10; i++){
//  Serial.print("게이트");
// Serial.println(gate_string[i]);
}
  if (gate_string[0] == "GA01") {
    // M5.Lcd.fillRect(0, 0, 320, 100, WHITE); //하얀색을 넣고
    //출력될 게이트를 파이어베이스 표시와 함께 넣을것
    fire_state[0] = 1;
    gate_print(1, 1, 2);
   gate_play(0, 0,1 , 0, 0);
  }
  else if (gate_string[0] == "GA00") {
    fire_state[0] = 0;
    gate_print(1, 0, 2);
    gate_play(0, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA11") {
    fire_state[1] = 1;
    gate_print(2, 1, 2);
    //gate(1, 0, 1);
    gate_play(1, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA10") {
    fire_state[1] = 0;
    gate_print(2, 0, 2);
    //gate(1, 0, 0);
    gate_play(1, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA21") {
    gate_print(3, 1, 2);
    fire_state[2] = 1;
    //gate(2, 0, 1);
    gate_play(2, 0, 1, 0, 0);

  }
  else if (gate_string[0] == "GA20") {
    gate_print(3, 0, 2);
    fire_state[2] = 0;
    //gate(2, 0, 0);
    gate_play(2, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA31") {
    gate_print(4, 1, 2);
    fire_state[3] = 1;
    //gate(3, 0, 1);
    gate_play(3, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA30") {
    gate_print(4, 0, 2);
    fire_state[3] = 0;
    //gate(3, 0, 0);
    gate_play(3, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA41") {
    gate_print(5, 1, 2);
    fire_state[4] = 1;
    //gate(4, 0, 1);
    gate_play(4, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA40") {
    gate_print(5, 0, 2);
    fire_state[4] = 0;
    //gate(4, 0, 0);
    gate_play(4, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA51") {
    gate_print(6, 1, 2);
    fire_state[5] = 1;
    //gate(5, 0, 1);
    gate_play(5, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA50") {
    gate_print(6, 0, 2);
    fire_state[5] = 0;
    ///gate(5, 0, 0);
    gate_play(5, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA61") {
    gate_print(7, 1, 2);
    fire_state[6] = 1;
    //gate(6, 0, 1);
    gate_play(6, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA60") {
    gate_print(7, 0, 2);
    fire_state[6] = 0;
    //gate(6, 0, 0);
    gate_play(6, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA71") {
    gate_print(8, 1, 2);
    fire_state[7] = 1;
    //gate(7, 0, 1);
    gate_play(7, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA70") {
    gate_print(8, 0, 2);
    fire_state[7] = 0;
    //gate(7, 0, 0);
    gate_play(7, 0, 0, 0, 0);
  }
  if (gate_string[0]== "GA81") {
    gate_print(9, 1, 2);
    fire_state[8] = 1;
    //gate(8, 0, 1);
    gate_play(8, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA80") {
    gate_print(9, 0, 2);
    fire_state[8] = 0;
    //gate(8, 0, 0);
    gate_play(8, 0, 0, 0, 0);
  }
  if (gate_string[0] == "GA91") {
    gate_print(10, 1, 2);
    fire_state[9] = 1;
    //  gate(9, 0, 1);
    gate_play(8, 0, 1, 0, 0);
  }
  else if (gate_string[0] == "GA90") {
    gate_print(10, 0, 2);
    fire_state[9] = 0;
    //    gate(9, 0, 0);
    gate_play(9, 0, 0, 0, 0);
  }
}

//전류값을 받아와 게이트 동작

void btn::gate_set(char* _string) {
  String string = _string;
  // M5.Lcd.fillRect(0, 0, 320, 100, WHITE); //
  //열게될 게이트 문자 넣을것
  if (string.indexOf("GA01") != -1) {
    gate::gate_state[0] = 1;  //릴레이 온 오프
    gate_play(0, 1, 0, 0, 0);
  } else if (string.indexOf("GA00") != -1) {
    gate::gate_state[0] = 0;
    gate_play(0, 0, 0, 0, 0);
  }

  //2
  else if (string.indexOf("GA11") != -1) {
    gate::gate_state[1] = 1;
    gate_play(1, 1, 0, 0, 0);
  } else if (string.indexOf("GA10") != -1) {
    gate::gate_state[1] = 0;
    gate_play(1, 0, 0, 0, 0);
  }

  //3

  else if (string.indexOf("GA21") != -1) {
    gate::gate_state[2] = 1;
    gate_play(2, 1, 0, 0, 0);
  } else if (string.indexOf("GA20") != -1) {
    gate::gate_state[2] = 0;
    gate_play(2, 0, 0, 0, 0);
  }

  //4
  else if (string.indexOf("GA31") != -1) {
    gate::gate_state[3] = 1;
    gate_play(3, 1, 0, 0, 0);
  } else if (string.indexOf("GA30") != -1) {
    gate_play(3, 0, 0, 0, 0);
    gate::gate_state[3] = 0;
  }
  //5
  else if (string.indexOf("GA41") != -1) {
    gate_play(4, 1, 0, 0, 0);
    gate::gate_state[4] = 1;
  } else if (string.indexOf("GA40") != -1) {
    gate_play(4, 0, 0, 0, 0);
    gate::gate_state[4] = 0;
  }
  //6
  else if (string.indexOf("GA51") != -1) {
    gate::gate_state[5] = 1;
    gate_play(5, 1, 0, 0, 0);
  } else if (string.indexOf("GA50") != -1) {
    gate::gate_state[5] = 0;
    gate_play(5, 0, 0, 0, 0);
  }

  //7
  else if (string.indexOf("GA61") != -1) {
    gate::gate_state[6] = 1;
    gate_play(6, 1, 0, 0, 0);
  } else if (string.indexOf("GA60") != -1) {
    gate::gate_state[6] = 0;
    gate_play(6, 0, 0, 0, 0);
  }
  //8
  else if (string.indexOf("GA71") != -1) {
    gate::gate_state[7] = 1;
    gate_play(7, 1, 0, 0, 0);
  } else if (string.indexOf("GA70") != -1) {
    gate::gate_state[7] = 0;
    gate_play(7, 0, 0, 0, 0);
  }

  //8
  else if (string.indexOf("GA81") != -1) {
    gate::gate_state[8] = 1;
    gate_play(8, 1, 0, 0, 0);
  } else if (string.indexOf("GA80") != -1) {
    gate::gate_state[8] = 0;
    gate_play(8, 0, 0, 0, 0);
  }

  //9

  else if (string.indexOf("GA91") != -1) {
    gate::gate_state[1] = 1;
    gate_play(9, 1, 0, 0, 0);
  } else if (string.indexOf("GA90") != -1) {
    gate::gate_state[1] = 0;
    gate_play(9, 0, 0, 0, 0);
  }
}


void btn::gate_play(int motor_int, int gate_int, int fire_int, int button_int, int bt_int) {



//모터값이 겹치지 않게 수정 할 것 
  if ( gate_int == 1 or fire_int == 1 or button_int == 1 or bt_int == 1) {
    delay(100);
    tone_a(1);
    Serial.println("오픈");
   // M5.Lcd.drawString((String)motor_int, 63, 197);
    pwm.setPWM(motor_int, 0, ang_min[motor_int]);
    
  }


//
  //  dust_gate.ang_min[i] = 200; //ang_get.ang_min[i];
    //dust_gate.ang_max[i] = 400;




  if (gate_int == 0 and fire_int == 0 and button_int == 0 and bt_int == 0) {
    delay(100);
    tone_a(0);
    Serial.println("닫힘");
   //  M5.Lcd.drawString((String)motor_int, 63, 197);
    pwm.setPWM(motor_int, 0, ang_max[motor_int]);
    //릴레이 off화면 표시 코드 넣을것
  }  //모터 각각에 미니멈값과 맥스 값을 따로 준다

Serial.print(gate_int);
Serial.print(fire_int);
  Serial.print(button_int);
Serial.println(bt_int);
}


///////////////////////////////////////////////btn 클래스

void btn::image_state() {

  if (state_a != state_toogle) {
    state_toogle = state_a;

    switch (state_a) {
      case 0:
        M5.Lcd.drawRect(64, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(256, 170, 62, 68, BLACK);
        M5.Lcd.drawRect(2, 102, 64, 68, YELLOW);

        break;
      case 1:
        M5.Lcd.drawRect(2, 102, 64, 68, BLACK);
        M5.Lcd.drawRect(128, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(64, 102, 64, 70, RED);

        break;
      case 2:
        M5.Lcd.drawRect(64, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(192, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(128, 102, 64, 70, YELLOW);

        break;
      case 3:
        M5.Lcd.drawRect(128, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(256, 102, 62, 68, BLACK);
        M5.Lcd.drawRect(192, 102, 64, 70, RED);

        break;
      case 4:
        M5.Lcd.drawRect(192, 102, 64, 70, BLACK);
        M5.Lcd.drawRect(2, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(256, 102, 62, 68, YELLOW);

        break;
      case 5:
        M5.Lcd.drawRect(256, 102, 62, 68, BLACK);
        M5.Lcd.drawRect(64, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(2, 170, 64, 68, YELLOW);

        break;
      case 6:
        M5.Lcd.drawRect(2, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(128, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(64, 170, 64, 68, RED);
        break;

      case 7:
        M5.Lcd.drawRect(64, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(192, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(128, 170, 64, 68, YELLOW);
        break;

      case 8:
        M5.Lcd.drawRect(128, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(256, 170, 62, 68, BLACK);
        M5.Lcd.drawRect(192, 170, 64, 68, RED);
        break;

      case 9:
        M5.Lcd.drawRect(192, 170, 64, 68, BLACK);
        M5.Lcd.drawRect(2, 102, 64, 68, BLACK);
        M5.Lcd.drawRect(256, 170, 62, 68, YELLOW);
        break;
    }
  }
}



void btn::button_get(int _state_toogle) {
  if (_state_toogle == 1) {
    state_a--;
    if (state_a == -1) {
      state_a = (gate_val-1);  //gate_val이 메뉴 갯수 
    }
  } else if (_state_toogle == 2) {
    state_a++;
    if (state_a == gate_val) {
      state_a = 0;
    }
  }
}


void btn::button_val() {
  enum {left = 1, right, click_c };
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
  //  tone_a(left);
    button_get(left);
  }
  if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
  //  tone_a(right);
    button_get(right);

  }
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
//    tone_a(click_c);
    button_set();
  }
  image_state();
}


void btn::tone_a(int _a) {
  //버튼과 연동할때 톤의 길이가 길게 되면 에러 난다
  switch (_a) {
    case 0:
      M5.Speaker.setVolume(3);
      M5.Speaker.tone(961, 5);  //5이상 넣지 말것
      break;
    case 1:
      M5.Speaker.setVolume(3);
      M5.Speaker.tone(661, 5);
      break;
    case 2:
      M5.Speaker.setVolume(3);
      M5.Speaker.tone(361, 5);
      break;
  }
}


void btn::button_set() { //일단 10개를 만들어 놓는다.
  //버튼 클릭했을때 더스트 값으로 가는 함수

  M5.Lcd.drawRect(0, 0, 320, 100, WHITE);
  M5.Lcd.drawRect(0, 100, 320, 240, WHITE);
  switch (state_a) {
    case 0:
      if (button_toogle[0] == 0) {//오프 
        M5.Lcd.fillRect(0, 0, 320, 100, WHITE);
        M5.Lcd.setTextColor(BLACK, WHITE);
        M5.Lcd.fillRect(2, 102, 64, 70, WHITE);
        M5.Lcd.drawString("1", 22, 120);
        gate_print(1, 1, 1);
        button_toogle[0] = 1;
        gate_play(0, 0, 0, 1, 0); //임시임.

      } else if(button_toogle[0] == 1 or button_toogle_first[0] == 1) {
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(2, 102, 64, 70, BLACK);
        M5.Lcd.drawString("1", 22, 120);
        button_toogle[0] = 0;
        gate_print(1, 0, 1);
        gate_play(0, 0, 0, 0, 0); //임시임.
        
        button_toogle_first[0] = 0;  //
      }
      break;
    case 1:
      if (button_toogle[1] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, NAVY);
        M5.Lcd.setTextColor(WHITE, NAVY);
        M5.Lcd.fillRect(64, 102, 64, 70, NAVY);
        M5.Lcd.drawString("2", 86, 120);
        gate_print(2, 1, 1);
        button_toogle[1] = 1;
        gate_play(1, 0, 0, 1, 0); //임시임.
      } else if(button_toogle[1] == 1 or button_toogle_first[1] == 1){
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(64, 102, 64, 70, BLACK);
        M5.Lcd.drawString("2", 86, 120);
        gate_print(2, 0, 1);
        button_toogle[1] = 0;
        gate_play(1, 0, 0, 0, 0); //임시임.

          button_toogle_first[1] = 0;  //
      }

      break;

    case 2:
      if (button_toogle[2] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, DARKGREEN);
        M5.Lcd.setTextColor(BLACK, DARKGREEN);
        M5.Lcd.fillRect(128, 102, 64, 70, DARKGREEN);
        M5.Lcd.drawString("3", 150, 120);
        gate_print(3, 1, 1);
        button_toogle[2] = 1;
        gate_play(2, 0, 0, 1, 0); //임시임.
      } else if(button_toogle[2] == 1 or button_toogle_first[2] == 1){
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(128, 102, 64, 70, BLACK);
        M5.Lcd.drawString("3", 150, 120);
        gate_print(3, 0, 1);
        button_toogle[2] = 0;
        gate_play(2, 0, 0, 0, 0); //임시임.
      }

      break;

    case 3:
      if (button_toogle[3] == 0) {
        M5.Lcd.setTextColor(YELLOW, MAROON);
        M5.Lcd.fillRect(0, 0, 320, 100, MAROON);

        gate_print(4, 1, 1);
        M5.Lcd.fillRect(192, 102, 64, 70, MAROON);
        M5.Lcd.drawString("4", 214, 120);
        button_toogle[3] = 1;
        gate_play(3, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        gate_print(4, 0, 1);
        M5.Lcd.fillRect(192, 102, 64, 70, BLACK);
        M5.Lcd.drawString("4", 214, 120);
        button_toogle[3] = 0;
        gate_play(3, 0, 0, 0, 0); //임시임.
      }
      break;

    case 4:
      if (button_toogle[4] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, PURPLE);
        M5.Lcd.setTextColor(GREENYELLOW, PURPLE);
        gate_print(5, 1, 1);
        M5.Lcd.fillRect(256, 102, 62, 70, PURPLE);
        M5.Lcd.drawString("5", 278, 120);
        button_toogle[4] = 1;
        gate_play(4, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        gate_print(5, 0, 1);
        M5.Lcd.fillRect(256, 102, 62, 70, BLACK);
        M5.Lcd.drawString("5", 278, 120);
        button_toogle[4] = 0;
        gate_play(4, 0, 0, 0, 0); //임시임.
      }
      break;

    case 5:
      if (button_toogle[5] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, OLIVE);
        M5.Lcd.setTextColor(BLACK, OLIVE);
        M5.Lcd.fillRect(2, 170, 62, 68, OLIVE);
        M5.Lcd.drawString("6", 22, 190);
        gate_print(6, 1, 1);

        button_toogle[5] = 1;
        gate_play(5, 0, 0, 1, 0); //임시임.
      } else {
                M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        gate_print(6, 0, 1);
        M5.Lcd.fillRect(2, 170, 62, 68, BLACK);
        M5.Lcd.drawString("6", 22, 190);
        button_toogle[5] = 0;
        gate_play(5, 0, 0, 0, 0); //임시임.
      }
      break;

    case 6:
      if (button_toogle[6] == 0) {
        M5.Lcd.setTextColor(YELLOW, BLUE);
        M5.Lcd.fillRect(0, 0, 320, 100, BLUE);

        gate_print(7, 1, 1);
        M5.Lcd.fillRect(64, 170, 62, 68, BLUE);
        M5.Lcd.drawString("7", 86, 190);
        button_toogle[6] = 1;
        gate_play(6, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        gate_print(7, 0, 1);
        M5.Lcd.fillRect(64, 170, 62, 68, BLACK);
        M5.Lcd.drawString("7", 86, 190);
        button_toogle[6] = 0;
        gate_play(6, 0, 0, 0, 0); //임시임.
      }
      break;
    case 7:
      if (button_toogle[7] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, YELLOW);
        M5.Lcd.setTextColor(BLUE, YELLOW);
        gate_print(8, 1, 1);
        M5.Lcd.fillRect(128, 170, 62, 68, YELLOW);
        M5.Lcd.drawString("8", 150, 190);
        button_toogle[7] = 1;
        gate_play(7, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        gate_print(8, 0, 1);
        M5.Lcd.fillRect(128, 170, 62, 68, BLACK);
        M5.Lcd.drawString("8", 150, 190);
        button_toogle[7] = 0;
        gate_play(7, 0, 0, 0, 0); //임시임.
      }
      break;

    case 8:
      if (button_toogle[8] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, ORANGE);
        M5.Lcd.setTextColor(GREEN, ORANGE);
        gate_print(9, 1, 1);
        M5.Lcd.fillRect(192, 170, 62, 68, ORANGE);
        M5.Lcd.drawString("9", 214, 190);
        button_toogle[8] = 1;
        gate_play(8, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        gate_print(9, 0, 1);
        M5.Lcd.fillRect(192, 170, 62, 68, BLACK);
        M5.Lcd.drawString("9", 214, 190);

        button_toogle[8] = 0;
        gate_play(8, 0, 0, 0, 0); //임시임.
      }

      break;
    case 9:
      if (button_toogle[9] == 0) {
        M5.Lcd.fillRect(0, 0, 320, 100, PINK);
        M5.Lcd.setTextColor(BLACK, PINK);
        gate_print(10, 1, 1);
        M5.Lcd.fillRect(256, 170, 62, 68, PINK);
        M5.Lcd.drawString("10", 266, 190);
        button_toogle[9] = 10;
        gate_play(9, 0, 0, 1, 0); //임시임.
      } else {
        M5.Lcd.fillRect(0, 0, 320, 100, BLACK);
        M5.Lcd.setTextColor(WHITE, BLACK);
        gate_print(10, 0, 1);
        M5.Lcd.fillRect(256, 170, 62, 68, BLACK);
        M5.Lcd.drawString("10", 266, 190);

        button_toogle[9] = 0;
        gate_play(9, 0, 0, 0, 0); //임시임.
      }
      break;
  
  }
}


void btn::gate_print(int i, int z, int k) {

  if (k == 1) {
    M5.Lcd.drawString("Button", 10, 10);
  } else if (k == 2) {
    M5.Lcd.drawString("Firebase", 10, 10);
  } else if (k == 3) {
    M5.Lcd.drawString("Bluetooth", 10, 10);
  }
  M5.Lcd.setTextSize(5);

  M5.Lcd.drawNumber(i, 10, 50);
  switch (z) {
    case 1:
      M5.Lcd.drawString("NUM ON", 80, 50);
      break;
    case 0:
      M5.Lcd.drawString("NUM OFF", 80, 50);
      break;
  }
  M5.Lcd.setTextSize(4);

}
