
#define current_max 520  //릴레이가 트리거 해야 하는 아날로그 값
#define current_period 500 //전류 값을 샘플링할 밀리초 

#define off_delay 5000 //전류값을 읽고 공구가 차단 되기까지 지연 시간, 집진기가 꺼지는 시간
//5초 후에 꺼저야지 나머지 먼지가 잘 집진된다.

int acs_current = 0;  //현제 adc 전류 값. 센서에서 읽은
unsigned long start_time =0;
boolean relay_state = HIGH;

//전류 센서
const uint8_t acs_vcc = A0; //VCC
const uint8_t acs_in = A1;  //전류 센서 핀
const uint8_t acs_gnd = A2; //GND

//릴레이
const uint8_t relay_sgl = 7;  //릴레이


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(acs_vcc, OUTPUT);
  pinMode(acs_in, INPUT);
  pinMode(acs_gnd, OUTPUT);

  digitalWrite(acs_vcc, HIGH);
  digitalWrite(acs_gnd, LOW);

  pinMode(relay_sgl, OUTPUT);
 
}

void loop() {

  acs_current = 0; //스테이트 초기화 
  start_time = millis();  //밀리스라는 함수안에 프로그램이 시작된 후의 시간이 저장되어 있다.


  //시작 기간 동안 현제 센서에서 측정된 최대 전류 값을, 아날로그 밸류 변수에 저장
  while(millis() - start_time<current_period){
    acs_current = max(acs_current, analogRead(acs_in)); //max( , )두 수의 최대값을 계산
    Serial.println("전류 값");
    Serial.println(acs_current);
  }

  if(acs_current > current_max){  //최대 전류 값이 한계를 초과할 경우 상태를 low로 설정
    Serial.println("집진기가 켜집니다.");
    delay(2000);
    Serial.println(acs_current);
    relay_state = LOW;
    
  }
  else{  //그렇지 않으면 릴레이가 low일 경우 4초 정도를 기다린후에 high
    if(relay_state == LOW){
      Serial.println("집진기가 꺼집니다.");
      delay(4000);
      relay_state = HIGH;
      
    }
  }
  digitalWrite(relay_sgl,relay_state);
}
