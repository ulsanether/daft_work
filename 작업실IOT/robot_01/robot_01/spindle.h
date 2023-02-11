#ifndef __SPINDLE_H__
#define __SPINDLE_H__


class Spindle {
  private:
    int gnd_pin;
    int anl_pin;

  public:
    Spindle(int _gnd_pin, int _anl_pin):gnd_pin(_gnd_pin), anl_pin(_anl_pin) {  }
    
    void set_spindle() {
      pinMode(gnd_pin, OUTPUT);
      pinMode(anl_pin, OUTPUT);
      digitalWrite(gnd_pin, LOW);
    }
    void onoff_spindle(int i, int pwm_power) {
      if(i == 0){
          analogWrite(anl_pin, 0);

      }else if(i == 1){
          analogWrite(anl_pin, pwm_power);
      }
    }
};



#endif
