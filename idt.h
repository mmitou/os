#ifndef _IDT_H_
#define _IDT_H_

#include "gdt.h"

typedef struct InterruptDescripter
{
      unsigned short handler_low;
      unsigned short codesegment;
      unsigned char no_use;
      unsigned char padd0 : 3; /* always 5 */
      unsigned char d : 1;     /* D/B flag */
      unsigned char padd1 : 1; /* always 0 */
      unsigned char dpl : 2;   /* DescripterPrivilegeLevel */
      unsigned char p : 1;     /* PhysicalMemoryStatus */
      unsigned char handler_high;
} InterruptDescripter;

void set_interruptdescripter(
   InterruptDescripter *i,
   const unsigned long handleraddr,
   const unsigned short cs_selector,
   const unsigned char dpl,
   const PhysicalMemoryStatus p);

void init_idt(void);

#endif
