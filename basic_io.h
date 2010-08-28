#ifndef __BASIC_ORDER_
#define __BASIC_ORDER_

extern void halt(void);
extern void io_cli(void);
extern void io_sti(void);
extern int io_in8(int port);
extern int io_in16(int port);
extern void io_out8(int port, int data);
extern void io_out16(int port, int data);
extern int io_load_eflags(void);
extern void io_store_eflags(int);

#endif
