#include "gui.h"
#include "M5Stack.h"


void gui::tone_a(int _a) {  //사운드 함수
  switch (_a) {
    case 0:
      // M5.Speaker.tone(961, 10);
      break;
    case 1:
      // M5.Speaker.tone(361, 10);
      break;
  }
}

int gui::button_state(int _ton, int _state_a, int _state_toogle) {
  if (_state_toogle == 1) {
    _state_a--;
    Serial.println(02);
    tone_a(_ton);
    if (_state_a == -1) {
      _state_a = 3;
    }
    return _state_a;
  } else if (_state_toogle == 2) {
    _state_a++;
    tone_a(_ton);
    if (_state_a == 3) {  //state_up
      _state_a = 0;
    }
    return _state_a;
  }
}


int gui::button_state(int _ton, int _state_a, int _state_toogle, bool ch) {
  if (_state_toogle == 1) {
    _state_a--;
    Serial.println(02);
    tone_a(_ton);
    if (_state_a == -1) {
      _state_a = 4;
    }
    return _state_a;
  } else if (_state_toogle == 2) {
    _state_a++;
    tone_a(_ton);
    if (_state_a == 4) {  //state_up
      _state_a = 0;
    }
    return _state_a;
  }
}
