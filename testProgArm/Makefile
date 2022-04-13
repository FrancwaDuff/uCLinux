CFLAGS = -march=armv7-m -mtune=cortex-m4 -mlittle-endian -mthumb -Os -ffast-math -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-common --param max-inline-insns-single=1000 -Wl,-elf2flt=-s -Wl,-elf2flt=16384

default : prog

prog : prog.c
	arm-uclinuxeabi-gcc -o prog $(CFLAGS) prog.c

clean :
	rm -f prog prog.gdb

