
#include "DHTesp.h"

#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include <LovyanGFX.hpp> // main library
static LGFX lcd;         // declare display variable

#include <lvgl.h>
#include "lv_conf.h"
/*** Setup screen resolution for LVGL ***/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

// 병아리 키우는 4주간 온도
static float maxTemp[] = {35.0, 31.0, 28.0, 25.0,37.5};
static float minTemp[] = {33.0, 28.0, 25.0, 22.0,37.0};
static uint8_t cnt = 1;

#define relayPin 2

void OnOffRelay(bool OnOff);
DHTesp dht;
// Variables for touch x,y
#ifdef DRAW_ON_SCREEN
static int32_t x, y;
#endif

/*** Function declaration ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void lv_button_demo(void);

bool toogleButton = false;
void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  dht.setup(4, DHTesp::DHT11); // Connect DHT sensor to GPIO 17

  lcd.init(); // Initialize LovyanGFX
  lv_init();  // Initialize lvgl

  // Setting display to landscape
  if (lcd.width() < lcd.height())
    lcd.setRotation(lcd.getRotation() ^ 1);

  /* LVGL : Setting up buffer to use for display */
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*** LVGL : Setup & Initialize the display device driver ***/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = display_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*** LVGL : Setup & Initialize the input device driver ***/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = touchpad_read;
  lv_indev_drv_register(&indev_drv);

  lv_obj_t *label = lv_label_create(lv_scr_act()); // full screen as the parent
  lv_label_set_text(label, "병아리 키우기");       // set label text
  lv_obj_align(label, LV_ALIGN_TOP_MID, -20, 30);  // Center but 20 from the top

  lv_obj_t *labela = lv_label_create(lv_scr_act()); // full screen as the parent
  lv_label_set_text(labela, "습도");                // set label text
  lv_obj_align(labela, LV_ALIGN_TOP_LEFT, 50, 100); // Center but 20 from the top

  lv_obj_t *label1 = lv_label_create(lv_scr_act()); // full screen as the parent
  lv_label_set_text(label1, "온도");                // set label text
  lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 50, 200); // Center but 20 from the top

  lv_button_demo();
}

void TempToHumi()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  lcd.setTextSize(2, 2);
  lcd.drawString(String(humidity), 100, 100);
  lcd.drawString(String(temperature), 100, 200);
  
  if (toogleButton == false)
  {
    if (temperature < minTemp[cnt - 1])
    {
      OnOffRelay(HIGH);
    }
    else if (temperature > maxTemp[cnt - 1])
    {
      OnOffRelay(LOW);
    }
  }
  else
  {
    if (temperature < minTemp[cnt - 1])
    {
      OnOffRelay(LOW);
    }
    else if (temperature > maxTemp[cnt - 1])
    {
      OnOffRelay(HIGH);
    }
  }

lcd.drawString("Set " + String(minTemp[cnt - 1]) + "~" + String(maxTemp[cnt - 1]) , 260, 270);
  delay(100);
}

void OnOffRelay(bool OnOff)
{
  if (OnOff)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
}

unsigned long previousMillis = 0;
const long interval = 3000;

void loop()
{

  unsigned long currentMillis = millis(); // 현재 시간을 가져옴

  // 이전 호출 시간에서 interval이 지나면 함수를 호출
  if (currentMillis - previousMillis >= interval)
  {
    // 시간 갱신
    previousMillis = currentMillis;
    TempToHumi();
    // 함수 호출
  }

  lv_timer_handler(); /* let the GUI do its work */
  delay(5);

#ifdef DRAW_ON_SCREEN
  /*** Draw on screen with touch ***/
  if (lcd.getTouch(&x, &y))
  {
    lcd.fillRect(x - 2, y - 2, 5, 5, TFT_RED);
    lcd.setCursor(380, 0);
    lcd.printf("Touch:(%03d,%03d)", x, y);
    // }
#endif
  }

  /*** Display callback to flush the buffer to screen ***/
  void display_flush(lv_disp_drv_t * disp, const lv_area_t *area, lv_color_t *color_p)
  {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lcd.endWrite();

    lv_disp_flush_ready(disp);
  }

  /*** Touchpad callback to read the touchpad ***/
  void touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
  {
    uint16_t touchX, touchY;
    bool touched = lcd.getTouch(&touchX, &touchY);

    if (!touched)
    {
      data->state = LV_INDEV_STATE_REL;
    }
    else
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

      // Serial.printf("Touch (x,y): (%03d,%03d)\n",touchX,touchY );
    }
  }

  /* Counter button event handler */
  static void counter_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
      cnt++;

      if (cnt >= 6)
      {
        cnt = 1;
      }

      lv_obj_t *label = lv_obj_get_child(btn, 0);
      lv_label_set_text_fmt(label, "태어난지 : %d 주", cnt);
      LV_LOG_USER("Clicked");
      Serial.println("Clicked");
    }
  }

  /* Toggle button event handler */
  static void toggle_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
      LV_LOG_USER("Toggled");
      Serial.println("Toggled");
      toogleButton ^= true;
      Serial.println(toogleButton);
    }
  }

  void lv_button_demo(void)
  {
    lv_obj_t *label;

    // Toggle button
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn, counter_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_pos(btn, 250, 190); /*Set its position*/
    lv_obj_set_size(btn, 200, 70); /*Set its size*/

    label = lv_label_create(btn);
    lv_label_set_text(label, "1주");
    lv_obj_center(label);

    // Toggle button
    lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, toggle_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_pos(btn2, 250, 80);  /*Set its position*/
    lv_obj_set_size(btn2, 200, 80); /*Set its size*/

    label = lv_label_create(btn2);
    lv_label_set_text(label, "전등 토글 버튼");
    lv_obj_center(label);
  }
