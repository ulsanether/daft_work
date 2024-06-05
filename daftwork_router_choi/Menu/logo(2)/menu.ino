

/*

  오픈 테이블 라우터 소스. 

  hangmini12@naver.com
    
 
 */

#include <U8glib.h>
#include <EEPROM.h>
#include <AccelStepper.h>

U8GLIB_ST7920_128X64_4X u8g(5, 3, 4);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17


#define dirPin 12
#define stepPin 13

#define KEY_NONE 0
#define KEY_NONE1 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

const uint8_t uiKeyPrev = 2;
const uint8_t uiKeyNext = 6;
const uint8_t uiKeySelect = 8;
const uint8_t uiKeyBack = 9;

AccelStepper stepper = AccelStepper(1, stepPin, dirPin);

float router = 0;
float ver = 0;
float ver1 = 0;
float ver2 = 0;
int toogle = 1;
int menu_state = 1;
int zero_state = 0;
int val;

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;

#define MENU_ITEMS 3
#define MEM_ITEMS 4

const char *menu_strings[MENU_ITEMS];
const char *mem_strings[MEM_ITEMS];

uint8_t menu_current = 0;
uint8_t mem_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;

void drawMenu(void) {
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g.setFont(u8g_font_fub14);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  u8g.drawBitmapP( 5, 2, 6, 64, menu);
  u8g.drawLine(60, 5, 60, 59);
  u8g.drawFrame(0, 0, 128, 64);

  h = u8g.getFontAscent() - u8g.getFontDescent();
  w = u8g.getWidth();
  for ( i = 0; i < MENU_ITEMS; i++ ) {
    d = (w - u8g.getStrWidth(menu_strings[i]) / 3);
    u8g.setDefaultForegroundColor();

    if ( i == menu_current ) {
      u8g.drawFrame(6, i * h + 3, w / 3 + 2, h + 3);
    }
  }
  if (menu_current == 0) {
    u8g.drawBitmapP( 70, 7, 6, 48, icon1);
  }
  else if (menu_current == 1) {
    u8g.drawBitmapP( 70, 7, 6, 48, icon2);
  }
  else if (menu_current == 2) {
    u8g.drawBitmapP( 70, 7, 6, 48, icon3);
  }
}

void updateMenu(void) {

  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;

  switch ( uiKeyCode ) {
    case KEY_NEXT:
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
    case KEY_SELECT:
      if ( menu_current == 0 ) {
        actMenu();
        menu_state = 2;
      } else if (menu_current == 1) {
        zeroMenu();
        menu_state = 3;
      } else if (menu_current == 2) {
        memMenu();
        menu_state = 4;
      }
      break;
  }
}

void uiStep(void) {
  static unsigned long rotaryLastInterrupt = 0;
  unsigned long rotaryCurrentInterrupt = millis();

  if (rotaryCurrentInterrupt - rotaryLastInterrupt > 5) {
    uiKeyCodeSecond = uiKeyCodeFirst;
    if ( digitalRead(uiKeyPrev) == LOW ) {
      uiKeyCodeFirst = KEY_PREV;
    }
    else if ( digitalRead(uiKeyNext) == LOW ) {
      uiKeyCodeFirst = KEY_NEXT;
    }
    else if ( digitalRead(uiKeySelect) == LOW ) {
      uiKeyCodeFirst = KEY_SELECT;
    }
    else if ( digitalRead(uiKeyBack) == LOW )
      uiKeyCodeFirst = KEY_BACK;
    else
      uiKeyCodeFirst = KEY_NONE;

    if ( uiKeyCodeSecond == uiKeyCodeFirst )
      uiKeyCode = uiKeyCodeFirst;
    else
      uiKeyCode = KEY_NONE;
    rotaryLastInterrupt = rotaryCurrentInterrupt;
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(uiKeyPrev, INPUT_PULLUP);           
  pinMode(uiKeyNext, INPUT_PULLUP);          
  pinMode(uiKeySelect, INPUT_PULLUP);         
  pinMode(uiKeyBack, INPUT_PULLUP);          

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  
  menu_redraw_required = 1;     
  u8g.firstPage();
  do {
    u8g.drawBitmapP( 0, 0, 16, 64, logo);
  } while ( u8g.nextPage() );
  delay(1500);
}


void loop() {

  switch (menu_state) {
    case 1:
      uiStep();
      if (  menu_redraw_required != 0 ) {
        u8g.firstPage();
        do  {
          drawMenu();
        }
        while ( u8g.nextPage() );
        menu_redraw_required = 0;
      }
      updateMenu();
      break;

    case 2:
      uiStep();
      if (menu_redraw_required != 0 ) {
       
        u8g.firstPage();
        do {
          actMenu();
        } while ( u8g.nextPage());
        menu_redraw_required = 0;
      }
      
      updateact();
      break;

    case 3:
      uiStep();
      if (menu_redraw_required != 0 ) {

        u8g.firstPage();
        do {
          zeroMenu();
        } while ( u8g.nextPage());
        menu_redraw_required = 0;

      }
      updatezeo();
      break;

    case 4:
      uiStep();
      if (menu_redraw_required != 0 ) {

        u8g.firstPage();
        do {
          memMenu();
        } while ( u8g.nextPage());
        menu_redraw_required = 0;

      }
      updatemem();
      break;


  }
}
