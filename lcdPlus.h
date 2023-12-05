/*
 * lcdPlus.h
 *
 *  Created on: 11 Kas 2023
 *      Author: omerg
 *
 *  Bu kütüphane, 16x2 LCD ekraný 4 bit modunda kullanmak için yazýlmýþtýr.
 *  LCD ekraný, GPIO portu B'nin 0, 1, 4, 5, 6 ve 7 numaralý pinlerine baðlanmalýdýr.
 *  RS pinini GPIO portu B'nin 0 numaralý pinine, E pinini GPIO portu B'nin 1 numaralý pinine,
 *  D4 pinini GPIO portu B'nin 4 numaralý pinine, D5 pinini GPIO portu B'nin 5 numaralý pinine,
 *  D6 pinini GPIO portu B'nin 6 numaralý pinine, D7 pinini GPIO portu B'nin 7 numaralý pinine baðlayýn.
 *  Kütüphaneyi kullanmak için önce lcdInit fonksiyonunu çaðýrýn.
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

// LCD komutlarý
#define CLEAR_DISPLAY                    0x01 // Ekraný temizle komutu
#define RETURN_HOME                      0x02 // Baþlangýç pozisyonuna dön komutu
#define ENTRY_MODE_SET                   0x04 // Yazma modunu ayarla komutu
#define DISPLAY_ON_OFF                  0x08 // Ekraný aç veya kapat komutu
#define FUNCTION_SET                    0x20 // Fonksiyon modunu ayarla komutu
#define HIDE_CURSOR                     0xD0
#define CURSOR_DISPLAY_SHIFT            0x10 // Ýmleci veya ekraný kaydýr komutu
#define SET_CGRAM_ADDR                  0x40 // Karakter oluþturma adresini ayarla komutu
#define SET_DDRAM_ADDR                  0x80 // Veri yazma adresini ayarla komutu
#define MOVE_CURSOR_START_ROW1          0x80
#define MOVE_CURSOR_START_ROW2          0xC0

// LCD modlarý
//**********************************************************************************
//
// ENTRY_MODE_SET --> 0b 0 0 0 0 0 1 I/D S
//  I/D (Increase/Decrease) --> Kayma Yönünü Belirler        | I/D = 0 Kursor Ayarlanmasý Gerekir    | I/D = 1 Saða Kayar
//  S (Cursor)              --> Kaydýrmayý Açýk Kapar        | S = 0 Kayma Kapalý                    | S = 1 Kayma Açýk
//
//**********************************************************************************

//**********************************************************************************
//
// DISPLAY_ON_OFF --> 0b 0 0 0 0 1 D C B
//  D (Display) --> Ekraný Açýp Kapar         | D = 0 EKRAN KAPALI | D = 1 EKRAN AÇIK
//  C (Cursor)  --> Ýmleçi Açýp Kapar         | C = 0 ÝMLEÇ KAPALI | C = 1 ÝMLEÇ AÇIK
//  B (Blink)   --> Yanýp Sönmeyi Açýp kapar  | B = 0 FLAÞ KAPALI  | B = 1 FLAÞ AÇIK
//
//**********************************************************************************

//**********************************************************************************
//
// FUNCTION_SET --> 0b 0 0 1 DL N F X X
//  DL (Data Length) --> 4 Bit'mi 8 Bit'mi?         | DL = 0 (4 Bit)    | D = 1 (8 Bit)
//  N (Line)  --> 1 Satýr mý 2 Satýr mý?            | N = 0 (1 SATIR)   | N = 1 (2 SATIR)
//  F (Dot)   --> 5x10'mu 5x8 mi?                   | F = 0 (5x8)       | F = 1 (5x10)
//
//**********************************************************************************

// Fonksiyon prototipleri
void lcd30h(void); // Baþlangýç ayarlarý için 30H gönderir.
void lcdInit(void); // LCD baþlangýç ayarlarýný yapar.
void lcdCommand(uint8_t cmd); // Komut gönderir.
void lcdPulse(void); // Komut ve veri göndermek için E' pinini yükseltip düþürür.
void lcdClear(void); // Ekraný temizler
void lcdSetCursor(char satir, char sutun); // SATIR -> 0 - 1 | SUTUN -> 0 - 15
void lcdWrite(unsigned char d); // Cursorun oldugu yere tek bir karakteri yazar.
void lcdPrint(char *satir1, char *satir2); // SATIR 1 ' e yazýlacak metin -> satir1 | SATIR 2 ' ye yazýlacak metin -> satir2
void lcdPrintLine(char satirNo, char *metin); // Belirtilen satýra metin yazar.
void lcdPrintSides(char satir, char *metin1, char *metin2); // Belirtilen satýra sol tarafa metin1 ' i sað tarafa metin2 ' yi yazar.
void lcdPrintCenter(char satir, char*metin); // Belirtilen satýra ortalanmýþ bir þekilde metin yazar.

#endif /* LCDPLUS_H_ */
