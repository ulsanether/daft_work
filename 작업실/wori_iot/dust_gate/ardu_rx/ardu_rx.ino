//신작동
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
  2021-10-28
  ether
  hangmini12@naver.com
  =================================================================
*/



#include <Wire.h>  //i2c통신을 위한 라이브러리
#include <Adafruit_PWMServoDriver.h>  //서보 모터 라이브러리

#include <SPI.h>  //spi통신
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN 9  //통신 핀 설정
#define CSN_PIN 10

#define relay_sgl 6  //릴레이 핀 설정
#define relay_gnd 7//나중에 핀 설정 할것 

//초기 전류 값

#define FREQUENCY 58

//각도
#define ang_max  100  //열렸을때  //100
#define ang_min  550  //닫혔을때  //650

int motor_int;
int gate_int;
int gate_state[7];


RF24 radio(CE_PIN, CSN_PIN);     // SPI통신을 위한 (CE, CSN) 핀 선언
//sck= 13, miso = 12, mosi = 11, scn = 10, ce = 9
//모듈 없을경우 vcc = 3v

const byte address[6] = "00001"; // 송신기와 수신기가 동일한 값으로 주소 설정함(5자리)
String valuea;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver (0x41);
//SDL = a4, scl = a5




void setup() {
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  pinMode(relay_sgl, OUTPUT);
  digitalWrite(relay_sgl, LOW);
  pinMode(relay_gnd, OUTPUT);
  digitalWrite(relay_gnd, LOW);



  Serial.println("111");
  reset_servo();
}


void loop() {

  char text[5] = "";

  if (radio.available()) {
    radio.read(&text, sizeof(text)); // 수신되는 데이터 길이만큼 읽어 저장
    String string  = text;
    Serial.println(string);
    if (string.indexOf("AN01") != -1) {
      gate_servo(0, 1);  //클래스명 수정
      gate_state[0] = 1;
    } else if (string.indexOf("AN00") != -1) {
      gate_servo(0, 0);
      gate_state[0] = 0;   
    } else if (string.indexOf("ML01") != -1) {
      gate_servo(1, 1);
      gate_state[1] = 1;
    } else if (string.indexOf("ML00") != -1) {
      gate_servo(1, 0);
      gate_state[1] = 0;
    }
    else if (string.indexOf("PN01") != -1) {
      gate_servo(2, 1);
      gate_state[2] = 1;

    } else if (string.indexOf("PN00") != -1) {
      gate_servo(2, 0);
      gate_state[2] = 0;
    }
    else if (string.indexOf("TA01") != -1) {
      gate_servo(3, 1);
      gate_state[3] = 1;
    } else if (string.indexOf("TA00") != -1) {
      gate_servo(3, 0);
      gate_state[3] = 0;
    }
    else if (string.indexOf("SA01") != -1) {
      gate_servo(4, 1);
      gate_state[4] = 1;
    } else if (string.indexOf("SA00") != -1) {
      gate_servo(4, 0);
      gate_state[4] = 0;
    }
    else if (string.indexOf("BA01") != -1) {
      gate_servo(5, 1);
      gate_state[5] = 1;
    } else if (string.indexOf("BA00") != -1) {
      gate_servo(5, 0);
      gate_state[5] = 0;
    }
    else if (string.indexOf("CN01") != -1) {
      gate_servo(6, 1);
      gate_state[6] = 1;
    } else if (string.indexOf("CN00") != -1) {
      gate_servo(6, 0);
      gate_state[6] = 0;
    }

  }
  relay();
}




void gate_servo(int motor_int, int gate_int) {
  if (gate_int == 1 ) {
    delay(100);
    pwm.setPWM(motor_int, 0, ang_max);
    Serial.println("on");
    delay(1000);

    //pwm.setPWM(motor_int, 0, 4096); 핀을 키는것

  }
  else if (gate_int == 0 ) {
    delay(100);
    pwm.setPWM(motor_int, 0, ang_min);
    Serial.println("off");
    delay(1000);
    //pwm.setPWM(motor_int, 0, 4096); 핀을 키는것
    //pwm.setPWM(motor_int, 0, 4096);  //핀을 끄는것
  }
}


void relay() {

  if (gate_state[0] == 1 or gate_state[1] == 1 or gate_state[2] == 1 or gate_state[3] == 1 or gate_state[4] == 1 or gate_state[5] == 1 or gate_state[6] == 1
     ) {
    digitalWrite(relay_sgl, HIGH);
    
  }
  else if (gate_state[0] == 0 and gate_state[1] == 0 and gate_state[2] == 0 and gate_state[3] == 0 and gate_state[4] == 0 and gate_state[5] == 0 and gate_state[6] == 0) {
    digitalWrite(relay_sgl, LOW);
  }
}


void reset_servo() {

     gate_servo(1, 1);
     gate_servo(2, 1);
     gate_servo(3, 1);
     gate_servo(4, 1);
     gate_servo(5, 1);
     gate_servo(6, 1);

    delay(2000);
     gate_servo(0, 0);
     gate_servo(1, 0);
     gate_servo(2, 0);
     gate_servo(3, 0);
     gate_servo(4, 0);
     gate_servo(5, 0);
     gate_servo(6, 0);
  
}
