/*
영점을 잡는 부분이다. 
Z probe로 잡을 수 있다. 
*/


void updatezeo(void) {
  int btn;
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      router += 10;  //1틱당 10mm를 이동한다 간격을 수정하고 싶다면 정수 == 10부분을 수정하면 된다.    
      menu_redraw_required = 1;
      if(btn == LOW){
        router =0;  
        stepper.stop();  
        delay(1000);  
        break;
      }
      step_up(3);
      break;
    case KEY_PREV:
    step_down(3);    
      menu_redraw_required = 1;
      router -= 10;  //-10의 간격으로 하강한다. 수정하고 싶다면 정수 부분을 수정하면 된다. 
      break;
    case KEY_SELECT:
      menu_redraw_required = 1;
      router = 0;
      break;
    case KEY_BACK:
      menu_state = 1;
      menu_redraw_required = 1;
      break;
  }
       if(router >= 200){
        router = 200;
      }else if (router <= -200){
        router = -200;
      }
}


void zeroMenu(void) {

  u8g2.setFont(u8g_font_cu12);
 
  u8g2.firstPage();
  do {
     u8g2.drawFrame(0, 0, 128, 64);
    u8g2.drawBitmap( 10, 10, 5, 52, zero);
    u8g2.drawBitmap( 83, 3, 3, 59, zero1);
    u8g2.setCursor(15, 20);
    u8g2.print(router);
  } while ( u8g2.nextPage() );


}
