#!/usr/bin/env bash

avr-gcc -Os -mmcu=atmega8 -o demo.elf pbavr.c
avr-objcopy -j .text -j .data -O ihex demo.elf demo.hex
avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -patmega8 -cft245r -Pft0 -b19200 -Uflash:w:demo.hex
