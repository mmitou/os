#include "idt.h"
#include "basic_io.h"
#include "gdt.h"
#include "kstring.h"
#include "textmode_graphic.h"

enum IDTParams
{
   IDT_HEAD_ADDR = GDT_HEAD_ADDR + GDT_SIZE + 0x1000,
   IDT_SIZE = 0x10000
};

enum PICParmas
{
   PIC0_IMR = 0x0021,  /* PIC0 InterruptMaskRegister */
   PIC0_ICW1 = 0x0020, /* Initial Control Word */
   PIC0_ICW2 = 0x0021, 
   PIC0_ICW3 = 0x0021,
   PIC0_ICW4 = 0x0021,
   PIC0_OCW1 = 0x0021, /* Operation Control Word */
   PIC0_OCW2 = 0x0020,
   PIC0_OCW3 = 0x0020,
   
   PIC1_IMR = 0x00a1,  /* PIC1 InterruptMaskRegister */
   PIC1_ICW1 = 0x00a0, /* Initial Control Word */
   PIC1_ICW2 = 0x00a1, 
   PIC1_ICW3 = 0x00a1,
   PIC1_ICW4 = 0x00a1,
   PIC1_OCW1 = 0x00a1, /* Operation Control Word */
   PIC1_OCW2 = 0x00a0,
   PIC1_OCW3 = 0x00a0

};

void init_idt(void)
{
   GateDescripter *i = (GateDescripter *)IDT_HEAD_ADDR;
   int j;

   memset(i, 0, IDT_SIZE);


   for( j = 0; j< 256; ++j)
   {
      set_gatedescripter(
         i+j, asm_handlerDummy, 1 * 8,
         0, ON_PHYS_MEMORY);
   }

   set_gatedescripter(
      i + 0x20, asm_handler20, 1 * 8,
      0, ON_PHYS_MEMORY);

   set_gatedescripter(
      i + 0x21, asm_handler21, 1 * 8,
      0, ON_PHYS_MEMORY);

   set_gatedescripter(
      i + 0x2c, asm_handler2c, 1 * 8,
      0, ON_PHYS_MEMORY);

   io_lidt(IDT_SIZE -1, IDT_HEAD_ADDR);
}

void init_pic(void)
{
   io_out8(PIC0_IMR, 0xff); /* mask all interrupt */
   io_out8(PIC1_IMR, 0xff); /* mask all interrupt */

   io_out8(PIC0_ICW1, 0x11); /* edge trigger mode */
   io_out8(PIC0_ICW2, 0x20); /* IRQ0-7 receive at INT 20-27 */
   io_out8(PIC0_ICW3, 0x04); /* PIC1 conneted IRQ2 */
   io_out8(PIC0_ICW4, 0x01); /* non buffer mode */

   io_out8(PIC1_ICW1, 0x11); /* edge trigger mode */
   io_out8(PIC1_ICW2, 0x28); /* IRQ8-15 receive at INT 28-2f */
   io_out8(PIC1_ICW3, 0x02); /* PIC1 conneted IRQ2 */
   io_out8(PIC1_ICW4, 0x01); /* non buffer mode */
   
   io_out8(PIC0_IMR, 0xfc); /* PIC1 accept */
   io_out8(PIC1_IMR, 0xff); /* mask all interrupt */

   //io_out8(PIC0_IMR, 0x00); 
   //io_out8(PIC1_IMR, 0x00);

}

void set_gatedescripter(
   GateDescripter *i,
   const void *offset,
   const unsigned short cs_selector,
   const unsigned char dpl,
   const PhysicalMemoryStatus p)
{
   unsigned long handler_offset = (unsigned long)offset;
   i->handler_low = (0x0000ffff & handler_offset);
   i->codesegment = cs_selector;
   i->no_use = 0;
   i->padd0 = 6;
   i->d = 1;
   i->padd1 = 0;
   i->dpl = dpl;
   i->p  = p;
   i->handler_high = (0xffff0000 & handler_offset) >> 16;
}

void interrupthandler20(int *esp)
{
   static int x =0;
   char buf[20];
   int_to_string(x, 10, buf);
   textmode_puts(buf, WHITE, BLACK, 10, 3);
   ++x;
   io_out8(PIC0_OCW2, 0x0 + 0x60);
}

void interrupthandler21(int *esp)
{
   int x =0;
   char buf[20];
   x = io_in8(0x0060);
   int_to_string(x, 16, buf);
   textmode_puts(buf, WHITE, BLACK, 10, 2);
   io_out8(PIC0_OCW2, 0x01 + 0x60);
}

void interrupthandler2c(int *esp)
{
   static int x = 1;
   
   textmode_puts("2c", WHITE, BLACK, 10, x);
   ++x;
   io_out8(PIC0_OCW2, 0xc + 0x60);
   /*while(1);*/
}

void interrupthandlerDummy(int *esp)
{
   static int x = 0;
   if((x%2) == 0)
   {
      textmode_puts("Dummy is  0", WHITE, BLACK, 10, 3);
   }
   if((x%2) != 0)
   {
      textmode_puts("Dummy not 0", WHITE, BLACK, 10, 3);
   }
   x++;
}
