
#include <CarrotPushButton.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

// These pins will also work for the 1.8" TFT shield

//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0
#define TFT_MISO 0

#define BUTTON 5
#define BUTTON1 18
#define BUTTON2 19


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

CarrotPushButton button;
CarrotPushButton button1;
CarrotPushButton button2;


int val = 0;
void IRAM_ATTR muk()
{
    button1.run();
  val  =  random(0, 10);
 Serial.println("111");
}



void IRAM_ATTR jji()
{
    button2.run();
  val  =  random(0, 10);
 Serial.println("111");
}
void IRAM_ATTR bba()
{
    button3.run();
  val  =  random(0, 10);
 Serial.println("222");
}

void setup(void)
{

  button.setPin(BUTTON);
  button.setPin(BUTTON1);
  button.setPin(BUTTON2);


  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);

  randomSeed(analogRead(0));
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);


  attachInterrupt(digitalPinToInterrupt(BUTTON), muk, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), jji, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), bba, FALLING);
  game_start();
}



void loop() {

  //win();
  //gui_basic();
  //test();
}


void win_loss() {

  if (val > 3) {
    Serial.print("졌음");
  } else if (val > 7) {
    Serial.print("비김");
  } else if (val > 10) {
    Serial.println("이김");
  }
}

void gui_basic() { //게임 시작
  tft.drawCircle(64, 90, 10, ST77XX_GREEN );
  delay(10);
  tft.drawCircle(64, 90, 10, ST77XX_BLACK );
  delay(10);
  tft.drawRect(64, 90, 10, 10, ST77XX_RED );
  delay(10);
  tft.drawRect(64, 90, 10, 10, ST77XX_BLACK);
  delay(10);

}

void game_start() {

  tft.drawCircle(64, 90, 30, ST77XX_WHITE );
}


void win() {

  for (int i = 0; i < 10; i++) {
    tft.fillCircle ( 115, 35, 10, ST77XX_BLACK ) ; //아래 동그라미
    tft.fillCircle ( 10, 35, 10, ST77XX_WHITE ) ; //아래 왼쪽 동그라미
    delay(100);
    tft.fillCircle ( 10, 35, 10, ST77XX_BLACK ) ; //아래 왼쪽 동그라미
    tft.fillCircle ( 115, 35, 10, ST77XX_WHITE ) ; //아래 동그라미
    delay(100);

  }
}

void test() {
  //tft.fillCircle ( 10,145, 10, ST77XX_BLACK ) ; //아래 왼쪽 동그라미
  //tft.fillCircle ( 10,35, 10, ST77XX_WHITE ) ; //아래 동그라미
  //tft.fillCircle ( 115,145, 10, ST77XX_WHITE ) ; //아래 오른쪽 동그라미
  //tft.fillCircle ( 115,35, 10, ST77XX_WHITE ) ; //아래 동그라미

  int i = 0;
  while (i < 20) {
    tft.fillCircle(41, 52, 5, ST77XX_BLACK); //11
    tft.fillCircle(64, 45, 5, ST77XX_WHITE ); //12시
    delay(100);
    tft.fillCircle(64, 45, 5, ST77XX_BLACK ); //12시
    tft.fillCircle(87, 52, 5, ST77XX_WHITE); //1
    delay(100);
    tft.fillCircle(87, 52, 5, ST77XX_BLACK); //1
    tft.fillCircle(103, 68, 5, ST77XX_WHITE); //2
    delay(100);
    tft.fillCircle(103, 68, 5, ST77XX_BLACK); //2
    tft.fillCircle(108, 90, 5, ST77XX_WHITE); //3
    delay(100);
    tft.fillCircle(108, 90, 5, ST77XX_BLACK); //3
    tft.fillCircle(103, 113, 5, ST77XX_WHITE); //4
    delay(100);
    tft.fillCircle(103, 113, 5, ST77XX_BLACK); //4
    tft.fillCircle(87, 129, 5, ST77XX_WHITE); //5
    delay(100);
    tft.fillCircle(87, 129, 5, ST77XX_BLACK); //5
    tft.fillCircle(64, 135, 5, ST77XX_WHITE); //6
    delay(100);
    tft.fillCircle(64, 135, 5, ST77XX_BLACK); //6
    tft.fillCircle(41, 129, 5, ST77XX_WHITE); //7
    delay(100);
    tft.fillCircle(41, 129, 5, ST77XX_BLACK); //7
    tft.fillCircle(26, 113, 5, ST77XX_WHITE); //8
    delay(100);
    tft.fillCircle(26, 113, 5, ST77XX_BLACK); //8
    tft.fillCircle(18, 90, 5, ST77XX_WHITE); //9
    delay(100);
    tft.fillCircle(18, 90, 5, ST77XX_BLACK); //9
    tft.fillCircle(26, 68, 5, ST77XX_WHITE); //10
    delay(100);
    tft.fillCircle(26, 68, 5, ST77XX_BLACK); //10
    tft.fillCircle(41, 52, 5, ST77XX_WHITE); //11
    delay(100);
    i++;
  }

}
