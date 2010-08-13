loaderHead equ 0x1000
kernelFrom equ 0x200	; base address との差分
kernelTo equ 0xf0000	; base address との差分
kernelSize equ 0x400

; DS:SI の文字列を出力する

print:
	lodsb
	cmp al, 0x0
	je printend

	mov ah, 0eh
	mov bx, 7
	int 10h
	
	jmp print
printend:
	ret

