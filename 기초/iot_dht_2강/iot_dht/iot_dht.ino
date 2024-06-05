//자동으로 제어되는 환풍기에, 수동으로(수동모드)로 on, off 할 수 있게 
//리모컨으로 제어. 
//수동모드 <==> 자동모드 

#include "DHT.h"   
#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#define DHTTYPE DHT11  


//DHT11 온습도 센서.
const uint8_t dht_sensor = 9;  
const uint8_t dht_vcc = 8;  
const uint8_t dht_gnd = 10; 
DHT dht(dht_sensor, DHTTYPE);  

//RELAY
const uint8_t relay_sgl = A0;  

//리모컨
const uint8_t ir_sgl = 5;
const uint8_t ir_vcc = 4;
const uint8_t ir_gnd = 3;

IRrecv ir(ir_sgl);   //신호를 받을    ir_sgl => ir별명 => IRrecv
decode_results res;;  // 신호를 해석할

int humi_on = 1;
int fan_on = 2;

void setup() {  //초기 설정 부분입니다 .
  Serial.begin(115200); //시리얼 모니터를 쓰기위해 시리얼 통신속도를 초기화 합니다 .
  //아두이노의 시리얼 통신 속도를 115200으로 합니다. 

  dht.begin(); //온도 센서 시작
  
  //온습도 센서에 설정
  pinMode(dht_vcc, OUTPUT); //핀을 설정합니다.pinMode(10, OUTPUT) = pinMode(dht_vcc,OUTPUT)와 같습니다 .
  //별칭을 적어 주는 습관이 좋습니다 .
  pinMode(dht_gnd, OUTPUT);  //GND를 설정합니다. 
  digitalWrite(dht_vcc, HIGH); //5V(HIGH)를 기본으로 설정한다.
  digitalWrite(dht_gnd, LOW); //0V(LOW = GND)


  //릴레이 설정
  pinMode(relay_sgl, OUTPUT); //릴레이 설정. 
  digitalWrite(relay_sgl, LOW);  //기본값을 설정하는데 기본 LOW로 되어 있습니다. 안하셔도 무방합니다.

  //리모컨 설정
  ir.enableIRIn();  //리모컨 수신 시작
  pinMode(ir_vcc, OUTPUT);
  pinMode(ir_gnd, OUTPUT);
  
  digitalWrite(ir_vcc, HIGH);
  digitalWrite(ir_gnd, LOW);

}

void loop() {

  float temp = dht.readTemperature(); //dht센서의 온도를 읽어서, 소수자리(float)로 표시하는 temp에 대입한다.
  float humi = dht.readHumidity();  //dht센서의 습도를 읽어서, humi에 대입한다.

  delay(500);

 /*
  0xFF807F = ON, 0xFF00FF = OFF, 0xFF30CF = 2H

  */
  if(ir.decode(&res)){
    Serial.print("리모컨 값");
    Serial.println(res.value, HEX);  //
    if(res.value == 0xFF807F){
      Serial.println("수동모드 팬on");
      digitalWrite(relay_sgl,HIGH);
      fan_on =1;
      humi_on = 2;
    }
    else if(res.value == 0xFF00FF){
     Serial.println("수동모드 팬OFF");
     digitalWrite(relay_sgl,LOW);
     fan_on = 0;
     humi_on = 2;
    }
    else if(res.value == 0xFF30CF){
      Serial.println("자동모드 복귀");
      fan_on = 2;
      humi_on = 1;
    }
    
  }
  delay(200);
  ir.resume();


  if (humi > 50 and humi_on == 1 or fan_on == 1) //만약에 humi( 습도 센서)의 값이, 70이상이라면,
  {
    digitalWrite(relay_sgl, HIGH);
    Serial.println(humi);
    Serial.println("릴레이가 켜졌다."); 
    //릴레이가 계속 켜져 있습니다. 
  }else if(humi <= 50 and humi_on == 1 or fan_on ==0){  //하지만 습도의 값이 10 이하로 되면 릴레이는 꺼질 것입니다. 
    digitalWrite(relay_sgl, LOW);
    Serial.println(humi);
    Serial.println("릴레이가 꺼졌다.");
  }


}
