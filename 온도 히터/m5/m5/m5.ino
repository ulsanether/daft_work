#include "M5Stack.h"
int RawValue= 0;
int ThermistorPin = 35;  
int d1 = 25;
int Vo;  
float R1 = 10000;  
float logR2, R2, T, Tc, Tf;  
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;  
int Sum;
double tempC = 0;
double minTemp = 200;
double maxTemp = 0;
void setup() {  
    analogReadResolution(12);
    analogSetWidth(10);
    M5.begin(true, false, false, false); //lcd, sd카드, 직렬통신, i2c 순서로
  M5.Power.begin();
    M5.Speaker.begin(); //Initialize the speaker
Serial.begin(9600);  
pinMode(d1,OUTPUT);
 M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
  delay(2000);
  M5.Lcd.setTextSize(6);
}  
  
void loop() {  
     Sum = 0;
    M5.update();
       for(int k=1;k<=100;k++) {
  RawValue = analogRead(ThermistorPin);  
      Sum += RawValue;
   }
   Vo = Sum / 100;
   Serial.println(Vo);
  R2 = R1 * (1024.0 / (float)Vo - 1.0);  
  logR2 = log(R2);  
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));  
  Tc = T - 273.15;  //온도 
 tempC = Tc/2;
   if(tempC > maxTemp)
      maxTemp = tempC;
   if(tempC < minTemp)
      minTemp = tempC;      
   Serial.println(tempC,1);
   M5.Lcd.fillRect(140, 40, 170, 190, YELLOW);
   M5.Lcd.setTextSize(4);
   M5.Lcd.setTextColor(BLUE);
   M5.Lcd.setCursor(175, 80);
   M5.Lcd.printf("%.1f",tempC);
   M5.Lcd.setTextSize(2);
   M5.Lcd.setTextColor(BLACK);
   M5.Lcd.setCursor(170, 150);
   M5.Lcd.printf("MIN: %.1f",minTemp);
   M5.Lcd.setCursor(170, 190);
   M5.Lcd.printf("MAX: %.1f",maxTemp);

  Tf = (Tc * 9.0)/ 5.0 + 32.0;    //화씨 
  if(Tc >50.0){
digitalWrite(d1,LOW );
     Serial.println(Tc);
     Serial.println("OFF");

  }else{
    digitalWrite(d1, HIGH);
         Serial.println(Tc);
       Serial.println("ON");

  }
  delay(500);

  
}  
