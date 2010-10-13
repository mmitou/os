#ifndef _IDT_H_
#define _IDT_H_

#include "gdt.h"

typedef struct GateDescripter
{
      unsigned short handler_low;
      unsigned short codesegment;
      unsigned char no_use;
      unsigned char padd0 : 3; /* always 6 */
      unsigned char d : 1;     /* D/B flag */
      unsigned char padd1 : 1; /* always 0 */
      unsigned char dpl : 2;   /* DescripterPrivilegeLevel */
      unsigned char p : 1;     /* PhysicalMemoryStatus */
      unsigned short handler_high;
} GateDescripter;

void set_gatedescripter(
   GateDescripter *i,
   const void *handleraddr,
   const unsigned short cs_selector,
   const unsigned char dpl,
   const PhysicalMemoryStatus p);

void init_idt(void);

void init_pic(void);

#endif
