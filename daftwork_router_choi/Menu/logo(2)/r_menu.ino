/*
메모리 관련
*/
void updatemem(void) {
  int temp;
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;

  switch ( uiKeyCode ) {
    case KEY_NEXT:
      mem_current++;
      if ( mem_current >= MEM_ITEMS )
        mem_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( mem_current == 0 )
        mem_current = MEM_ITEMS;
      mem_current--;
      menu_redraw_required = 1;
      break;
    case KEY_SELECT:
      if ( mem_current == 0 ) {
        ver = router;
       EEPROM.put(1, ver);        
      }
      else if (mem_current == 1) {
        EEPROM.get(1, router);
      } else if (mem_current == 2) {
        ver1 = router;
        EEPROM.put(2, ver1);   
      } else if (mem_current == 3) {
        EEPROM.get(2, router);
      }
      break;
    case KEY_BACK:
      menu_state = 1;
      menu_redraw_required = 1;
      break;
  }
}

void memMenu(void) {
  uint8_t i, h;
  u8g_uint_t w, d;
  u8g.setFont(u8g_font_cu12);
  u8g.firstPage();
  do {
    u8g.setFontRefHeightText();
    u8g.setFontPosTop();
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawLine(60, 5, 60, 59);
    u8g.drawLine(60, 34, 128, 34);
    u8g.drawBitmapP( 10, 0, 5, 64, mem);
    u8g.drawBitmapP(73, 33, 5, 18, mem1);
    u8g.drawBitmapP(73, 1, 5, 18, mem2);
    u8g.setPrintPos(80, 48);
    u8g.print(router);

    h = u8g.getFontAscent() - u8g.getFontDescent();
    w = u8g.getWidth();
    for ( i = 0; i < MEM_ITEMS; i++ ) {
      d = (w - u8g.getStrWidth(mem_strings[i]) / 5);
      u8g.setDefaultForegroundColor();
      if ( i == mem_current) {
        u8g.drawFrame(10, i * h + 1, w / 3 - 1, h + 2);
      }

    }
    if (mem_current == 0) {
      EEPROM.get(1,ver);
      u8g.setPrintPos(77, 15);
      u8g.print(ver);
    }
    else if (mem_current == 1) {
      EEPROM.get(1,ver);
      u8g.setPrintPos(77, 15);
      u8g.print(ver);
    }
    else if (mem_current == 2) {
      EEPROM.get(2,ver1);
      u8g.setPrintPos(77, 15);
      u8g.print(ver1);
    }
    else if (mem_current == 3) {
      u8g.setPrintPos(77, 15);
      u8g.print(EEPROM.get(2,ver1));
    }
  } while ( u8g.nextPage() );
}
