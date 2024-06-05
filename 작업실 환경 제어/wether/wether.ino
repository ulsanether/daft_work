//https://docs.m5stack.com/en/api/system  명령어

//이미지 데이터 메모리 업로드 툴 깃 주소( esptool)
//https://github.com/me-no-dev/arduino-esp32fs-plugin/releases

#include <WiFi.h>
#include <FirebaseESP32.h>

#include <BluetoothSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>
#include <RF24.h>
#include "FS.h"
#include "SPIFFS.h"
#include "M5Stack.h"
#include "state.h"


portTickType delay_10 = 10 / portTICK_RATE_MS;
#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"  //
#define FIREBASE_AUTH "FlowlqsCBeqdvMJxdgxbmEyeiWi2CbSX3KStpCUW"  //

#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD "cookiebox!1"  //작업실은 cookiebox, 집은 !1


//#define APIKEY
//#define VERSION
//const char* SERVER = "";

//String url = "http://apis.data.go.kr/1360000/VilageFcstInfoService/getUltraSrtNcst?serviceKey=XIR%2F7enMmtb%2FRvXmb7Lrc0pZTegsHRd9xv%2Fo0D1j1efyfS%2FAt3u3wAxJ%2FHXLdTY%2B4VPHY%2FkOmEuH8KWmOu8x0A%3D%3D&numOfRows=10&pageNo=1&base_date=20210905&base_time=0600&nx=102&ny=84&dataType=XML";

FirebaseData firebaseData;
FirebaseJson json;
RF24 radio(26, 25);     // SPI통신을 위한 (CE, CSN) 핀 선언
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
BluetoothSerial SerialBT;

//클래스 생성.

#define relay_sgl 3
//
#define Freq 58  //전류 값
int state_x = 0;
int state_toogle = 0;
const byte address[6] = "00001"; 
state sta;
void setup() {

  M5.begin(true, false, false, false); //lcd, sd카드, 직렬통신, i2c 순서로
  M5.Power.begin();
  M5.Speaker.begin(); //Initialize the speaker
  Serial.begin(115200);
 // SerialBT.begin("DUST GATE"); //Bluetooth device name
    M5.Speaker.begin(); //Initialize the speaker
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
  pwm.begin();
  pwm.setPWMFreq(Freq);
  radio.begin();
  radio.openReadingPipe(0, address);// 데이터를 받을 송신기 주소를 설정
  radio.setPALevel(RF24_PA_MAX); // 송신거리에 따른, 전원공급 파워레벨 설정
  //(최소) RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX (최대) 설정가능
  //송신이 약하다고 판단될 경우 nRF24모듈의 GND와 3.3V 단자에 전해콘덴서(10uF이상:+를3.3V연결)사용권장
  radio.startListening();   // 모듈을 수신기(상태)로 설정
  pinMode(relay_sgl, OUTPUT);
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
  delay(2000);
  M5.Lcd.setTextSize(6);
}



void loop() {
    if(Firebase.get(firebaseData, "Room_3/board_1")) {
    String value = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다
      Serial.println(value);

  }
 Serial.println(Firebase.get(firebaseData, "Room_3/board_1"));
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
    Serial.println("a");
    state_x = sta.button_state(0, state_x, 1);
  }
  if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
    state_x = sta.button_state(1, state_x, 2);
    Serial.println(state_x);
  }
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
     M5.Lcd.setTextColor(BLACK,WHITE);
     if(state_x ==0){
          M5.Lcd.drawString("Sunny", 75, 197);
     }else if(state_x==1){
       M5.Lcd.drawString("Blur", 90, 197);
     }else if(state_x==2){
       M5.Lcd.drawString("Working", 30, 197);
     }else if(state_x==3){
       M5.Lcd.drawString("Outing", 60, 197);
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
