
C_SRCS = \
kernel.c textmode_graphic.c idt.c gdt.c \
kstring.c

AS_SRCS = basic_io.nasm

BOOTLOADERS = boot.nasm loader.nasm

all: a.img

a.img: $(subst .nasm,.img,$(BOOTLOADERS)) kernel.img
	cat $^ > $@

kernel.img: $(subst .c,.o,$(C_SRCS)) $(subst .nasm,.o,$(AS_SRCS))
	gcc $^ -o $@ -Wall -nostdlib -Wl,-T lnk.ls

%.img : %.nasm
	nasm $^ -f bin -o $@

%.o : %.nasm
	nasm basic_io.nasm -f elf -o $@

%.o : %.c
	gcc $^ -c -o $@ -Wall -nostdlib

.PHONY: clean
clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*~" -exec rm {} \;
	find ./ -name "*.img" -exec rm {} \;

.PHONY: run
run:
	qemu -fda a.img -boot a -m 512
