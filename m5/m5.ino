
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "M5Stack.h"

#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"  //
#define FIREBASE_AUTH ""  //


#define WIFI_SSID ""
#define WIFI_PASSWORD ""  /

#define relay 25

FirebaseData firebaseData;  //객체
FirebaseJson json;

void setup() {

  M5.Speaker.begin(); //Initialize the speaker
  M5.begin(true, false, false, false); //lcd, sd카드, 직렬통신, i2c 순서로
  M5.Power.begin();
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);  //1초 *60 = 1분이란 설정
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  M5.Lcd.fillScreen(WHITE);
  delay(2000);
  M5.Lcd.setTextSize(6);

}

void loop() {
  delay(200);
  if (Firebase.get(firebaseData, "home")) {
    String value = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다.
    if (value.substring(7, 11) == "1111") {
      digitalWrite(relay, HIGH);
      Serial.println("on");
    } else if (value.substring(7, 11) == "2222") {
      digitalWrite(relay, LOW);
      Serial.println("off");
    }
  }
}
