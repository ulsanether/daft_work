//https://docs.m5stack.com/en/api/system  명령어

//이미지 데이터 메모리 업로드 툴 깃 주소( esptool)
//https://github.com/me-no-dev/arduino-esp32fs-plugin/releases

#include <WiFi.h>
#include <FirebaseESP32.h>


#include "FS.h"
#include "SPIFFS.h"
#include "M5Stack.h"
#include "state.h"

#define FIREBASE_HOST "ucon-robot-default-rtdb.asia-southeast1.firebasedatabase.app"  //
#define FIREBASE_AUTH "opmEz2YVv2Lg8oAq36tyN3m0ra3oEmwLv3T97Wur"  //

#define WIFI_SSID "KT_GiGA_5B1F"
#define WIFI_PASSWORD "0dee01hz80"  


//#define APIKEY
//#define VERSION
//const char* SERVER = "";

//String url = "http://apis.data.go.kr/1360000/VilageFcstInfoService/getUltraSrtNcst?serviceKey=XIR%2F7enMmtb%2FRvXmb7Lrc0pZTegsHRd9xv%2Fo0D1j1efyfS%2FAt3u3wAxJ%2FHXLdTY%2B4VPHY%2FkOmEuH8KWmOu8x0A%3D%3D&numOfRows=10&pageNo=1&base_date=20210905&base_time=0600&nx=102&ny=84&dataType=XML";

FirebaseData firebaseData;
FirebaseJson json;

//클래스 생성.


int state_x = 0;
int state_toogle = 0;

state sta;
void setup() {

  M5.begin(true, false, false, false); //lcd, sd카드, 직렬통신, i2c 순서로
  M5.Power.begin();
  M5.Speaker.begin(); //Initialize the speaker
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
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

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
  delay(2000);
  M5.Lcd.setTextSize(6);
}



void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
     M5.Lcd.wakeup();
    Serial.println("a");
    state_x = sta.button_state(0, state_x, 1);
  }
  if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
     M5.Lcd.wakeup();
    state_x = sta.button_state(1, state_x, 2);
    Serial.println(state_x);
  }
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
 M5.Lcd.wakeup();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
    M5.Lcd.setTextColor(BLACK, WHITE);
    if (state_x == 0) {
      M5.Lcd.drawString("Sunny", 75, 197);
      delay(3000);
      M5.Lcd.sleep();
    } else if (state_x == 1) {
      M5.Lcd.drawString("Blur", 90, 197);
      delay(3000);
      M5.Lcd.sleep();
    } else if (state_x == 2) {
      M5.Lcd.drawString("Working", 30, 197);
      delay(3000);
      M5.Lcd.sleep();
    } else if (state_x == 3) {
      M5.Lcd.drawString("Outing", 60, 197);
      delay(3000);
      M5.Lcd.sleep();
    }
    sta.click_state(state_x);
  }
  sta.img_update(state_x, &state_toogle);
}



void fire_base_sun(int a) { //맑음 외출
  switch (a) {
    case 1:
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_1", "FA02");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_2", "FA02");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_3", "FA02");

      Firebase.setString(firebaseData, "Room_2/board_1/Fan_1", "FA02");
      Firebase.setString(firebaseData, "Room_2/board_1/Fan_2", "FA01");

      Firebase.setString(firebaseData, "Room_3/board_2/Fan_1", "FA60");
      break;
    case 2:
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_1", "FA00");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_2", "FA00");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_3", "FA00");

      Firebase.setString(firebaseData, "Room_2/board_1/Fan_1", "FA00");
      Firebase.setString(firebaseData, "Room_2/board_1/Fan_2", "FA00");

      Firebase.setString(firebaseData, "Room_3/board_2/Fan_1", "FA00");
      break;
    case 3:

      Firebase.setString(firebaseData, "Room_1/board_1/Fan_1", "FA02");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_2", "FA01");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_3", "FA02");

      Firebase.setString(firebaseData, "Room_2/board_1/Fan_1", "FA02");
      Firebase.setString(firebaseData, "Room_2/board_1/Fan_2", "FA01");

      Firebase.setString(firebaseData, "Room_3/board_2/Fan_1", "FA60");
      break;
    case 4:

      Firebase.setString(firebaseData, "Room_1/board_1/Fan_1", "FA01");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_2", "FA01");
      Firebase.setString(firebaseData, "Room_1/board_1/Fan_3", "FA01");

      Firebase.setString(firebaseData, "Room_2/board_1/Fan_1", "FA00");
      Firebase.setString(firebaseData, "Room_2/board_1/Fan_2", "FA00");

      Firebase.setString(firebaseData, "Room_3/board_2/Fan_1", "FA00");
      break;
  }
}
