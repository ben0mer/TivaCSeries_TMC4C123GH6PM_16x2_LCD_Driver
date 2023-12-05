
# 16x2 LCD 4 Bit Haberleşme Kütüphanesi
Tiva C Series TMC4C123GH6PM 16x2 LCD 4 Bit Driver
Bu kütüphane, 16x2 LCD ekranı 4 bit modunda kullanmak için yazılmıştır. LCD ekranı, GPIO portu B'nin 0, 1, 4, 5, 6 ve 7 numaralı pinlerine bağlanmalıdır. RS pinini GPIO portu B'nin 0 numaralı pinine, E pinini GPIO portu B'nin 1 numaralı pinine, D4 pinini GPIO portu B'nin 4 numaralı pinine, D5 pinini GPIO portu B'nin 5 numaralı pinine, D6 pinini GPIO portu B'nin 6 numaralı pinine, D7 pinini GPIO portu B'nin 7 numaralı pinine bağlayın. Kütüphaneyi kullanmak için önce lcdInit fonksiyonunu çağırın. Ardından, lcdClear, lcdSetCursor, lcdWrite, lcdPrint, lcdPrintLine gibi fonksiyonları kullanarak LCD ekranına metin yazabilirsiniz.

## Kurulum

Bu kütüphaneyi kullanmak için, aşağıdaki adımları izleyin:

- TivaWare C Series kütüphanelerini indirin ve kurun.
- Code Composer Studio IDE'yi indirin ve kurun.
- Bu kütüphaneyi GitHub'dan indirin veya klonlayın.
- Code Composer Studio'yu açın ve yeni bir proje oluşturun.
- Projenize lcdPlus.h ve lcdPlus.c dosyalarını ekleyin.
- Projenizin linker ayarlarında, TivaWare C Series kütüphanelerinin yolunu belirtin.
- Projenizin main.c dosyasında, lcdPlus.h dosyasını include edin.
- Kütüphaneyi istediğiniz gibi kullanın.

## Kullanım

Bu kütüphaneyi kullanmak için, aşağıdaki fonksiyonları kullanabilirsiniz:

- `void lcdInit(void);` LCD başlangıç ayarlarını yapar.
- `void lcdClear(void);` Ekranı temizler.
- `void lcdSetCursor(char satir, char sutun);` Cursorun konumunu ayarlar. SATIR -> 0 - 1 | SUTUN -> 0 - 15
- `void lcdWrite(unsigned char d);` Cursorun oldugu yere tek bir karakteri yazar.
- `void lcdPrint(char *satir1, char *satir2);` SATIR 1 ' e yazılacak metin -> satir1 | SATIR 2 ' ye yazılacak metin -> satir2
- `void lcdPrintLine(char satirNo, char *metin);` Belirtilen satıra metin yazar.
- `void lcdPrintSides(char satir, char *metin1, char *metin2);` Belirtilen satıra sol tarafa metin1, sağ tarafa metin2 yazar.

## Örnek

Bu kütüphaneyi kullanarak, LCD ekranına yazmak için aşağıdaki kodu kullanabilirsiniz:

```c
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
