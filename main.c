#include "lcdPlus.h"


int main(void) {

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 40MHz
        lcdInit();
        while (1) {
            lcdPrint("Omer-Gokyer-----", "SAU-EEM-2023--------");
            SysCtlDelay(80000000/3); // 2 Saniye Bekle
            lcdClear();

            lcdPrintLine(0, "G200100060");
            SysCtlDelay(8000000/3); // 2 Saniye Bekle
            lcdPrintLine(1, "Omer Gokyer");
            SysCtlDelay(80000000/3); // 2 Saniye Bekle
            lcdClear();

            lcdPrintSides(0, "-->", "<--");
            lcdPrintCenter(0, "OMER");
            lcdPrintSides(1, "-->", "<--");
            lcdPrintCenter(1, "GOKYER");
            SysCtlDelay(80000000/3); // 2 Saniye Bekle
            lcdClear();


            lcdPrintCenter(0, "OMER GOKYER");
            lcdPrintCenter(1, "G200100060");
            SysCtlDelay(80000000/3); // 2 Saniye Bekle
            lcdClear();
        }
}
