/*
 * lcdPlus.h
 *
 *  Created on: 11 Kas 2023
 *      Author: omerg
 *
 *  Bu k�t�phane, 16x2 LCD ekran� 4 bit modunda kullanmak i�in yaz�lm��t�r.
 *  LCD ekran�, GPIO portu B'nin 0, 1, 4, 5, 6 ve 7 numaral� pinlerine ba�lanmal�d�r.
 *  RS pinini GPIO portu B'nin 0 numaral� pinine, E pinini GPIO portu B'nin 1 numaral� pinine,
 *  D4 pinini GPIO portu B'nin 4 numaral� pinine, D5 pinini GPIO portu B'nin 5 numaral� pinine,
 *  D6 pinini GPIO portu B'nin 6 numaral� pinine, D7 pinini GPIO portu B'nin 7 numaral� pinine ba�lay�n.
 *  K�t�phaneyi kullanmak i�in �nce lcdInit fonksiyonunu �a��r�n.
 */

#include "stdint.h"
#include "stdbool.h"

#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "string.h"

#ifndef LCDPLUS_H_
#define LCDPLUS_H_

// LCD portu ve pinleri
#define LCDPORT                          GPIO_PORTB_BASE
#define LCDPORTENABLE                    SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7

// LCD komutlar�
#define CLEAR_DISPLAY                    0x01 // Ekran� temizle komutu
#define RETURN_HOME                      0x02 // Ba�lang�� pozisyonuna d�n komutu
#define ENTRY_MODE_SET                   0x04 // Yazma modunu ayarla komutu
#define DISPLAY_ON_OFF                  0x08 // Ekran� a� veya kapat komutu
#define FUNCTION_SET                    0x20 // Fonksiyon modunu ayarla komutu
#define HIDE_CURSOR                     0xD0
#define CURSOR_DISPLAY_SHIFT            0x10 // �mleci veya ekran� kayd�r komutu
#define SET_CGRAM_ADDR                  0x40 // Karakter olu�turma adresini ayarla komutu
#define SET_DDRAM_ADDR                  0x80 // Veri yazma adresini ayarla komutu
#define MOVE_CURSOR_START_ROW1          0x80
#define MOVE_CURSOR_START_ROW2          0xC0

// LCD modlar�
//**********************************************************************************
//
// ENTRY_MODE_SET --> 0b 0 0 0 0 0 1 I/D S
//  I/D (Increase/Decrease) --> Kayma Y�n�n� Belirler        | I/D = 0 Kursor Ayarlanmas� Gerekir    | I/D = 1 Sa�a Kayar
//  S (Cursor)              --> Kayd�rmay� A��k Kapar        | S = 0 Kayma Kapal�                    | S = 1 Kayma A��k
//
//**********************************************************************************

//**********************************************************************************
//
// DISPLAY_ON_OFF --> 0b 0 0 0 0 1 D C B
//  D (Display) --> Ekran� A��p Kapar         | D = 0 EKRAN KAPALI | D = 1 EKRAN A�IK
//  C (Cursor)  --> �mle�i A��p Kapar         | C = 0 �MLE� KAPALI | C = 1 �MLE� A�IK
//  B (Blink)   --> Yan�p S�nmeyi A��p kapar  | B = 0 FLA� KAPALI  | B = 1 FLA� A�IK
//
//**********************************************************************************

//**********************************************************************************
//
// FUNCTION_SET --> 0b 0 0 1 DL N F X X
//  DL (Data Length) --> 4 Bit'mi 8 Bit'mi?         | DL = 0 (4 Bit)    | D = 1 (8 Bit)
//  N (Line)  --> 1 Sat�r m� 2 Sat�r m�?            | N = 0 (1 SATIR)   | N = 1 (2 SATIR)
//  F (Dot)   --> 5x10'mu 5x8 mi?                   | F = 0 (5x8)       | F = 1 (5x10)
//
//**********************************************************************************

// Fonksiyon prototipleri
void lcd30h(void); // Ba�lang�� ayarlar� i�in 30H g�nderir.
void lcdInit(void); // LCD ba�lang�� ayarlar�n� yapar.
void lcdCommand(uint8_t cmd); // Komut g�nderir.
void lcdPulse(void); // Komut ve veri g�ndermek i�in E' pinini y�kseltip d���r�r.
void lcdClear(void); // Ekran� temizler
void lcdSetCursor(char satir, char sutun); // SATIR -> 0 - 1 | SUTUN -> 0 - 15
void lcdWrite(unsigned char d); // Cursorun oldugu yere tek bir karakteri yazar.
void lcdPrint(char *satir1, char *satir2); // SATIR 1 ' e yaz�lacak metin -> satir1 | SATIR 2 ' ye yaz�lacak metin -> satir2
void lcdPrintLine(char satirNo, char *metin); // Belirtilen sat�ra metin yazar.
void lcdPrintSides(char satir, char *metin1, char *metin2); // Belirtilen sat�ra sol tarafa metin1 ' i sa� tarafa metin2 ' yi yazar.
void lcdPrintCenter(char satir, char*metin); // Belirtilen sat�ra ortalanm�� bir �ekilde metin yazar.

#endif /* LCDPLUS_H_ */
