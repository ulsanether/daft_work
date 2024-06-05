#include "state.h"
#include "M5Stack.h"
#include <FirebaseESP32.h>

void fire_base_sun(int);

int state::button_state(int _ton, int _state_a, int _state_toogle ) {
  if (_state_toogle == 1) {
     _state_a--;
      tone_a(_ton);
    if (_state_a == -1) {
      _state_a = 0;
    }
      return _state_a;
  } else if (_state_toogle == 2) {
    _state_a++;
     tone_a(_ton);
    if (_state_a == 4) {
      _state_a = 3;
    }
      return _state_a;
  }

}

void state::tone_a(int _a) {

  switch (_a) {
    case 0:
       M5.Speaker.setVolume(3);
      M5.Speaker.tone(961, 10);
      break;
    case 1:
       M5.Speaker.setVolume(3);
      M5.Speaker.tone(661, 10);
      break;
    case 2:
       M5.Speaker.setVolume(3);
      M5.Speaker.tone(361, 10);
      break;
  }
}


void state::click_state(int state_a) {

  if (state_a == 0) {
    fire_base_sun(1);
  } else if (state_a == 1) {
    Serial.println(1);
    fire_base_sun(2);
  } else if (state_a == 2) {
    fire_base_sun(3);
    Serial.println(2);
  }
   else if (state_a == 3) {
    fire_base_sun(4);
    Serial.println(3);
  }
}


void state::img_update(int _state_a, int *state_toogle) {
  if (_state_a != *state_toogle) {
    *state_toogle = _state_a;
    switch (_state_a) {
      case 0:
        M5.Lcd.drawJpgFile(SPIFFS, "/a.jpg", 0, 0);
        Serial.println(1);

        break;

      case 1:
        M5.Lcd.drawJpgFile(SPIFFS, "/b.jpg", 0, 0);
        Serial.println(2);

        break;

      case 2:

        M5.Lcd.drawJpgFile(SPIFFS, "/c.jpg", 0, 0);
        Serial.println(3);


        break;

      case 3:

        M5.Lcd.drawJpgFile(SPIFFS, "/d.jpg", 0, 0);
        Serial.println(4);
        break;
    }
  }
}
