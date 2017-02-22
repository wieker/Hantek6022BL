/*
 * convert_string/convert.c -- FX2 USB data converter (filter) example.
 *
 * Copyright (c) 2006--2008 by Wolfgang Wieser ] wwieser (a) gmx <*> de [
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation. (See COPYING.GPL for details.)
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

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

BYTE set_samplerate(BYTE rate);
char commands[100];

void initEps() {
    CPUCS=0x10;                  // 48 MHz, CLKOUT output disabled.
    IFCONFIG=0xc0;   SYNCDELAY;  // Internal IFCLK, 48MHz; A,B as normal ports.
    REVCTL=0x03;     SYNCDELAY;  // See TRM...
    EP6CFG=0xe2;     SYNCDELAY;  // 1110 0010 (bulk IN, 512 bytes, double-buffered)
    EP2CFG=0xa2;     SYNCDELAY;  // 1010 0010 (bulk OUT, 512 bytes, double-buffered)
    FIFORESET=0x80;  SYNCDELAY;  // NAK all requests from host.
    FIFORESET=0x82;  SYNCDELAY;  // Reset individual EP (2,4,6,8)
    FIFORESET=0x84;  SYNCDELAY;
    FIFORESET=0x86;  SYNCDELAY;
    FIFORESET=0x88;  SYNCDELAY;
    FIFORESET=0x00;  SYNCDELAY;  // Resume normal operation.
    EP2FIFOCFG=0x00; SYNCDELAY;  // Make sure AUTOOUT=0.
    OUTPKTEND=0x82;  SYNCDELAY;  // Be sure to clear the 2 buffers...
    OUTPKTEND=0x82;  SYNCDELAY;  // ...(double-buffered) (required!).
}

void main(void) {
    int state = 0;
    char command;
    unsigned char param;
    int i = 0;
    int j = 0;

    initEps();
    //main_init();


    OEA = 0xff;
    IOA = 0x00;
    OEB = 0xff;
    IOB = 0x00;
    OEC = 0xff;
    IOC = 0x00;
    OED = 0xff;
    IOD = 0x00;

    for(;;)
    {
        IOB = 0xff;
        IOB = 0x00;
    }
}



