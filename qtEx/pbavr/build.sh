#!/usr/bin/env bash

avr-gcc -Os -mmcu=attiny13 -o demo.elf pbavr.c
avr-objcopy -j .text -j .data -O ihex demo.elf demo.hex
avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -pattiny13 -cstk500v1 -P/dev/ttyUSB0 -b19200 -Uflash:w:demo.hex

