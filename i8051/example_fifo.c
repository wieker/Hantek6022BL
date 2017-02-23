#define ALLOCATE_EXTERN
#include "fx2regs.h"



// Read TRM p.15-115 for an explanation on this.
// A single nop is sufficient for default setup but like that we're on
// the safe side.
#define	NOP		__asm nop __endasm
#define	SYNCDELAY	NOP; NOP; NOP; NOP
#define SYNCDELAY3 {SYNCDELAY;SYNCDELAY;SYNCDELAY;}

#define MSB(word)  (BYTE)((((WORD)word) >> 8) & 0xff)
#define LSB(word)  (BYTE)(((WORD)word) & 0xff)


void main(void) {
    CPUCS=0x12;

    IFCONFIG = 0x03;    SYNCDELAY; //Diff
    REVCTL = 0x03;      SYNCDELAY;

    EP6CFG = 0xE0;      SYNCDELAY;

    FIFORESET = 0x80;   SYNCDELAY;
    FIFORESET = 0x82;   SYNCDELAY;
    FIFORESET = 0x84;   SYNCDELAY;
    FIFORESET = 0x86;   SYNCDELAY;
    FIFORESET = 0x88;   SYNCDELAY;
    FIFORESET = 0x00;   SYNCDELAY;


    EP6FIFOCFG = 0x08;  SYNCDELAY; //Diff

    PINFLAGSAB = 0x00;  SYNCDELAY; //New
    PINFLAGSCD = 0x00;  SYNCDELAY; //New

    PORTACFG = 0x00;    SYNCDELAY;
    FIFOPINPOLAR = 0x00;SYNCDELAY;
    EP6AUTOINLENH = 0x02;SYNCDELAY;
    EP6AUTOINLENL = 0x00;SYNCDELAY;
    EP6FIFOPFH = 0x80;   SYNCDELAY;//New
    EP6FIFOPFL = 0x00;   SYNCDELAY;//New

    OED = 0xff;
    IOD = 0xc0;
    OEA = 0xff;
    IOA = 0xff;
    SYNCDELAY;
    IOD = 0xc9;

    for (;;);
}

