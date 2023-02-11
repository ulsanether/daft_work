#ifndef __WATER_PUMP__
#define __WATER_PUMP__


class Water_pump {
  private:
    int dir_pin;
    int anl_pin;

  public:
    Water_pump(int _dir_pin, int _anl_pin) {
      dir_pin = _dir_pin;
      anl_pin = _anl_pin;

   
    }
    void set_water_pump() {
      pinMode(dir_pin, OUTPUT);
      pinMode(anl_pin, OUTPUT);
    }
    void onoff_water_pump(int i, int pwm_power) {
      if(i == 0){
            digitalWrite(dir_pin, HIGH);
          analogWrite(anl_pin, 0);

      }else if(i == 1){
          digitalWrite(dir_pin, HIGH);
          analogWrite(anl_pin, pwm_power);
      }
    }
};



#endif
