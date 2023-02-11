#ifndef __STATE_H_
#define __STATE_H_

class state {
  private:
    int state_a;
    int state_toogle_A;
    int ton ;
  public:
    int button_state(int _ton, int _state_a, int _state_toogle );
    void tone_a(int _a);
    void img_update(int _state_a, int *state_toogle);
    void click_state(int state_a);
};

#endif
