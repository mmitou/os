[org 100000]
[bits 32]
	jmp short start

start:
	hlt
	jmp start


kmsg db ' in kernel '

times 512 - ($ -$$) db 0