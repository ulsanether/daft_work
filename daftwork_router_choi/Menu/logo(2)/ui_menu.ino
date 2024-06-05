

/*
 모터 작동
1틱당 0.5mm와
1틱당 5mm의 간격으로 동작을 조절 할 수 있다. 
1틱당 동작 간격을 조절 하고 싶다면 화살 표 부분을 수정하면 된다. 


 */

void updateact(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      router += (0.5 + ver2);
      menu_redraw_required = 1;

      break;
    case KEY_PREV:
      menu_redraw_required = 1;
      router -= (0.5 + ver2);
      break;
    case KEY_SELECT:
      if (toogle == 1) {
        ver2 = 4.5;  // <------------
        toogle = 0;
      } else {
        ver2 = 0;   //<-------------
        toogle = 1;
      }          
      break;
    case KEY_BACK:
      menu_state = 1;
      menu_redraw_required = 1;
      break;
  }

}

void actMenu() {

  u8g.setFont(u8g_font_fub14);
  u8g.firstPage();
  do {
    u8g.setPrintPos(34, 2);
    u8g.print("position");
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawLine(28, 20, 128, 20);
    u8g.drawBitmapP( 2, 3, 3, 59, atr);
    u8g.setPrintPos(28, 40);
    u8g.print(router);
    u8g.print("mm");
      if(ver2== 4.5){
    u8g.drawBitmapP( 6, 20, 2, 15, zero3);
  }else if(ver2==0){
       u8g.drawBitmapP( 6, 30, 2, 15, zero4);
  }
  } while ( u8g.nextPage() );
}
