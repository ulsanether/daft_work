/*

  SFU1605(직경 16mm, 리드 피치 5mm) 리드스크류와 nema23 1.8도 모터  TB6600 드라이버에 8 분주로 스탭 값을 맞춘다고 가정 할 경우
  스탭값은 (200x8)== 1600스탭이 한바퀴를 돌고, 한바퀴 돌때, 스크류의 피치인 5mm 전진 하게 된다. 
  스탭값은 점퍼로 맞추고,  전진 거리에 대한 세팅은  manu 항목의 Move_high, Move_low 항목을 를 수정하면 된다.

  스탮값이 16 분주일 경우 값을 320으로 바꿔 주면 된다. 

리드 스크류의 피치 간격에 따라 거리가 달라지므로 피치가 다를 경우 그에 따라 값 역시 수정 해 줘야 한다. 
*/


#include <AccelStepper.h>



extern AccelStepper stepper;
int Move_high = 160;
int Move_low  = -160;

void step_up(int axis) {
  stepper.setCurrentPosition(0);
 switch (axis) {
    case 0:  //위로 0.5mm
      stepper.runToNewPosition(Move_high);
      Serial.println("가");
      break;
    case 1:  //1mm  
      stepper.runToNewPosition(Move_high*2);
      Serial.println("나");
      break;
    case 2:  //위로 5mm
      Serial.println("다");
      stepper.runToNewPosition(Move_high*10);

      break;
    case 3:  //10mm 

      stepper.runToNewPosition(Move_high*20);
Serial.println("라");
      break;
  }
  
}



void step_down(int axis) {
        stepper.setCurrentPosition(0);
    switch (axis) {
    case 0:  //아래로 0.5mm

      stepper.runToNewPosition(Move_low);

      break;
    case 1:  //아래로1mm
   
      stepper.runToNewPosition(Move_low*2);

      break;
    case 2:  //아래로 5mm
     
      stepper.runToNewPosition(Move_low*10);

      break;
    case 3:  //아래로 10mm
     
      stepper.runToNewPosition(Move_low*20);

      break;
  }
}
