
#include "FirebaseESP8266.h"
#include <FirebaseJson.h>
#include <ESP8266WiFi.h>
#include <MsTimer2.h> //타이머 인터럽트 
//타이머 인터럽트를 구성하는 경우 3번 9번핀을 출력으로 사용 못한니다.

//atmega == 아두이노 8비트
//8266 == 16비트 프로세서 wifi
//esp32 == 32비트 프로세서 wifi


//https://home-135e9-default-rtdb.firebaseio.com/
//

#define FIREBASE_HOST "home-135e9-default-rtdb.firebaseio.com"  //
#define FIREBASE_AUTH ""  //
#define WIFI_SSID "touchwood"
#define WIFI_PASSWORD "touchwood01##"  

FirebaseData firebaseData;  //객체
FirebaseJson json;

#define sensor_a 16
#define tr_pin 0
//d8 == tr
//d9 == ec
#define relay 5  //설정 아직 안함 



int one_min = 0;
int bumo = 1;
int flag = 0;
int fan_toogle_min;
double a = 0;
unsigned long past = 0;
String fan_tooogle = "Fan_01";
String get_fire;
int toogle_b = 0, toogle_a = 0;

bool one_min_t = true; //1분 작동 플래그

//인터럽트 타이머 사용하면 주석 해제
//int timer;
//int timer_t =0;

//밀리스
int five_sec = 0;


void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println();
  Serial.print("와이파이에 연결");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("IP에 연결");
  Serial.println(WiFi.localIP());
  Serial.println();
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

  //와치독

  Firebase.setString(firebaseData, "Room_2/Fan_01", fan_tooogle); // 자동모드 설정


  //timer = Firebase.getInt(firebaseData, "Room_2/Time");  //시간을 가져올 값

  //if(timer > 2000000000){  //값이 20억을 초과 하면
  // Firebase.setInt(firebaseData, "Room_2/Time",1); //1로 초기화
  //}


  pinMode(sensor_a, INPUT);
  pinMode(tr_pin, OUTPUT);
  //기본값 "Fan_01";
  //on == Fan_02;
  //off == Fan_03;
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW); //off로 설정



  //MsTimer2::set(10000, timerset);
  //MsTimer2::start();


  ESP.wdtEnable(10000);
  ESP.wdtFeed();

}




void loop() {

  sensor_val();  //센서값이 가까울 경우 팬을 작동한다
  //3시간마다 한번씩 팬을 작동한다
  Firebase_a();

  switch (bumo)  {
    case 1:
      if (toogle_a < 1000 or fan_toogle_min == 2) {
        if (flag > 10800) {
          if (one_min_t == true) {
            one_min = 0;
            one_min_t = false;
          }
          fan_toogle_min = 1;
        } else {
          //릴레이 off
          fan_toogle_min = 0;
        }
        fan_to(fan_toogle_min );
      }
      break;
    case 2:
      //팬 ON
      digitalWrite(relay, HIGH);
      break;
    case 3:
      digitalWrite(relay, LOW);
      //팬 off
      break;
  }
}


void sensor_val() { //센서값
  long duration, distance, value = 0;
  if (five_sec <= 5) {
    digitalWrite(tr_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(tr_pin, LOW);
    duration = pulseIn(sensor_a, HIGH);
    distance = ((double)(340 * duration) / 1000) / 2;
    delayMicroseconds(10);
    toogle_a = distance;  //현제 거리는 toogle_a로 확인 할것.
  } else {
    five_sec = 0;
  }


}

/*
  //파이어베이스 연결 타이머 안쓸 경우 인터럽트와 함게 제거
  void timerset(){  //무조건 3시간
  timer_t += 1;  //10초마다 1식 늘어 난다
  if(timer_t > 6){  //3시간이 되면 0
    timer_t =0 ; 리셋
       timer+=1; // 파이어 베이스로 1분마다 1씩 올린다.
  }

  }

*/


void time_a() {
  unsigned long now = millis(); //70일쯤 0
  if (now - past >= 1000) { //1초
    past = now;
    flag += 1;  //540 == 3  //3시간 변수
    one_min += 1;   //1분 세는 변수
    five_sec += 1;  //5초세는 변수

  }
} //5400 3시간
