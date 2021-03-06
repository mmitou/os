#ifndef __BASIC_ORDER_
#define __BASIC_ORDER_

extern void halt(void);
extern void io_cli(void);
extern void io_sti(void);
extern unsigned long io_in8(unsigned long port);
extern unsigned long io_in16(unsigned long port);
extern void io_out8(unsigned long port, unsigned char data);
extern void io_out16(unsigned long port, unsigned short data);
extern unsigned long io_load_eflags(void);
extern void io_store_eflags(unsigned long);
extern void io_lgdt(unsigned long limit, unsigned long addr);
extern void io_lidt(unsigned long limit, unsigned long addr);
extern void asm_handler20(void);
extern void asm_handler21(void);
extern void asm_handler2c(void);
extern void asm_handlerDummy(void);

#endif
