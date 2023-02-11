#ifndef __GATE_H_
#define __GATE_H_


class btn;

class gate {

  private:

  public:
    int gate_val;
    int *ang_min;  //100
    int *ang_max;  //550범위를 넘어 서면 제대로 작동 안함
    int *gate_state;
    int *fire_state;
    int *button_state;
    int* bluetooth_state;
    //처음 버튼 토글 시작 설정 

    gate(int _gate_val): gate_val(_gate_val) {
      gate_state = new int(gate_val);  //버튼과 게이트의 수량을 같게 통일한다.
      fire_state = new int(gate_val);
      bluetooth_state = new int(gate_val);
      button_state = new int(gate_val);
      ang_min = new int(gate_val);
      ang_max = new int(gate_val);

    }

    ~gate() {
      delete []gate_state;
      delete []fire_state;
      delete []button_state;
      delete []bluetooth_state;
      delete []ang_min;
      delete []ang_max;
    }


};


class btn: public gate {
  private:
   
    int state_a;
    int state_toogle;
      int button_toogle_first[10];
  private:  //버튼 값
    void button_get(int _state_toogle); //버튼 함수 받아 위치값 조정 ok
    void tone_a(int _a); //버튼 함수 값 받아 소리 동작
    void button_set(); // 버튼 클릭했을때 게이트 동작 함수 1
    void image_state();  //이미지 표시 //게이트 동작시에도 표시 하게 할것

  private:  //게이트 동작
    void gate_play(int motor_int, int gate_int, int fire_int, int button_int, int bt_int);

  public:
   int* button_toogle;
    btn(int _btn_val): gate(_btn_val) { //생성자
      button_toogle = new int(_btn_val);
      state_a = 0;
      state_toogle = 0;

      for(int i=0; i<10; i++){

        button_toogle_first[i] = 1;
      }

    }
    void button_val();  //버튼 동작 시키는 함수 ok
    void gate_set(char* _string); //문자열 저장후 게이트 동작 함수
    void firebase_get(String value); //파이어베이스 값을 받아서 동작
    void bt_gate(String text);
    void gate_print(int i, int z, int k);
    ~btn() {
      delete []button_toogle;
    }
    void relay();
};





#endif
