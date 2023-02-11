
//135*240 사이즈

//설명 https://diyprojects.io/ttgo-t-watch-get-started-esp32-tft_espi-library/#.YQNom44zaUk

#include <FirebaseESP32.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include <WiFi.h>

#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"  //
#define FIREBASE_AUTH "FlowlqsCBeqdvMJxdgxbmEyeiWi2CbSX3KStpCUW"  //
#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD "cookiebox"  //작업실은 cookiebox, 집은 !1

#define BUTTON1PIN 35
#define BUTTON2PIN 0

FirebaseData firebaseData;
FirebaseJson json;
TFT_eSPI tft = TFT_eSPI();  

bool showButton     = true;
bool showButton1     = false;
long lastDebounceButton1 = 0;    // Holds Button1 last debounce
long lastDebounceButton2 = 0;    // Holds Button2 last debounce
long debounceDelay       = 300;  // 200ms between re-polling

char *menu_ary[] = {"AN", "ML", "PN", "TA", "SA", "BA", "CN", ""};
int menu_iary[7] = {0, 0, 0, 0, 0, 0, 0};
bool toogle[7] = {0,0,0,0,0,0,0};

int bar;
int x_dr = 10;
String value = "test";
int i = 0;

//---------------------------------------------------------

void IRAM_ATTR toggleButton1() {
  if ((millis() - lastDebounceButton1) > debounceDelay) {
    i++;
    if (i > 6) {
      i = 0;

    }
    Serial.println(i);
  }

  lastDebounceButton1 = millis();
}

void IRAM_ATTR toggleButton2() {
  if ((millis() - lastDebounceButton2) > debounceDelay) {

    showButton1 = true;

    lastDebounceButton2 = millis();

  }
}


//----------------------------------------------------------

void setup(void) {

  tft.setFreeFont(&FreeMono12pt7b);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK,TFT_WHITE);

  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);
  attachInterrupt(BUTTON1PIN, toggleButton1, RISING);
  attachInterrupt(BUTTON2PIN, toggleButton2, FALLING);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  tft.setCursor(0, 0, 2);
  Serial.println();
  Serial.print("와이파이에 연결");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    tft.println("DaftWork");
    delay(300);
  }
  tft.fillScreen(TFT_SKYBLUE);
  tft.setTextColor(TFT_BLACK,TFT_SKYBLUE);
  Serial.print("IP에 연결");
  Serial.println(WiFi.localIP());
  tft.print(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //대용량 데이터 작업시 HTTP 응답하는 버퍼 크기 설정.
  firebaseData.setResponseSize(1024);

  //데이터 베이스 읽기 시간 제한을 1분으로 설정 (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);  //1초 *60 = 1분이란 설정

  //tiny(가장 작은), small(작은), medium(중간), large and unlimited(무제한).
  //크기및 쓰기 제한 시간 소형 1초
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  reset_fire();


  
  tft.setRotation(0);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GOLD, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 30);
  tft.print("DaftWork");
  tft.drawRoundRect(0, 0, 135, 240, 3, TFT_WHITE);
  tft.setTextSize(1);
  for (int j = 1 ; j < 135; j += 19) {
    tft.drawRoundRect(j, 200, 19, 30, 4, TFT_WHITE);
  }


  
}


//---------------------------------------------------------------------------------------

void loop() {

  if (Firebase.get(firebaseData, "Room_3/board_1/")) {
    value = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다.
  }

  if (showButton1 == true) {
    bar = showbutton();}
    
  menu_a();
  menu_b();

}



//------------------------------------------------------------------------------
void menu_a() {
  tft.fillRect(3, 50, 126, 143, TFT_BLACK);
  tft.setTextSize(2);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setCursor(27, 130);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); //135*240
  tft.print(menu_ary[i]);
}




void menu_b() {
  switch (i) {

    case 0:
      x_dr = 10;
      break;
    case 1:
      x_dr = 29;
      break;
    case 2:
      x_dr = 48;
      break;

    case 3:
      x_dr = 67;
      break;
    case 4:
      x_dr = 86;
      break;
    case 5:
      x_dr = 105;
      break;
    case 6:
      x_dr = 126;
      break;

  }

  tft.drawLine(x_dr, 170 , x_dr,  190, TFT_ORANGE);


  if (menu_iary[0] == 3) {
    tft.fillCircle(10, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(10, 215, 4, TFT_BLACK);
  }
  if (menu_iary[1] == 3) {
    tft.fillCircle(29, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(29, 215, 4, TFT_BLACK);
  }

  if (menu_iary[2] == 3) {
    tft.fillCircle(48, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(48, 215, 4, TFT_BLACK);
  }
  if (menu_iary[3] == 3) {
    tft.fillCircle(67, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(67, 215, 4, TFT_BLACK);
  }

  if (menu_iary[4] == 3) {
    tft.fillCircle(86, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(86, 215, 4, TFT_BLACK);
  }

  if (menu_iary[5] == 3) {
    tft.fillCircle(105, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(105, 215, 4, TFT_BLACK);
  }
  if (menu_iary[6] == 3) {
    tft.fillCircle(126, 215, 4, TFT_GREEN);
  } else
  {
    tft.fillCircle(126, 215, 4, TFT_BLACK);
  }

}

void showbutton() {

  switch (i) {
    case 0:
      if (toogle[0] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_1", "AN01");  //각도 절단기
        toogle[0] = 1;
        menu_iary[0] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_1", "AN00");
        toogle[0] = 0;
        menu_iary[0] = 0;
      }
      break;
    case 1:
      if (toogle[1] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_2", "ML01");  //각도 절단기
        toogle[1] = 1;
        menu_iary[1] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_2", "ML00");

        toogle[1] = 0;
        menu_iary[1] = 0;
      }
      break;
    case 2:
      if (toogle[2] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_3", "PN01");  //각도 절단기

        toogle[2] = 1;
        menu_iary[2] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_3", "PN00");

        toogle[2] = 0;
        menu_iary[2] = 0;
      }
      break;
    case 3:
      if (toogle[3] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_4", "TA01");  //각도 절단기
        toogle[3] = 1;
        menu_iary[3] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_4", "TA00");
        toogle[3] = 0;
        menu_iary[3] = 0;
      }
      break;
    case 4:
      if (toogle[4]== 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_5", "SA01");  //각도 절단기

        toogle[4] = 1;
        menu_iary[4] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_5", "SA00");

        toogle[4] = 0;
        menu_iary[4] = 0;
      }
      break;
    case 5:
      if (toogle[5] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_6", "BA01");  //각도 절단기
        toogle[5] = 1;
        delay(500);
        menu_iary[5] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_6", "BA00");
        toogle[5] = 0;
        menu_iary[5] = 0;
      }
      break;
    case 6:
      if (toogle[6] == 0) {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_7", "CN01");  //각도 절단기

        toogle[6] = 1;
        menu_iary[6] = 3;
      } else {
        Firebase.setString(firebaseData, "Room_3/board_1/gate_7", "CN00");
        toogle[6] = 0;
        menu_iary[6] = 0;
      }
      break;

  }
  showButton1 = false;
}


void reset_fire() {
  Firebase.setString(firebaseData, "Room_3/board_1/gate_1", "AN02");  //각도 절단기
  Firebase.setString(firebaseData, "Room_3/board_1/gate_2", "ML02");  //밀링
  Firebase.setString(firebaseData, "Room_3/board_1/gate_3", "PN02");  //자동 대패
  Firebase.setString(firebaseData, "Room_3/board_1/gate_4", "TA02");  //테이블 쏘
  Firebase.setString(firebaseData, "Room_3/board_1/gate_5", "SA02");  //샌딩
  Firebase.setString(firebaseData, "Room_3/board_1/gate_6", "BA02"); //밴드쏘
  Firebase.setString(firebaseData, "Room_3/board_1/gate_7", "CN02");  //CNC
}
