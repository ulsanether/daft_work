#include "DHT.h"    //온습도 센서의 외부 모듈을 불러 옵니다.
//직접 제어를 할 수는 있지만 쉽지 않고 외부에 누가 만든 것을 쓰는게 효율적이기 때문입니다.
#define DHTTYPE DHT11  //온도 센서 DHT11 = DHTTYPE라고 정의 합니다. 


//DHT11 온습도 센서.
const uint8_t dht_sensor = 9;  //센서의 데이터 신호는 9번핀을 씁니다. 
const uint8_t dht_vcc = 10;  //5V는 10번핀
const uint8_t dht_gnd = 8;  //GND는 8번핀 
DHT dht(dht_sensor, DHTTYPE);  //위에서 정의된 값을 DHT dht(별칭)(센서, DHTTYPE)
//이러한 정의에 대한 것은 검색을 해 보시거나. 값을 읽어서 확인하시면 됩니다. 

//RELAY
const uint8_t relay_sgl = 12;  //릴레이는 VCC와 GND는 아두이노에있는 5V와 GND핀에 연결했고
//SGL값만 12번 핀을 씁니다. 
//당연한 얘기지만  const uint8_t realay_vcc = 5,6, a1 이렇게 해도 됩니다. 



void setup() {  //초기 설정 부분입니다 .
  Serial.begin(115200); //시리얼 모니터를 쓰기위해 시리얼 통신속도를 초기화 합니다 .
  //아두이노의 시리얼 통신 속도를 115200으로 합니다. 

  dht.begin(); //온도 센서 초기화  //온도 센서초기화 합니다

  pinMode(dht_vcc, OUTPUT); //핀을 설정합니다.pinMode(10, OUTPUT) = pinMode(dht_vcc,OUTPUT)와 같습니다 .
  //별칭을 적어 주는 습관이 좋습니다 .
  pinMode(dht_gnd, OUTPUT);  //GND를 설정합니다. 

  pinMode(relay_sgl, OUTPUT); //릴레이 설정. 
  
  digitalWrite(relay_sgl, LOW);  //기본값을 설정하는데 기본 LOW로 되어 있습니다. 안하셔도 무방합니다.
  
  digitalWrite(dht_vcc, HIGH); //5V(HIGH)를 기본으로 설정한다.
  digitalWrite(dht_gnd, LOW); //0V(LOW = GND)
}

void loop() {

  float temp = dht.readTemperature(); //dht센서의 온도를 읽어서, 소수자리(float)로 표시하는 temp에 대입한다.
  float humi = dht.readHumidity();  //dht센서의 습도를 읽어서, humi에 대입한다.

  delay(1000); //1초 == 1000, 10초 = 10000
  //온도 센서의 값을 읽기 위해서 연결 된 것이, 시리얼 창
  Serial.print("온도 :"); // print는 줄 바꿈 안함(enter x)
  Serial.println(temp); //시리얼(Serial.println 출력) 어떤 값을?  == temp == 온도 센서의 값을
  delay(2000);
  Serial.print("습도 :");
  Serial.println(humi); //
  delay(500);

  //습도는 70%이상으로 올라갈때 1번 릴레이에 연결된 환풍기가 켜집니다.
  //온도는 20도 이상올라갈때 2번 환풍기가 켜지거나 다른 연결된 무언가가 동작 하도록 합니다.



}
