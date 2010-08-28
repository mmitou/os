
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
	