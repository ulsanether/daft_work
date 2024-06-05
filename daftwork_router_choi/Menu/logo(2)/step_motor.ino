/*

SFU1605 (직경 16mm, 리드 피치 5mm)와 nema23 1.8도 모터  
 TB6600 모터에 16 분주로 스탭 값을 맞춘다고 가정 할 경우 
 
 스탭값은 (200x16)== 3200스탭이 한바퀴를 돌고, 한바퀴 돌때 
 르드 피치인 5mm를 전진 하게 도니다. 

 
/ 10을 하면 0.5mm 간격을 간다. 
 
 
*/



stepper.currentPosition();

stepper.moveTo(router);
stepper.setSpeed(100);
stepper.runSpeedToPosition();





