
all: a.img

a.img: boot.img loader.img kernel.img
	cat $^ > $@

boot.img: boot.nasm
	nasm $^ -f bin -o $@

loader.img: loader.nasm
	nasm $^ -f bin -o $@

kernel.img: kernel.o basic_io.o textmode_graphic.o
	gcc $^ -o $@ -Wall -nostdlib -Wl,-T lnk.ls

basic_io.o: basic_io.nasm 
	nasm basic_io.nasm -f elf -o $@

graphic.o: graphic.c
	gcc $^ -c -o $@ -Wall -nostdlib

textmdoe_graphic.o: textmdoe_graphic.c
	gcc $^ -c -o $@ -Wall -nostdlib

kernel.o: kernel.c 
	gcc $^ -c -o $@ -Wall -nostdlib

clean:
	rm *.img *~ *.o

run:
	qemu -fda a.img -boot a -m 512
