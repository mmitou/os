loaderHead equ 0x1000
kernelFrom equ 0x10200	; base address との差分
kernelTo   equ 0x100000	; base address との差分
kernelSize equ 0x2800

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

