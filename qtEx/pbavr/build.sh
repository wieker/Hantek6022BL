#!/usr/bin/env bash

avr-gcc -Os -mmcu=attiny85 -o demo.elf pbavr.c
avr-objcopy -j .text -j .data -O ihex demo.elf demo.hex
avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -pattiny85 -cft245r -Pft0 -b2400 -Uflash:w:demo.hex

