/*
  �ѱ� ���̺귯�� '��췯��' �Ƶ��̳� ���� 1.0
  ���� : OLED ���÷��̸� ����ϴ� �Ƶ��̳� ���α׷����� �ѱ� ����� �����Ӱ� �ϱ� ����
         ���������.
  ��� ���̺귯�� : Adafruit���� ������ OLED ���÷��̿� ���̺귯����
                    Adafruit_GFX, Adafruit_SSD1306
  ��� ��� : ��� (�� ����) ���̺귯���� '(�����)/����/Arduino/libraries' ������ ��ġ�ϰ�,
              �ҽ� ���Ͽ��� EURK_Arduino.h ��� ������ ��Ŭ����� �Ŀ�,
              ���÷��� ��Ȳ�� ���� display ������Ʈ�� �����ϰ� ����,
              ������ �ѱ� ���̺귯�� �Լ����� ȣ���ϸ� �ȴ�.
  ���� : �����̷�������� ( http://sookmook.org )
  ���� ��� : ���� ������ ( mailto://sookmook@sookmook.org )
              feat. �Ⱥ��� ( mailto://hayansea@sookmook.org )
  ���� ��¥ : 2018�� 4�� 24��
*/

#ifndef __EURK_ARDUINO_H
#define __EURK_ARDUINO_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sfif_inc.h"
#include "Hangeul_Font.h"
#include "ASCII_Font.h"

/* 2����Ʈ ������ �ѱ��� ���� ����ü */
#ifndef __HAN_UNION
#define __HAN_UNION
union HAN_UNION {
  struct {
    word l : 5 ;
    word m : 5 ;
    word f : 5 ;
    word s : 1 ;
  } a ; /* �ڸ� */
  struct {
    byte s ;
    byte f ;
  } c ; /* �ڵ� */
} ;
#endif

/* ���뱹��� ǥ�� ������ ��� �ѱ��� �� = 11172 */
/* (�ʼ� 19 * �߼� 21 * ����(��ħ ���� �� ����) 28 */
#ifndef ALL_OF_HAN
#define ALL_OF_HAN 11172
#endif

/* �ѱ� �ڵ� ���� */
#ifndef __HANCODE__DEFINE
#define __HANCODE__DEFINE
#define HANCODE_UTF_8       0
#define HANCODE_EXTENED_KSC 1
#endif

/* �����ڵ忡�� �ѱ��� ���� ��ġ */
#ifndef UNICODE_HAN_BASE
#define UNICODE_HAN_BASE 0xAC00
#endif

void EURK_hancode(int kind) ;
void EURK_setxy(int x, int y) ;
void EURK_puts(char *s) ;
void EURK_putsxy(int XPOS, int YPOS, char *s) ;

#endif
