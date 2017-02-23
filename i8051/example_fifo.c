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

    IFCONFIG = 0x03;
    SYNCDELAY;
    REVCTL = 0x03;
    SYNCDELAY;
    EP8CFG = 0xE0;
    SYNCDELAY;
    FIFORESET = 0x80;
    SYNCDELAY;
    FIFORESET = 0x82;
    SYNCDELAY;
    FIFORESET = 0x84;
    SYNCDELAY;
    FIFORESET = 0x86;
    SYNCDELAY;
    FIFORESET = 0x88;
    SYNCDELAY;
    FIFORESET = 0x00;
    SYNCDELAY;
    EP8FIFOCFG = 0x0C;
    PINFLAGSAB = 0x00;
    SYNCDELAY;
    PINFLAGSCD = 0x00;

    PORTACFG = 0x00;
    SYNCDELAY;
    FIFOPINPOLAR = 0x00;
    SYNCDELAY;
    EP8AUTOINLENH = 0x02;
    SYNCDELAY;
    EP8AUTOINLENL = 0x00;
    SYNCDELAY;
    EP8FIFOPFH = 0x80;
    SYNCDELAY;
    EP8FIFOPFL = 0x00;

    OED = 0xff;
    IOD = 0x00; //0xc9
    OEA = 0xff;
    IOA = 0x00;
    SYNCDELAY;
    IOD = 0xc9; //0xc9

    for (;;);
}

