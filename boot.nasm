; boot 

[org 0]
[bits 16]

	jmp 0x07c0:start

%include "common.inc"

start:
	; セグメントレジスタの初期化
	mov ax, cs
	mov ds, ax
	mov es, ax

	; とりあえず文字列表示する
	mov si, bgnMsg
	call print

resetFdc:
	mov ax, 0
	mov dl, 0	; Aドライブを指定して
	int 0x13	; FDコントローラをリセットする
	jc resetFdc	; エラーが出たらやり直し

	mov ax, loaderHead	; loaderHeadに読み込む
	mov es, ax	; ES = loaderHead
	mov bx, 0x0	; ES:BX = loaderHead:0000
	mov ah, 0x02	; ES:BX を指定して
	mov ch, 0	; シリンダ0
	mov al, 1	; 1セクタ分
	mov cl, 0x02	; 読み込み開始セクタ2
	mov dh, 0	; ヘッド0
	mov dl, 0	; ドライブA

loopHead:
	; FDを読み込む
	mov ah, 0x02	; ES:BX を指定して
	mov al, 1	; 1セクタ分
	mov dl, 0	; ドライブA

	int 0x13	; FDD読み込み

	; 次のセクターを読むために変数を更新する
	mov ax, es	
	add ax, 0x20	; 512byte読み込むにあたり、リアルモードのアドレス指定だと +0x20
	mov es, ax

	add cl, 0x1
	cmp cl, 19	; セクターが1~18番まで
	jb loopHead
	mov cl, 1
	

	inc dh
	cmp dh, 2	; ヘッドは0 or 1なので
	jb loopHead
	mov dh, 0

	; 必要になるまでコピーしない
	;inc ch
	;cmp ch, 80	; シリンダは各面に0~79番まである
	;jb loopHead
	
loopEnd:
	
	jmp loaderHead:0
	

bgnMsg db 'BOOT ', 0x0

times 510 - ($ - $$) db 0
       dw 0xaa55