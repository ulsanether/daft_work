/*
  LJ12A3-4-ZBX-Inductive-Proximity-Sensor
  made on 04 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home
*/

#include <ArduinoJson.h>

#define SETUP_T 1
const int Pin = 2;
const int rePin1 = 3;
const int rePin2 = 4;
const int spindle = 6;

int spindle_step = 0;
int lift_step =0;
String str = "";
StaticJsonDocument<200> doc;


void setup() {
  Serial.begin(9600);
  pinMode(spindle, OUTPUT);
  pinMode(Pin, INPUT);
  pinMode(rePin1, OUTPUT);
  pinMode(rePin2, OUTPUT);
  digitalWrite(rePin1, HIGH);
  digitalWrite(rePin2, HIGH);
  analogWrite(spindle, 0);
  while (!Serial) continue;
#if SETUP_T == 0
  first();
#endif
#if SETOP_T == 1
  first();
test_mode();
#endif

}

void test_mode() {
  Serial.println("111");
  digitalWrite(rePin1, HIGH);
  digitalWrite(rePin2, LOW);
  delay(1000);
  digitalWrite(rePin1, HIGH);    // 멈춤
  digitalWrite(rePin2, HIGH);
  delay(5000);
  digitalWrite(rePin1, LOW);    // ON(COM NO)
  digitalWrite(rePin2, LOW);
  delay(1000);
  digitalWrite(rePin1, HIGH);    // 멈춤
  digitalWrite(rePin2, HIGH);
  delay(5000);
  analogWrite(spindle, 255);
}



void first() {
  while (true) {
    int sensorValue = digitalRead(Pin);
    if (sensorValue != HIGH) {
      digitalWrite(rePin1, HIGH);    // 멈춤
      digitalWrite(rePin2, HIGH);
      break;
    }
    else {
      digitalWrite(rePin1, HIGH);
      digitalWrite(rePin2, LOW);
    }
  }
}

void loop() {
  if (Serial.available())
  {
    str = Serial.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, str);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
  }

  delay(1000);
  if(doc["lift_step"] < 4 && doc["lift_step"] != null ){
      Move_motor(lift_step);
  }

    if( doc["spindle_step"] < 256 && doc["spindle_step"] != null){
       Play_spindle(spindle_step);  //스핀들 속도 받아서
  }

 
  
}

void Play_spindle(int val) {
  static int val1;
  if (val1 == val) {
    return;
  }
  analogWrite(spindle, val);
  val1 = val;
  delay(100);

}

void Move_motor(int val) {
  static int val1;
  if (val1 == val) {
    return;
  }
  if (val == 1) {
    digitalWrite(rePin1, LOW);
    digitalWrite(rePin2, HIGH); // OFF(COM NC)
    Serial.println("a");
    delay(100);
  } else if (val == 2) { //역회전(왼방향)
    first();
  } else if (val == 3) { //스톱
    motor_stop();
  }
  val1 = val;

}

void motor_stop() {
  digitalWrite(rePin1, LOW);    // ON(COM NO)
  digitalWrite(rePin2, LOW);
  delay(1000);
  digitalWrite(rePin1, HIGH);    // 멈춤
  digitalWrite(rePin2, HIGH);
}
