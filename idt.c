
#include "idt.h"
#include "basic_io.h"
#include "gdt.h"
#include "kstring.h"

enum IDTParams
{
   IDT_HEAD_ADDR = GDT_HEAD_ADDR + GDT_SIZE + 0x1000,
   IDT_SIZE = 0x10000
};


void init_idt(void)
{
   InterruptDescripter *i = (InterruptDescripter *)IDT_HEAD_ADDR;

   memset(i, 0, IDT_SIZE);

   io_lidt(IDT_SIZE -1, IDT_HEAD_ADDR);
}

void set_interruptdescripter(
   InterruptDescripter *i,
   const unsigned long handler_offset,
   const unsigned short cs_selector,
   const unsigned char dpl,
   const PhysicalMemoryStatus p)
{
   i->handler_low = (0x0000ffff & handler_offset);
   i->codesegment = cs_selector;
   i->no_use = 0;
   i->padd0 = 5;
   i->d = 1;
   i->padd1 = 0;
   i->dpl = dpl;
   i->p  = p;
   i->handler_high = (0xffff0000 & handler_offset) >> 16;
}

