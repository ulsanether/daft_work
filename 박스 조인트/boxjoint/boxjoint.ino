//09_13일


//https://docs.m5stack.com/en/api/system  명령어

//이미지 데이터 메모리 업로드 툴 깃 주소( esptool)
//https://github.com/me-no-dev/arduino-esp32fs-plugin/releases

#include <AccelStepper.h>


//#include <WiFi.h>
//#include <FirebaseESP32.h>
#include "FS.h"
#include "SPIFFS.h"
#include "M5Stack.h"
#include "gui.h"

#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD_HOME "cookiebox!1"
#define WIFI_PASSWORD_WORK "cookiebox"

gui gui_a[2];

float blade = 8.0;  //날 두께
float magin = 0.2;   //마진값.

int state_toogle = 1;
int state_toogle_sa = 1;
int state_toogle_b = 1;
int menu_state = 0;
int state_x = 0;
int state_sa = 0;
int state_ba = 0;

int z_switch = 26;


//////조인트 값
bool joint_val[4] = {1, 0, 0, 0}; //메뉴 값
float joint_gap[4] = {0, 0, 0, 0};




void setup() {
  M5.begin(true, false, false, false);
  M5.Power.begin();
  Serial.begin(115200);

  pinMode(z_switch, INPUT_PULLUP);  //캔슬 스위치

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
  delay(2000);
  M5.Lcd.setTextSize(3);
}




void loop() {
  main_loop();
}



void main_loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
    state_x = gui_a[0].button_state(0, state_x, 1);
    //날 두께와 마진 값 출력. 적을것.
  }
  if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
    state_x = gui_a[0].button_state(1, state_x, 2);
  }
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
    click_state(state_x);
  }
  img_update(state_x, &state_toogle);
}


void click_state(int state_a) {   //클릭 호출함수인데 이걸 어떻게 바꿔야 한다.

  if (state_a == 0) {
    menu_sa();  //날 두께와 마진 설정.
  } else if (state_a == 1) {
    menu_ba();
  } else if (state_a == 2) {
    menu_play();
  }
}



void img_update(int _state_a, int *state_toogle) {
  if (_state_a != *state_toogle) {
    *state_toogle = _state_a;
    switch (_state_a) {
      case 0:
        M5.Lcd.drawJpgFile(SPIFFS, "/a.jpg", 0, 60);
        Serial.println(1);
        break;

      case 1:
        M5.Lcd.drawJpgFile(SPIFFS, "/b.jpg", 0, 60);
        Serial.println(2);
        break;

      case 2:

        M5.Lcd.drawJpgFile(SPIFFS, "/c.jpg", 0, 60);
        Serial.println(3);
        break;


    }
    M5.Lcd.setTextColor(WHITE, DARKGREY);
    M5.Lcd.fillRect(100, 0, 320, 60, DARKGREY);
    M5.Lcd.fillRect(0, 0, 140, 60, BLACK);
    M5.Lcd.drawFastHLine(140, 30, 320, BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Blade : ", 142, 7);
    M5.Lcd.drawString("Margin: ", 142, 36);
    M5.Lcd.drawFloat(blade, 2, 230, 7 );
    M5.Lcd.drawFloat(magin, 2, 230, 36 );
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawString("2 JOINT", 5, 15);   //장부 위치 변수 넣을것
  }
}



///////////////////////////////////////////////////두께 마진 설정.

void menu_sa() {

  while (1) {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      if (state_sa == 0) {
        blade -= 0.5;
        M5.Lcd.drawFloat(blade, 2, 5, 10 );
      } else if (state_sa == 1) {
        magin -= 0.1;
        M5.Lcd.drawFloat(magin, 2, 5, 120 );
      }
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
      if (state_sa == 0) {
        blade += 0.5;
        M5.Lcd.drawFloat(blade, 2, 5, 10 );
      } else if (state_sa == 1) {
        magin += 0.1;
        M5.Lcd.drawFloat(magin, 2, 5, 120 );
      }
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      state_sa++;
      if (state_sa >= 3) {
        state_sa = 0;
      }
    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      break;
      state_toogle = 1;
      for (int i = 0; i < 4; i++) {
        joint_gap[i] = blade;
      }

    }
    img_update_a(state_sa, &state_toogle_sa);
  }

}



void img_update_a(int _state_a, int *state_toogle_sa) {
  if (_state_a != *state_toogle_sa) {
    *state_toogle_sa = _state_a;
    switch (_state_a) {
      case 0:
        M5.Lcd.drawJpgFile(SPIFFS, "/a_1.jpg", 160, 0);
        Serial.println(1);
        break;

      case 1:
        M5.Lcd.drawJpgFile(SPIFFS, "/b_1.jpg", 160, 0);
        Serial.println(2);
        break;

      case 2:

        M5.Lcd.drawJpgFile(SPIFFS, "/c_1.jpg", 160, 0);
        Serial.println(3);
        break;
    }
    M5.Lcd.fillRect(0, 0, 160, 180, RED);
    M5.Lcd.setTextColor(BLACK, RED);
    M5.Lcd.drawString("Blade ", 5, 10);
    M5.Lcd.drawFloat(blade, 2, 5, 50 );
    M5.Lcd.drawString("Margin:", 5, 100);
    M5.Lcd.drawFloat(magin, 2, 5, 120 );
    M5.Lcd.drawJpgFile(SPIFFS, "/button.jpg", 0, 180);
  }

}


///////////////////////////장부 설정


void menu_ba() {
  while (1) {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      state_ba = gui_a[1].button_state(0, state_ba, 1, true);

    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
      state_ba = gui_a[1].button_state(1, state_ba, 2, true);

    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      click_state_2(state_ba);
    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      M5.Lcd.fillScreen(WHITE);
      break;
    }
    img_update_b(state_ba, &state_toogle_b);
  }

}



void img_update_b(int _state_a, int *state_toogle_ba) {
  M5.update();
  if (_state_a != *state_toogle_ba) {
    *state_toogle_ba = _state_a;
    switch (_state_a) {
      case 0:
        M5.Lcd.drawJpgFile(SPIFFS, "/a_2.jpg", 0, 0);
        Serial.println(1);

        break;

      case 1:
        M5.Lcd.drawJpgFile(SPIFFS, "/b_2.jpg", 0, 0);
        Serial.println(2);
        break;

      case 2:

        M5.Lcd.drawJpgFile(SPIFFS, "/c_2.jpg", 0, 0);
        Serial.println(3);
        break;

      case 3:
        M5.Lcd.drawJpgFile(SPIFFS, "/d_2.jpg", 0, 0);
        Serial.println(3);
        break;

    }

  }

}



void click_state_2(int state_a) {

  if (state_a == 0) {
    joint_1();
  } else if (state_a == 1) {
    joint_2();

  } else if (state_a == 2) {
    joint_3();
  }
  else if (state_a == 4) {
    joint_4();
  }
}


void joint_1() {

  while (1) {
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      joint_gap[0] -= 0.5;
      M5.Lcd.setTextSize(2);
      for (int i = 50; i < 250; i += 60) {
        M5.Lcd.drawFloat(joint_gap[0], 1, i, 5 );
        M5.Lcd.drawFloat(joint_gap[0], 1, i + 24, 30 );
      }
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
      M5.Lcd.setTextSize(2);
      joint_gap[0] += 0.5;
      for (int i = 50; i < 250; i += 60) {
        M5.Lcd.drawFloat(joint_gap[0], 1, i, 5 );
        M5.Lcd.drawFloat(joint_gap[0], 1, i + 24, 30 );
      }
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      //확정.
      //이 설정으로 하겠습니까?

      //메인 루프로
      joint_val[0] = true; //1번 온

    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      break;
      //M5.Lcd.fillScreen(WHITE);
      //뒤 설정으로
    }
    img_update_b(state_ba, &state_toogle_b);
  }

}


void joint_2() {
  M5.Lcd.drawFloat(joint_gap[1], 2, 5, 5 );

  while (1) {
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      joint_gap[1] -= 0.5;
      M5.Lcd.drawFloat(joint_gap[1], 2, 5, 5 );
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {

      joint_gap[1] += 0.5;
      M5.Lcd.drawFloat(joint_gap[1], 2, 5, 5 );
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      //확정.
      //이 설정으로 하겠습니까?

      //메인 루프로
      joint_val[1] = true; //1번 온
      joint_val[2] = false;
      joint_val[3] = false;
      joint_val[4] = false;

    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      break;
      //M5.Lcd.fillScreen(WHITE);
      //뒤 설정으로
    }
    img_update_b(state_ba, &state_toogle_b);
  }

}



void joint_3() {
  M5.Lcd.drawFloat(joint_gap[2], 2, 5, 5 );

  while (1) {
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      joint_gap[2] -= 0.5;



    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {

      joint_gap[2] += 0.5;
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      //확정.
      //이 설정으로 하겠습니까?

      //메인 루프로
      if (joint_val[1] == true) {
        joint_val[2] = true; //1번 온
      } else {
        //앞의 설정부터 먼저
      }

    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      break;
      //M5.Lcd.fillScreen(WHITE);
      //뒤 설정으로
    }
    img_update_b(state_ba, &state_toogle_b);
  }

}



void joint_4() {
  M5.Lcd.drawFloat(joint_gap[3], 2, 5, 5 );

  while (1) {
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      joint_gap[1] -= 0.5;
      M5.Lcd.drawFloat(joint_gap[3], 2, 5, 5 );
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {

      joint_gap[1] += 0.5;
      M5.Lcd.drawFloat(joint_gap[3], 2, 5, 5 );
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      //확정.
      //이 설정으로 하겠습니까?

      if (joint_val[2] == true) {
        joint_val[3] = true; //1번 온
      } else {
        //앞의 설정부터 먼저
      }
    }
    else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
      break;
      //M5.Lcd.fillScreen(WHITE);
      //뒤 설정으로
    }
    img_update_b(state_ba, &state_toogle_b);
  }

}


//
//날이 8mm
//갭이 22mm
//cut_0 = joint_gap[0] /blade  //3
//blade - 1mm 이동 
//cut_0_0 = joint_gap[0] % blade  // 2mm
//move_0 = 

void menu_play() {

  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
    //a면

  }
  if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
    //b면

  }
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
    //캔슬
  }
  else if (digitalRead(z_switch) == LOW) {  //브레이크 다시 만들것
    //실행.
  }

}
