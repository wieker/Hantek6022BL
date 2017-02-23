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
    CPUCS=0x12;                  // 48 MHz, CLKOUT output enabled.
    IFCONFIG=0xc0;   SYNCDELAY;  // Internal IFCLK, 48MHz; A,B as normal ports.
    REVCTL=0x03;     SYNCDELAY;  // See TRM...
    EP6CFG=0xe0;     SYNCDELAY;  // 1110 0010 (bulk IN, 512 bytes, double-buffered)
    EP2CFG=0xa2;     SYNCDELAY;  // 1010 0010 (bulk OUT, 512 bytes, double-buffered)
    FIFORESET=0x80;  SYNCDELAY;  // NAK all requests from host.
    FIFORESET=0x82;  SYNCDELAY;  // Reset individual EP (2,4,6,8)
    FIFORESET=0x84;  SYNCDELAY;
    FIFORESET=0x86;  SYNCDELAY;
    FIFORESET=0x88;  SYNCDELAY;
    FIFORESET=0x00;  SYNCDELAY;  // Resume normal operation.
    EP2FIFOCFG=0x00; SYNCDELAY;  // Make sure AUTOOUT=0.
    EP4FIFOCFG=0x00; SYNCDELAY;  // Make sure AUTOOUT=0.
    EP6FIFOCFG=0x00; SYNCDELAY;  // Make sure AUTOOUT=0.
    EP8FIFOCFG=0x00; SYNCDELAY;  // Make sure AUTOOUT=0.
    OUTPKTEND=0x82;  SYNCDELAY;  // Be sure to clear the 2 buffers...
    OUTPKTEND=0x82;  SYNCDELAY;  // ...(double-buffered) (required!).
}

static char ProcessSendData(void)
{
    xdata const unsigned char *src=EP2FIFOBUF;
    xdata unsigned char *dest=EP6FIFOBUF;
    unsigned int len = ((int)EP2BCH)<<8 | EP2BCL;
    unsigned int i;
    for(i=0; i<len && i < sizeof(commands); i++,src++)
    {
        commands[i] = *src;
    }
    ;;

    // "Skip" the received OUT packet to "forget" it (see TRM p. 9-26):
    SYNCDELAY;  OUTPKTEND=0x82;

    // Arm the endpoint. Be sure to set BCH before BCL because BCL access
    // actually arms the endpoint.
    //SYNCDELAY;  EP6BCH=len>>8;
    //SYNCDELAY;  EP6BCL=len&0xff;
    return 'a';
}

void writeOut(unsigned char c, unsigned char v) {
    xdata unsigned char *dest=EP6FIFOBUF;
    dest[0] = 'A';
    dest[1] = c;
    dest[2] = v;
    dest[3] = 0;
    SYNCDELAY;  EP6BCH=0;
    SYNCDELAY;  EP6BCL=4;
}

void wait() {
    int i;
    for (i = 0; i < 100; i ++) {
        SYNCDELAY;
    }
}

void wait1() {
    int i;
    for (i = 0; i < 100; i ++) {
        wait();
    }
}

void wait10() {
    int i;
    for (i = 0; i < 1000; i ++) {
        wait();
    }
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
    IOD = 0x00; //0x89
    SYNCDELAY;
    IOD = 0x89; //0x89
    FIFOPINPOLAR = 0x1f;
    SYNCDELAY;


    for(;;)
    {
        // Wait for input on EP2 (EP2 non-empty).
        if(!(EP2CS & (1<<2)))
        {
            // Wait for EP6 buffer to become non-full so that we don't
            // overwrite content.
            while(EP6CS & (1<<3));
            command = ProcessSendData();
            command = commands[0];
            if (command == 'W') {
                for (i = 0; i < commands[1]; i ++) {
                    IOD = commands[i + 2];
                    wait();
                }
            }
            if (command == 'R') {
                CPUCS=0x12;                  // 48 MHz, CLKOUT output enabled.
                IFCONFIG=0x03;   SYNCDELAY;  // External IFCLK; A as slave FIFO, B as normal port.
                EP6FIFOCFG=0x0C; SYNCDELAY;
                OED = 0xff;
                FIFOPINPOLAR = 0x1f;
                SYNCDELAY;
                EP8AUTOINLENH = 0x02; // EZ-USB automatically commits data in 512-byte chunks
                SYNCDELAY;
                EP8AUTOINLENL = 0x00;
                SYNCDELAY;
            }
        }
    }
}



