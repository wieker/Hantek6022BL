#define ALLOCATE_EXTERN
#include "fx2regs.h"



// Read TRM p.15-115 for an explanation on this.
// A single nop is sufficient for default setup but like that we're on
// the safe side.
#define	NOP		__asm nop __endasm
#define	SYNCDELAY	NOP; NOP; NOP; NOP
#define SYNCDELAY3 {SYNCDELAY;SYNCDELAY;SYNCDELAY;}

static void Initialize(void)
{
    CPUCS = 0x12;  // 48MHz, output to CLKOUT signal enabled.

    // Internally clocked (48MHz) sync slave fifo mode.
    // Output to IFCLK not enabled (set bit5 to enable).
    IFCONFIG = 0x03;  SYNCDELAY;
    REVCTL = 0x03;    SYNCDELAY;  // See TRM...

    // Configure EP6 (IN) for bulk input, quad-buffered (4*512 bytes).
    EP6CFG = 0xe0;  SYNCDELAY;

    FIFORESET = 0x80;  SYNCDELAY;  // NAK all requests from host.
    FIFORESET = 0x82;  SYNCDELAY;  // Reset individual EP (2,4,6,8)
    FIFORESET = 0x84;  SYNCDELAY;
    FIFORESET = 0x86;  SYNCDELAY;
    FIFORESET = 0x88;  SYNCDELAY;
    FIFORESET = 0x00;  SYNCDELAY;  // Resume normal operation.

    // Configure EP6 for AUTOIN, 16bit wide bus.
    EP6FIFOCFG = 0x0d;  SYNCDELAY;

    // PORTACFG: FLAGD SLCS(*) 0 0 0 0 INT1 INT0
    PORTACFG = 0x00;  SYNCDELAY; // (delay maybe not needed)

    // All default polarities: SLWR active low,...
    FIFOPINPOLAR=0x00;  SYNCDELAY;

    // This determines how much data is accumulated in the FIFOs before a
    // USB packet is committed. Use 512 bytes to be sure.
    EP6AUTOINLENH = 0x02; SYNCDELAY;  // MSB
    EP6AUTOINLENL = 0x00; SYNCDELAY;  // LSB
}

void main()
{
    Initialize();

    for(;;) {}
}
