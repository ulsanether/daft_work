

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define on_btn 2  //버튼 인터럽트를 위해  

#define lcd_vcc A3
#define lcd_gnd A2

#define relay_vcc 9
#define relay_gnd 8

bool btn_toogle = false;
int ThermistorPin = A0;
int d1 = 10;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

unsigned long past = 0;
int flag = 0;
bool time_toogle = false;


void setup() {
  //-------lcd
  pinMode(lcd_vcc, OUTPUT);
  pinMode(lcd_gnd, OUTPUT);
  digitalWrite(lcd_vcc, HIGH); //5v
  digitalWrite(lcd_gnd, LOW); //gnd

  ///릴레이  or 모스펫
  pinMode(relay_vcc, OUTPUT);
  pinMode(relay_gnd, OUTPUT);
 // digitalWrite(relay_vcc, HIGH); //5v
  digitalWrite(relay_gnd, LOW); //gnd

  //버튼
  pinMode(on_btn, INPUT_PULLUP);

  //lcd.init();
  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);
  pinMode(d1, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(on_btn),btn_sta,FALLING);
  

}


void temp_sensor() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;  //온도값
  Tf = (Tc * 9.0) / 5.0 + 32.0;   //화씨
  lcd.clear( );
  lcd.print("Temp :");
  lcd.println(Tc);
  lcd.print("Timer :");
  lcd.print(flag);
}



void loop() {
  temp_sensor();

  delay(1000);

}
  void btn_sta() { //인터럽트
    if (btn_toogle == true) {
      btn_toogle = false;
    } else {
      btn_toogle = true;
    }
  }
