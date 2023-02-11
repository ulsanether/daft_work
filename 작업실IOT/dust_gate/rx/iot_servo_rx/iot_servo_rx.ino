
/* =============================================================
  공방 자동화


  아두이노 제어 파일입니다. Wemos D1 보드에 적용 가능합니다.
  집진 게이트를 자동으로 제어하기 위한 파일입니다.
  인터넷연결이 필요로 하며, 구글 파이어베이스 사용자 id가 필요로 합니다.



  필요 하드웨어

  Wemos D1 혹은 Wemos D1 mini
  아두이노 우노 혹은 mini
  2.4G RF모듈
  MG996 서보 모터
  16채널 서보 모터 드라이버
  플라스틱 집진 게이트
  M3 볼트 너트
  3D 프린터 출력물.

	 
	 


  보드 라이브러리 주소 : http://arduino.esp8266.com/stable/package_esp8266com_index.json

  -----------------------------------------------------------------
  2020-12-12
  ether
  hangmini12@naver.com
  =================================================================
*/


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"  //
#define FIREBASE_AUTH "FlowlqsCBeqdvMJxdgxbmEyeiWi2CbSX3KStpCUW"  //
#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD "cookiebox"  //작업실은 cookiebox, 집은 !1


RF24 radio(16, 0);     // SPI통신을 위한 (CE, CSN) 핀 선언  

const byte address[6] = "00001"; // 송신기와 수신기가 동일한 값으로 주소 설정함(5자리)
String valuea;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver ();

#define FREQUENCY 58  //전류 값
int ang_min =  100;
int ang_max  = 550  //범위를 넘어 서면 제대로 작동 안함 

#define ang_max_2 540 //다른 사이즈 설정 
//릴레이
const uint8_t relay_sgl = 15;
 String string_toogle;

//서보 핀
//const uint8_t servo_sgl_1 = 16; //d2번 핀  됨
//const uint8_t servo_sgl_2 = 0; //d8 됨
//const uint8_t servo_sgl_3 = 2; // d9 됨
//const uint8_t servo_sgl_4 = 15; //D10

//const uint8_t servo_sgl_1 = 14; //d13번 핀 안되고 있음. 다시 테스트 요망
//const uint8_t servo_sgl_1 =  12;  //d12 xxxxx
//const uint8_t servo_sgl_1 = 13;  //d07 xxxxx
//const uint8_t servo_sgl_1 = A0; //

int gate_state[7] = {0, 0, 0, 0, 0, 0, 0};
int fire_state[7] = {0, 0, 0, 0, 0, 0, 0};


FirebaseData firebaseData;
FirebaseJson json;

 bool toogle = false;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  pinMode(relay_sgl, OUTPUT);
  digitalWrite(relay_sgl, HIGH);

  radio.begin();
  radio.openReadingPipe(0, address);// 데이터를 받을 송신기 주소를 설정
  radio.setPALevel(RF24_PA_HIGH); // 송신거리에 따른, 전원공급 파워레벨 설정
 radio.setDataRate( RF24_250KBPS );
  //(최소) RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX (최대) 설정가능
  //송신이 약하다고 판단될 경우 nRF24모듈의 GND와 3.3V 단자에 전해콘덴서(10uF이상:+를3.3V연결)사용권장
  radio.startListening();   // 모듈을 수신기(상태)로 설정

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("와이파이에 연결");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  //Serial.print("IP에 연결");
  //Serial.println(WiFi.localIP());
  //Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //데이터 버퍼 크기 설정
  firebaseData.setBSSLBufferSize(1024, 1024);

  //대용량 데이터 작업시 HTTP 응답하는 버퍼 크기 설정.
  firebaseData.setResponseSize(1024);

  //데이터 베이스 읽기 시간 제한을 1분으로 설정 (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);  //1초 *60 = 1분이란 설정

  //tiny(가장 작은), small(작은), medium(중간), large and unlimited(무제한).
  //크기및 쓰기 제한 시간 소형 1초
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

      reset_fire();
      reset_servo();

}


void loop() {
  
  loop_fire();
  
  char text[5] = "";   // 데이터를 수신 받을 변수 설정
     delay(100);
  if (radio.available()) {
    radio.read(&text, sizeof(text)); // 수신되는 데이터 길이만큼 읽어 저장
    String string = text;  //스트링으로 변환 해줘야 if문이 인식을 한다.
    if (string.indexOf("AN01") != -1) {
      gate(0, 1, 0);
      gate_state[0] = 1;
    } else if (string.indexOf("AN00") != -1) {
      gate(0, 0, 0);
      gate_state[0] = 0;
    }
    else if (string.indexOf("ML01") != -1) {
      gate(1, 1, 0);
      gate_state[1] = 1;

    } else if (string.indexOf("ML00") != -1) {
      gate(1, 0, 0);
      gate_state[1] = 0;
    }
    else if (string.indexOf("PN01") != -1) {
      gate(2, 1, 0);
      gate_state[2] = 1;
    } else if (string.indexOf("PN00") != -1) {
      gate(2, 0, 0);
      gate_state[2] = 0;
    }
    else if (string.indexOf("TA01") != -1) {
      gate(3, 1, 0);
      gate_state[3] = 1;
    } else if (string.indexOf("TA00") != -1) {
      gate(3, 0, 0);
      gate_state[3] = 0;
    }
    else if (string.indexOf("SA01") != -1) {
      gate(4, 1, 0);
      gate_state[4] = 1;
    } else if (string.indexOf("SA00") != -1) {
      gate(4, 0, 0);
      gate_state[4] = 0;
    }
    else if (string.indexOf("BA01") != -1) {
      gate(5, 1, 0);
      gate_state[5] = 1;
    } else if (string.indexOf("BA00") != -1) {
      gate(5, 0, 0);
      gate_state[5] = 0;
    }
    else if (string.indexOf("CN01") != -1) {
      gate(6, 1, 0);
      gate_state[6] = 1;
    } else if (string.indexOf("CN00") != -1) {
      gate(6, 0, 0);
      gate_state[6] = 0;
    }
  }
 relay();
}



bool loop_fire(){
  if (Firebase.get(firebaseData, "Room_3/board_1")) {
    String value = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다.
    if (value != valuea) {
      firebase_get(value);
      valuea = value;
    }
  }
  toogle = false;
}





void relay(void){
    if (gate_state[0] == 1 or gate_state[1] == 1 or gate_state[2] == 1 or gate_state[3] == 1 or gate_state[4] == 1 or gate_state[5] == 1 or gate_state[6] == 1
      or fire_state[0] == 1 or fire_state[1] == 1 or fire_state[2] == 1 or fire_state[3] == 1 or fire_state[4] == 1 or fire_state[5] == 1 or fire_state[6] == 1) {
    digitalWrite(relay_sgl, HIGH);
  }
  else if (gate_state[0] == 0 and gate_state[1] == 0 and gate_state[2] == 0 and gate_state[3] == 0 and gate_state[4] == 0 and gate_state[5] == 0 and gate_state[6] == 0
           and fire_state[0] == 0 and fire_state[1] == 0 and fire_state[2] == 0 and fire_state[3] == 0 and fire_state[4] == 0 and fire_state[5] == 0 and fire_state[6] == 0) {
    digitalWrite(relay_sgl, LOW);
  }
}


void gate(int motor_int, int gate_int, int fire_int) {
  if (gate_int == 1 or fire_int == 1) {
    delay(100);
    pwm.setPWM(motor_int, 0, ang_min);


  }
  else if (gate_int == 0 and fire_int == 0) {
    delay(100);
    pwm.setPWM(motor_int, 0, ang_max);

  }
}

void firebase_get(String value) {
  String gate1_string = value.substring(11, 15);
  String gate2_string = value.substring(27, 31);
  String gate3_string = value.substring(43, 47);
  String gate4_string = value.substring(59, 63);
  String gate5_string = value.substring(75, 79);
  String gate6_string = value.substring(91, 96);
  String gate7_string = value.substring(108, 112);
  if (gate1_string == "AN01") {
    fire_state[0] = 1;
    gate(0, 0, 1);
  }
  else if (gate1_string == "AN00") {
    fire_state[0] = 0;
    gate(0, 0, 0);
  }
  else if (gate2_string == "ML01") {
    fire_state[1] = 1;
    gate(1, 0, 1);
  }
  else if (gate2_string == "ML00") {
    fire_state[1] = 0;
    gate(1, 0, 0);
  }
  else if (gate3_string == "PN01") {
    fire_state[2] = 1;
    gate(2, 0, 1);

  }
  else if (gate3_string == "PN00") {
    fire_state[2] = 0;
    gate(2, 0, 0);
  }
  else if (gate4_string == "TA01") {
    fire_state[3] = 1;
    gate(3, 0, 1);
  }
  else if (gate4_string == "TA00") {
    fire_state[3] = 0;
    gate(3, 0, 0);
  }
  else if (gate5_string == "SA01") {
    fire_state[4] = 1;
    gate(4, 0, 1);
  }
  else if (gate5_string == "SA00") {
    fire_state[4] = 0;
    gate(4, 0, 0);
  }
  else if (gate6_string == "BA01") {
    fire_state[5] = 1;
    gate(5, 0, 1);
  }
  else if (gate6_string == "BA00") {
    fire_state[5] = 0;
    gate(5, 0, 0);
  }
  else if (gate7_string == "CN01") {
    fire_state[6] = 1;
    gate(6, 0, 1);
  }
  else if (gate7_string == "CN00") {
    fire_state[6] = 0;
    gate(6, 0, 0);
  }
}

void reset_servo() {
  for (int i = 0; i < 7; i++) {
    gate(i, 1, 0);
  }
  delay(2000);
  for (int i = 0; i < 7; i++) {
    gate(i, 0, 0);
  }
  /* gate(0, 1, 0);
    gate(1, 1, 0);
    gate(2, 1, 0);
    gate(3, 1, 0);
    gate(4, 1, 0);
    gate(5, 1, 0);
    gate(6, 1, 0);

    delay(2000);
    gate(0, 0, 0);
    gate(1, 0, 0);
    gate(2, 0, 0);
    gate(3, 0, 0);
    gate(4, 0, 0);
    gate(5, 0, 0);
    gate(6, 0, 0);
  */
}

void reset_fire() {
  if (Firebase.get(firebaseData, "Room_3/board_1")) {
    String value1 = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다.
  }
  Firebase.setString(firebaseData, "Room_3/board_1/gate_1", "AN02");  //각도 절단기
  Firebase.setString(firebaseData, "Room_3/board_1/gate_2", "ML02");  //밀링
  Firebase.setString(firebaseData, "Room_3/board_1/gate_3", "PN02");  //자동 대패
  Firebase.setString(firebaseData, "Room_3/board_1/gate_4", "TA02");  //테이블 쏘
  Firebase.setString(firebaseData, "Room_3/board_1/gate_5", "SA02");  //샌딩
  Firebase.setString(firebaseData, "Room_3/board_1/gate_6", "BA02"); //밴드쏘
  Firebase.setString(firebaseData, "Room_3/board_1/gate_7", "CN02");  //CNC

}
