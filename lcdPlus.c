/*
 * lcdPlus.c
 *
 *  Created on: 11 Kas 2023
 *      Author: omerg
 */


#include "lcdPlus.h"

void lcd30h(){
    SysCtlDelay(50000);
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);
}

void lcdInit() {
        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);
        lcd30h();
        lcd30h();
        lcd30h();
        SysCtlDelay(50000);
        lcdCommand(FUNCTION_SET | 0x08);
        SysCtlDelay(50000);
        lcdCommand(DISPLAY_ON_OFF | 0x07);
        lcdClear();
        SysCtlDelay(50000);
        lcdCommand(ENTRY_MODE_SET);
        SysCtlDelay(600); // Minimum 40us
}

void lcdPrint(char *metin1, char *metin2) {
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(metin1)) {
            lcdSetCursor(0,j);
            lcdWrite(metin1[j]);
        }
        if (j<strlen(metin2)) {
            lcdSetCursor(1,j);
            lcdWrite(metin2[j]);
        }
    }
    lcdCommand(HIDE_CURSOR);
}

void lcdPulse(){
    GPIOPinWrite(LCDPORT, E, E); //enable high
    SysCtlDelay(10); //pulse width > 450ns
    GPIOPinWrite(LCDPORT, E, 0x00); //enable low
    SysCtlDelay(50000); //wait for > 37us between commands 1480 is more correct
}

void lcdCommand(uint8_t cmd){
    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (cmd & 0xf0));
    lcdPulse();

    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (cmd & 0x0f) << 4);
    lcdPulse();
}

void lcdWrite(unsigned char d) {
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        lcdPulse();
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        lcdPulse();
}

void lcdSetCursor(char satir, char sutun){

    if (satir == 0) {
        lcdCommand(0x80 + (sutun % 16));
        return;
    }
    else if (satir == 1){
        lcdCommand(0xC0 + (sutun % 16));
        return;
    }
    else{
        return; // HATA
    }
}

void lcdClear(void){
    lcdCommand(CLEAR_DISPLAY);
    SysCtlDelay(10);
}

void lcdPrintSides(char satir, char *metin1, char *metin2){
    int i;
    int j = strlen(metin2);
    for (i = 16 ; i > (15-(strlen(metin2))) ; i--){
        lcdSetCursor(satir, i);
        lcdWrite(metin2[j]);
        j--;
    }

    for (i = 0 ; i < strlen(metin1) ; i++){
        lcdSetCursor(satir, i);
        lcdWrite(metin1[i]);
    }

    lcdCommand(HIDE_CURSOR);
}

void lcdPrintCenter(char satir, char*metin){
    int s = (8-(strlen(metin)/2));
    int e = s+strlen(metin);
    int i = 0;
    for(s = (8-(strlen(metin)/2)); s < e; s++){
        lcdSetCursor(satir, s);
        lcdWrite(metin[i]);
        i++;
    }
    lcdCommand(HIDE_CURSOR);
}

void lcdPrintLine(char satirNo, char *metin) {
    lcdSetCursor(satirNo, 0);
    int i;
    for (i=0; i<strlen(metin); i++) {
        lcdWrite(metin[i]);
    }
    lcdCommand(HIDE_CURSOR);
}
