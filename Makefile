


all: a.img

a.img: boot.img loader.img kernel.img
	cat $^ > $@

boot.img: boot.nasm
	nasm $^ -f bin -o $@

loader.img: loader.nasm
	nasm $^ -f bin -o $@

kernel.img: kernel.c lnk.ls
	gcc kernel.c  -o $@ -Wall -nostdlib -Wl,-T lnk.ls
clean:
	rm *.img *~

run:
	qemu -fda a.img -boot a -m 512
