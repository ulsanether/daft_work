#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <EEPROM.h>

int motor_pwm_power; //eeprom에서 적재 할 것


long EEPROMRead(int address)
{
  long four = EEPROM.read(address * 4);
  long three = EEPROM.read(address * 4 + 1);
  long two = EEPROM.read(address * 4 + 2);
  long one = EEPROM.read(address * 4 + 3);

  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}


void EEPROMWrite(int address, long value)
{
  byte b4= (value & 0xFF);
  byte b3= ((value >> 8) & 0xFF);
  byte b2= ((value >> 16) & 0xFF);
  byte b1= ((value >> 24) & 0xFF);

  EEPROM.write(address * 4, b4);
  EEPROM.write(address * 4 + 1, b3);
  EEPROM.write(address * 4 + 2, b2);
  EEPROM.write(address * 4 + 3, b1);
}




#endif
