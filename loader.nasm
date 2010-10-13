[org 0]
[bits 16]
	jmp short start

%include "common.inc"

start:
	mov ax, cs
	mov ds, ax
	mov es, ax
	xor ax, ax
	mov ss, ax

	mov si, kmsg
	call print

	; VGA mode
	; mov ax, 0x0013
	; int 0x10

	; AT互換機はCLIを呼ぶ前にこれをやらないといけないらしい
	; と、30日でOS作る本に書いてあった

	;mov al, 0xff
	;out 0x21, al
	;nop
	;out 0xa1, al

	; PIC の割り込みを無効化する
	; カーネル内で割り込み設定をした後で改めて有効にする
	cli

	; A20ラインを有効にする
	call enableA20


	; GDT を登録する
	lgdt [gdtr]


	; IDT を登録する
	lidt [idtr]

	; プロテクトモードになる
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; パイプラインのフラッシュをする
	jmp pipeFlush

pipeFlush:
	; セグメント間ジャンプでCSレジスタにGDTのセレクタ値を設定する
	jmp dword codeSgmntSlctr:(0x10000 + prtctModeBegin)

prtctModeBegin:
[bits 32]
	mov bx, dataSgmntSlctr
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	mov ss, bx

	mov esi, 0x0


kernelCopy:
	mov eax, kernelFrom
	add eax, esi
	mov ebx, kernelTo
	add ebx, esi
	mov ecx, [eax]
	mov [ebx], ecx
	add esi, 0x2
	cmp esi, kernelSize
	jbe kernelCopy

	jmp dword codeSgmntSlctr:kernelTo

[bits 16]
;<defun enableA20>
; A20 ラインを有効にする
enableA20:
	call kbdclr
	mov al, 0xd1	
	out 0x64, al	; これからコマンド送信をすると8042に伝える
	call kbdclr
	mov al, 0xdf	
	out 0x60, al	; A20ラインを有効にする
	call kbdclr
	mov al, 0xff
	out 0x64, al
	call kbdclr

	ret

;<defun kbdclr>
;キーボードコントローラ8042の状態ポート 0x64 と入力バッファ0x60 を空にする
kbdclr: 
waitkbdin:	; 8042の入力バッファが空になるまで読む
	in al, 0x60	; 0x60 を読む
	test al, 0x2	; バッファが空?
	jnz waitkbdin	

waitkbdout:	; 8042の状態ポートが空になるまで読みまくる
	in al, 0x64	; 0x64を読み込む
	test al, 0x2	; バッファが空?
	jnz waitkbdout	 
	

	ret

;</defun kbdclr>
;</defun enableA20>


kmsg db 'LOAD ', 0x0

; IDT
idtr	dw 0	; IDTのサイズ
	dw 0, 0	; IDTのアドレス

; GDT
gdtr:
	dw gdtEnd - gdt - 1	; GDT全体のサイズ
	dd gdt + loaderHead * 0x10  ; GDTのアドレス

gdt:
	dw 0, 0, 0, 0	; NULLセレクタ

codeSgmntSlctr equ 0x08
	dw 0xffff   ; リミット 0xffff
	dw 0x0	    ; baseaddress 0~15
	db 0x0	    ; baseaddress 16~23
	db 0x9a	    ; P:1 DPL:0 S:1 TYPE:10 Code non-conforming readable
	db 0xcf	    ; G:1, D:1, limit 16~19: 0xf
	db 0x0	    ; baseaddress 24~31: 0x0
	; base = 0x00000000

dataSgmntSlctr equ 0x10
	dw 0xffff   ; リミット 0xffff
	dw 0x0	    ; baseaddress 0~15
	db 0x0	    ; baseaddress 16~23
	db 0x92	    ; P:1 DPL:0 S:1 TYPE: Data, expand-up, writable
	db 0xcf	    ; G:1 D:1 limit 16~19: 0xf
	db 0x0	    ; baseaddress 24~31: 0x0
	; base = 0x00000000

gdtEnd:

times 512 - ($ -$$) db 0