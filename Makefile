
all: a.img

a.img: boot.img loader.img kernel.img
	cat $^ > $@

boot.img: boot.nasm
	nasm $^ -f bin -o $@

loader.img: loader.nasm
	nasm $^ -f bin -o $@

kernel.img: kernel.o basic_order.o lnk.ls
	gcc kernel.o basic_order.o -o $@ -Wall -nostdlib -Wl,-T lnk.ls

basic_order.o: basic_order.nasm
	nasm $^ -f elf -o $@

kernel.o: kernel.c
	gcc $^ -c -o $@ -Wall -nostdlib

clean:
	rm *.img *~ *.o

run:
	qemu -fda a.img -boot a -m 512
