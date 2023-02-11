#include "spindle.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();
Spindle Spin(0,A0);
void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(51); //오작동 한다면 50Hz에서 조금씩 바꿔보기
  Spin.set_spindle();
}
void loop() {
long a = 0;
  if (Serial.available()) {
    a = Serial.parseInt(); //시리얼 통신으로 값을 받아옴
    int ra = constrain(map(a, 0, 180, 150, 600), 150, 600); //받은 값의 범위 0~180을 펄스길이150~600으로 매핑해주고, ra의 최소,최대를 150,600을 넘지 않게 해준다.
    pwm.setPWM(0,0,0); //pca9685모듈의 0번 포트에 연결된 서보를 ra만큼 회전
    pwm.setPWM(4,0,0);
    pwm.setPWM(8,0,0);
    pwm.setPWM(12,0,0);
    Serial.println(a);
    delay(1000);

    
  }
}
