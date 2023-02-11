  
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define current_max 525  //릴레이가 트리거 해야 하는 아날로그 값
#define current_period 500 //전류 값을 샘플링할 밀리초 

#define off_delay 5000 //전류값을 읽고 공구가 차단 되기까지 지연 시간, 집진기가 꺼지는 시간
//5초 후에 꺼저야지 나머지 먼지가 잘 집진된다.

//전류 센서
const uint8_t acs_vcc = 4; //VCC
const uint8_t acs_in = A3;  //전류 센서 핀
const uint8_t acs_gnd = 5; //GND

int acs_current = 0;
unsigned long start_time = 0;
//7 8
RF24 radio(7,8); // SPI통신을 위한 (CE, CSN) 핀 선언
const byte address[6] = "00001"; // 송신기와 수신기가 동일한 값으로 주소 설정함(5자리)

boolean toogle  = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(acs_vcc, OUTPUT);
  pinMode(acs_in, INPUT);
  pinMode(acs_gnd, OUTPUT);

  digitalWrite(acs_vcc, HIGH);
  digitalWrite(acs_gnd, LOW);


  radio.begin();
  radio.openWritingPipe(address); // 데이터를 보낼 수신 주소를 설정
  radio.setPALevel(RF24_PA_LOW); // 송신거리에 따른, 전원공급 파워레벨 설정
  //(최소) RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX (최대) 설정가능
  //송신이 약하다고 판단될 경우 nRF24모듈의 GND와 3.3V 단자에 전해콘덴서(10uF이상:+를3.3V연결)사용권장

  radio.stopListening();  // 모듈을 송신기로 설정




}
void loop() {
  acs_current = 0; //스테이트 초기화
  start_time = millis();  //밀리스라는 함수안에 프로그램이 시작된 후의 시간이 저장되어 있다.

  //시작 기간 동안 현제 센서에서 측정된 최대 전류 값을, 아날로그 밸류 변수에 저장
  while (millis() - start_time < current_period) {
    acs_current = max(acs_current, analogRead(acs_in));
    Serial.println("전류 값");
    Serial.println(acs_current);
  }

  if (acs_current > current_max) { //최대 전류 값이 한계를 초과할 경우 상태를 low로 설정
    Serial.println("PN ON.");
    delay(500);
    Serial.println(acs_current);
    if(toogle == LOW){
    char text[] = "PN01"; // 송신할 문자
    radio.write(&text, sizeof(text)); // 위 문자를 문자 길이 만큼 송출함
    toogle = HIGH;
    }
  }else { //그렇지 않으면 릴레이가 low일 경우 4초 정도를 기다린후에 high
      Serial.println("집진기가 꺼집니다.");
      delay(500);
      if(toogle == HIGH){
      char text1[] = "PN00"; // 송신할 문자
       Serial.println("보냅니다.");
      radio.write(&text1, sizeof(text1)); // 위 문자를 문자 길이 만큼 송출함
      toogle = LOW;
      }
    
  }


}
