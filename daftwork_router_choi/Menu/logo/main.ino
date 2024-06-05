
#include <math.h>  //연산 모듈
#include <SPI.h>
#include <U8g2lib.h>   //lcd 모듈
#include "ClickEncoder.h"  //로타리 엔코더 
#include "Menu.h"
#include "pin_map.h"
#include "logo.h"
#include "DHT.h"
#include <EEPROM.h>
#include <AccelStepper.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#define DHTTYPE DHT11
DHT dht(dht_sgl, DHTTYPE);

bool Running = true;   //
int units = 0; // Celcius 메뉴 번호
char *menu_current[20];   //매뉴의 배열 갯수
uint8_t menu_item_current  = 0; //메뉴 아이템 흐름
uint8_t menu_length_current  = 0;  //매뉴 길이 흐름
uint8_t menu_redraw_required = 0;  //메뉴 다시 그리기
int16_t last, value;                  // 엔코더 위치 저장할 변수
float Temp_C  = 0;
unsigned int sensorReadFreq = 1; // 센서의 읽는 hz주파수
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, DOGLCD_SCK , DOGLCD_MOSI, DOGLCD_CS ); // Initialize graphics controller
ClickEncoder *encoder;                //Create instance of ClickEncoder class




#define KEY_NONE 0
#define KEY_NONE1 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

#define MENU_ITEMS 3
#define MEM_ITEMS 4

const char *menu_strings[MENU_ITEMS];
const char *mem_strings[MEM_ITEMS];
uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;
uint8_t last_key_code = KEY_NONE;
float router = 0;
float ver = 0;
float ver1 = 0;
float ver2 = 0;
int toogle = 1;
int menu_state = 1;
int zero_state = 0;
int val;

//tb6600 모터 드라이버 핀번호
const uint8_t dirPin = 11;  //
const uint8_t stepPin = 13;  //
AccelStepper stepper = AccelStepper(1, stepPin, dirPin);
//스탭당 이동거리
int Move_high = 160;
int Move_low  = -160;




void setup() {
  Serial.begin(115200);
  u8g2.enableUTF8Print();
  dht.begin();

  pinMode(KILL_PIN, INPUT_PULLUP);


  //set up Menu
  memcpy(menu_current, menu_setup, sizeof(menu_setup));
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
  OCR1A = round(16000000 / 256 / sensorReadFreq);        // compare match register 16MHz/256/1Hz
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

}

ISR(TIMER2_COMPA_vect)
{
  encoder->service();
}


void loop() {
  Temp_C = dht.readTemperature();        // read temperature from thermistor
  if (Running) {  //running가 참일때
    u8g2.firstPage();
    do {
      drawMenu(menu_setup, *(&menu_setup + 1) - menu_setup);
      u8g2.setCursor(10, 20);

      switch (units) {
        case 0:
          if (menu_redraw_required != 0 ) {  //들어 가긴 하는데, 무한 반복이 되지 않는다. 토글을 넣을것

            u8g2.firstPage();
            do {
              actMenu();

            } while ( u8g2.nextPage());
            menu_redraw_required = 0;
          }

          break;
        case 1:

          break;
        case 2:

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

  // 클릭 했을 겨웅
  value += encoder->getValue();    //
  if (value < 0) {
    value = 0;
  }
  if (value > menu_length_current - 1) {
    value = menu_length_current - 1;
  }
  if (value != last) {
    Serial.print("Encoder Value: ");  //휠값 업데이트 함수
    Serial.println(value);
    updateMenu(value);                            // update menu bar
    last = value;
  }


  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Clicked:  //클릭 함수
        Serial.println("ClickEncoder::Clicked");
        if (Running == 0) {
          menu_redraw_required = 1;

          menuClick(value);
        } else {
          Running = 0;
        }
        break;
      case ClickEncoder::Pressed:
        Serial.println("ClickEncoder::Pressed");  //일반 클릭 함수
        break;
      case ClickEncoder::DoubleClicked:
        Serial.println("ClickEncoder::DoubleClicked");  //더블 클릭 함수
        break;
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
  u8g2.drawBitmap( 5, 2, 6, 64, top_menu);
  u8g2.drawLine(60, 5, 60, 59);
  u8g2.drawFrame(0, 0, 128, 64);

  h = u8g2.getFontAscent() - u8g2.getFontDescent();
  w = u8g2.getWidth();
  for (  i = 0; i < menu_len; i++ ) {
    d = (w - u8g2.getStrWidth(menu[i]) / 3);
    u8g2.setDrawColor(2);
    if ( i == menu_item_current ) {
      u8g2.drawBox(6, i * (h + 7) + 2, w / 3 + 2, h + 6); //위치값 나중에 좀더 수정.
      u8g2.setDrawColor(0);
      u8g2.drawUTF8(d, i * (h + 1) , menu[i]);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawUTF8(d, i * (h + 1) , menu[i]);
    }
  }
  if (menu_item_current == 0) {
    u8g2.drawBitmap( 70, 7, 6, 48, icon1);
  }
  else if (menu_item_current == 1) {
    u8g2.drawBitmap( 70, 7, 6, 48, icon2);
  }
  else if (menu_item_current == 2) {
    u8g2.drawBitmap( 70, 7, 6, 48, icon3);
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
