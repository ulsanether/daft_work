

//온도 습도에 자동으로 제어가 됩니다.
//만약에, 내가 습도가 낮은데, 환기를 위해서 팬을 작동 시키고 싶을 경우.
//리모컨으로 작동을 시킨다. <켜거나, 끈다.>


//리모컨 라이브러리.
#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

//1. 환풍기(시로코 팬으로 작동하는 환풍기를 제어)
//2. 아두이노 + DHT11 +릴레이


#include "DHT.h" //라이브러리를 불러 옵니다. 
#define DHTTYPE DHT11 //DHT11센서의 별명은 DHTTYPE

//온습도 센서.
const uint8_t dht_sensor = 9;  //const(상수) uint8_t(8비트 정수) ,  dht_sensor = 9 대입
const uint8_t dht_vcc = 8; //5v == vcc
const uint8_t dht_gnd = 10; //gnd == 0v

DHT dht(dht_sensor, DHTTYPE);  //라이브러리에 클래스에 접근 할 수있다.

//릴레이
int relay_sgl = A0;
//+는 아두이노의 5v 핀에 꼽고, - gnd에 꼽았기에 정의할 필요가 없다.

//리모컨
const uint8_t ir_sgl = 5;
const uint8_t ir_vcc = 4;
const uint8_t ir_gnd = 3;

IRrecv ir(ir_sgl);
decode_results res;

//인터럽트
int ISR = 0; //off
int ir_sig_1 = 0;  //off

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);// 115200의 속도로 아두이노에서 -> 컴퓨터로, 혹은 다른 기기로 통신 하겠다.

  dht.begin(); //

  //인터럽트
  pinMode(2, INPUT_PULLUP); 
  attachInterrupt(0, ir_function, FALLING);

  pinMode(dht_vcc, OUTPUT);
  pinMode(dht_gnd, OUTPUT);

  pinMode(relay_sgl, OUTPUT);

  digitalWrite(dht_vcc, HIGH); //5V를 진짜로 줘 버리는것.
  digitalWrite(dht_gnd, LOW);; //0 OR gnd로 진짜로 만들어 버리는것입니다.

  //리모컨
  ir.enableIRIn(); //수신 시작
  pinMode(ir_vcc, OUTPUT);
  pinMode(ir_gnd, OUTPUT);

  digitalWrite(ir_vcc, HIGH);
  digitalWrite(ir_gnd, LOW);


}

void loop() {
  // put your main code here, to run repeatedly:

  float temp = dht.readTemperature(); //dht센서의 온도를 읽어서, temp 소수에 그 값을 대입합니다.
  //temp = 온도 센서의 값이 대입됩니다.
  float humi = dht.readHumidity(); //
  Serial.print("습도값 :");
  Serial.println(humi);
  delay(500); //1초 쉬고

  //만약에(if) 0xFF807E라고 리모컨에서 신호가 온다면, 릴레이 1번이 켜지고
  //그렇지만 만약에(else if) 0xFF00FF라고 리모컨에서 신호가 온다면, 릴레이 1번이 꺼진다.
  //또 그렇지만(else if)

  if (ir.decode(&res)) {
    //리모컨
    //on = 0xFF807F,off = 0xFF00FF , 2h = 0xFF30CF
    Serial.print("리모컨 주소는?? = ");
    Serial.println(res.value, HEX);
    if (res.value == 0xFF807F or ir_sig_1  == 1 ) { //ir_sig_1 원래라면 0이지만, 1이되면 릴레이가 켜진다.
      ir_sig_1 = 1;
      Serial.println("릴레이 1번이 켜진다.");
      digitalWrite(relay_sgl, HIGH);
      if (ISR == 1) {
        digitalWrite(relay_sgl, LOW);
        Serial.println("OFF");
        ISR = 0;
        ir_sig_1 = 0;
      }
    }
  }
  delay(200);
  ir.resume();
  if (humi > 50 || ir_sig_1 == 1) {

    Serial.println(humi);
    Serial.println("팬 동작");
    digitalWrite(relay_sgl, HIGH);
  } else if (humi < 49) {
    Serial.println("팬 멈춤");
    digitalWrite(relay_sgl, LOW);
  }

}

void ir_function() {
      ISR = 1; //ISR이라는 변수에 1이 들어갑니다. 그 전에는 ISR == 0, 2H라는 리모컨을 누르면
    //ISR 은 1이 됩니다.
  }
