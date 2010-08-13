OUTPUT_FORMAT("binary");
OUTPUT_ARCH("i386");
ENTRY(kernel_start);

krnlHead = 0x100000;

SECTIONS
{
	. = krnlHead;
	.text	: {*(.text)}
	.rodata	: {*(.rodata*)}
	.data	: {*(.data)}
	.bss	: {*(.bss)}
	. = krnlHead + (80 * 2 * 18 -2) * 512 - 4;
	.sigin	: {SHORT(0x1234)}
	.sigin	: {SHORT(0xabcd)}
}