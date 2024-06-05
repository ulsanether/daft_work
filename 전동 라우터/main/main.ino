       
#include <SPI.h> //SPI 통신을 위해서는 MOSI, MISO, SCK, SS 핀이 필요하다. 
#include <math.h>  //연산 모듈 
#include <EEPROM.h>  //메모리 모들
#include <U8g2lib.h>   //lcd 모듈
#include <AccelStepper.h>  //스탭모터 모듈


#include "ClickEncoder.h"  //로타리 엔코더 
#include "pin_map.h"
#include "logo.h"
#include "DHT.h"
#include "ze_menu.h"
#include "ui_menu.h"
#include "r_menu.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DHTTYPE DHT11

uint8_t mem_current = 0;  //256 정수 

//메뉴 수
const char *menu_setup[] = {"", "", ""}; //메인 메뉴의 숫자 
//메모리 주소 힙이라는 공간에 문자열을 저장하기 위한

DHT dht(dht_sgl, DHTTYPE);  //객체 만들었다. 


//int btn = 0; //나중에 영점 엔드 스톱 설정

bool Running = true;   //
int units = 10; // Celcius 메뉴 번
char *menu_current[20];   //매뉴의 배열 갯수

uint8_t menu_item_current  = 0; //메뉴 아이템 흐름
uint8_t menu_length_current  = 0;  //매뉴 길이 흐름

uint8_t menu_redraw_required = 0;  //메뉴 다시 그리기
int16_t last, value;                  // 엔코더 위치 저장할 변수

float humi = 0;
float temp = 0;

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, DOGLCD_SCK , DOGLCD_MOSI, DOGLCD_CS ); // Initialize graphics controller


ClickEncoder *encoder;                //Create instance of ClickEncoder class


//임시 토글
uint8_t menu_toogle = 0;

const char *menu_strings[MENU_ITEMS];


float router = 0;

int toogle = 1;
int menu_state = 1;
int zero_state = 0;
int val;

uint8_t kill_button_stat;

AccelStepper stepper = AccelStepper(1, X_STEP_PIN, X_DIR_PIN);
//스탭당 이동거리

char s_temp[5];
char s_humi[5];

const char SYMBOL[] = { 0xB0, '\0' };

int end_State = 0;

void setup() {
  Serial.begin(115200);
  u8g2.enableUTF8Print();
  dht.begin();

  pinMode(KILL_PIN, INPUT_PULLUP);  //
  pinMode(end_PIN, INPUT_PULLUP);  //
  stepper.setMaxSpeed(30000);
  stepper.setAcceleration(30000);

  //set up Menu
  memcpy(menu_current, menu_setup, sizeof(menu_setup));//메모리 설정 
  menu_length_current = *(&menu_setup + 1) - menu_setup ;
  menu_redraw_required = 1;     // force initial redraw

  // set up click encoder
  //encoder = new ClickEncoder(BTN_EN2, BTN_EN1, BTN_ENC);
  encoder = new ClickEncoder(D33, D31, D35);
  last = -1;  //엔코더 변수에 -1을 준다.

  // initialize timers
  noInterrupts();           // disable all interrupts

  /*
     - TCCRA0A (Timer/Counter Control Register 0A) : 타이머/카운터 설정 레지스터 A
    - TCCRA0B (Timer/Counter Control Register 0B) : 타이머/카운터 설정 레지스터 B
    - TIMSK0 (Timer/Counter Interrupt Mask Register) : 타이머/카운터 활성화시키는 레지스터
    - TIFR0 (Timer/Counter Interrupt Flag Register) : 비교일치 or 오버플로우시 발생시 Flag 레지스터
    - TCNT0 (Timer/Counter Register) : 분주된 타이머/카운터가 저장되는 레지스터
    - OCR0A (Output Compare Register) : 비교일치를 위해 값을 저장하는 레지스터
  */
  // 센서 타이머 인터럽트 설정.
  TCCR1A = 0; //타이머 //카운터 설정 레지스터 1a
  TCCR1B = 0; //1b
  TCNT1  = 0; // 분주된 타이머/ 카운터가 저장되는 레지스터는 0이다.
  OCR1A = round(16000000 / 1024 / 1000);        // compare match register 16MHz/256/1Hz
  //비교 일치를 위해 값을 저장하는 레지스터
  TCCR1B |= (1 << WGM12);   // CTC mode  //좌우 항 or연산을 하고  대입
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  // encoder read timer
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = round(16000000 / 1024 / 1000);        // compare match register e.g. 16MHz/1024/100Hz
  TCCR2B |= (1 << WGM12);   // CTC mode
  TCCR2B |= (1 << CS12) | (1 << CS10);  // 1024 prescaler
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts

  u8g2.begin(); // Write startup message to LCD
  u8g2.setFontPosTop(); // references position to top of font
  do {
    u8g2.setFont(u8g2_font_unifont_t_korean1);
    u8g2.setFontDirection(0);
    u8g2.drawBitmap( 0, 0, 16, 64, logo);
  } while ( u8g2.nextPage() );
  delay(1500);
  // Menu splash screen
}

// ----------------------------------------------------------------------------
// TIMER ISRs
// ----------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
  end_State = digitalRead(end_PIN);
  if (end_State == 0) {
    router = 0;
    stepper.stop();
  }
}

ISR(TIMER2_COMPA_vect)
{
  encoder->service();
}


void loop() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  dtostrf(temp, 3, 1, s_temp); 
  dtostrf(humi, 3, 1, s_humi);
//=============================================================================

  if (Running) {  //running가 참일때
    u8g2.firstPage();
    do {
      drawMenu(menu_setup, *(&menu_setup + 1) - menu_setup);
      u8g2.setCursor(10, 20);
      switch (units) {  //클릭시 진입
        case 0:
            actMenu();  //ui_memu
          units = 10;
          break;
        case 1:
            zeroMenu();  //ui_memu
          units = 10;
          break;
        case 2:
          memMenu();  //ui_memu
          units = 10;
          break;
      }
    } while ( u8g2.nextPage() );
  } else {    //Draw Menu
    if (menu_redraw_required != 0) {
      u8g2.firstPage();
      do  {
        drawMenu(menu_setup, *(&menu_setup + 1) - menu_setup  );
      } while ( u8g2.nextPage() );
      menu_redraw_required = 0;
    }
  }

  //======================================================================================

  value += encoder->getValue();    //
  if (value < 0) {
    value = 0;
  }
  if (value > menu_length_current - 1) {
    value = menu_length_current - 1;
  }
  if (value != last) {
    Serial.print("휠값: ");  //휠값 업데이트 함수
    Serial.println(value);   //휠의 위치값
    updateMenu(value);                            // update menu bar
    last = value;
  }


  //====================================================================================


  ClickEncoder::Button b = encoder->getButton();
  if ((b != ClickEncoder::Open)  || (digitalRead(KILL_PIN) == LOW)) {
    switch (b) {
      case ClickEncoder::Clicked:  //클릭 함수
        Serial.println("ClickEncoder::Clicked");
        menu_redraw_required = 1;
        menuClick(value);
        break;
      case ClickEncoder::Pressed:
        Serial.println("ClickEncoder::Pressed");  //
        break;
      case ClickEncoder::DoubleClicked:
        Serial.println("ClickEncoder::DoubleClicked");  //더블 클릭 함수
        break;
    }
    if (digitalRead(KILL_PIN) == LOW) {
      Serial.println("stop");
      Serial.println(digitalRead(KILL_PIN));
      Running = 0;
    }
  }
}


// ----------------------------------------------------------------------------
// MENU HANDLING ROUTINES
// ----------------------------------------------------------------------------
void drawMenu(const char *menu[], uint8_t menu_len) {
  uint8_t i, h;
  u8g2_uint_t w, d;

  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_helvB10_tf);
  u8g2.drawUTF8(7, 51, s_temp);
  u8g2.drawUTF8(36, 51, SYMBOL);
  u8g2.drawUTF8(40, 51, "C");
  u8g2.drawUTF8(80, 51, s_humi);
  u8g2.drawStr(110, 51, "%");
  u8g2.drawBitmap( 5, 2, 6, 47, top_menu);
  u8g2.drawLine(60, 4, 60, 46);
  u8g2.drawLine(60, 53, 60, 60);
  u8g2.drawFrame(0, 0, 128, 50);
  h = u8g2.getFontAscent() - u8g2.getFontDescent();
  w = u8g2.getWidth();
  for (  i = 0; i < menu_len; i++ ) {
    d = (w - u8g2.getStrWidth(menu[i]) / 3);
    u8g2.setDrawColor(2);
    if ( i == menu_item_current ) {
      u8g2.drawBox(6, i * h + 3, w / 3 + 2, h + 1); //위치값 나중에 좀더 수정.
      u8g2.setDrawColor(0);
      u8g2.drawUTF8(d, i * (h + 1) , menu[i]);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawUTF8(d, i * (h + 1) , menu[i]);
    }
  }
  if (menu_item_current == 0) {
    u8g2.drawBitmap( 75, 5, 5, 40, icon1);
  }
  else if (menu_item_current == 1) {
    u8g2.drawBitmap( 75, 5, 5, 40, icon2);
  }
  else if (menu_item_current == 2) {
    u8g2.drawBitmap( 75, 5, 5, 40, icon3);
  }
}




void updateMenu(int i) {
  menu_item_current  = i;
  menu_redraw_required = 1;
}



void menuClick( uint8_t _value) {   //누르고 나면 실행되는 함수
  Serial.print("menuClick\t");
  Serial.println(_value);  //값
  units = _value;
  Running = true;
}
