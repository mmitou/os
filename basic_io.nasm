
[bits 32]

segment .text

[global halt]
[global io_cli]
[global io_sti]
[global io_in8]
[global io_in16]
[global io_out8]
[global io_out16]
[global io_load_eflags]
[global io_store_eflags]
[global io_lgdt]
[global io_lidt]
[global asm_handler20]
[global asm_handler21]
[global asm_handler2c]
[global asm_handlerDummy]

[extern interrupthandler20]
[extern interrupthandler21]
[extern interrupthandler2c]
[extern interrupthandlerDummy]

io_cli:
	cli
	ret

io_sti:
	sti
	ret

io_in8:
	mov edx, [esp + 4]
	mov eax, 0
	in al, dx
	ret

io_in16:
	mov edx, [esp + 4]
	mov eax, 0
	in ax, dx
	ret

io_out8:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret

io_out16:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, ax
	ret

halt:
	hlt
	ret

io_load_eflags:
	pushfd
	pop eax
	ret

io_store_eflags:
	mov eax, [esp + 4]
	push eax
	popfd
	ret
	
io_lgdt: ;void lgdt(ulong limit, ulong addr)
	mov ax, [esp + 4] ; limit
	mov [esp + 6], ax
	lgdt [esp + 6]
	ret

io_lidt: ; void idrt(ulong limit, ulong addr)
	mov ax, [esp + 4] ; limit
	mov [esp + 6], ax
	lidt [esp + 6]
	ret



asm_handler20:
	push es
	push ds
	pushad

	mov eax, esp

	push eax
	mov ax, ss
	mov ds, ax
	mov es, ax

	call interrupthandler20

	pop eax
	popad
	pop ds
	pop es
	iretd


asm_handler21:
	push es
	push ds
	pushad

	mov eax, esp

	push eax
	mov ax, ss
	mov ds, ax
	mov es, ax

	call interrupthandler21

	pop eax
	popad
	pop ds
	pop es
	iretd

asm_handler2c:
	push es
	push ds
	pushad

	mov eax, esp
	push eax

	mov ax, ss
	mov ds, ax
	mov es, ax

	call interrupthandler2c

	pop eax
	popad
	pop ds
	pop es
	iretd
	
asm_handlerDummy:
	push es
	push ds
	pushad

	mov eax, esp

	push eax
	mov ax, ss
	mov ds, ax
	mov es, ax

	call interrupthandlerDummy

	pop eax
	popad
	pop ds
	pop es
	iretd
