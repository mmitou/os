
#include "gdt.h"
#include "basic_io.h"

void set_segmentdescripter(
   SegmentDescripter* s, 
   const unsigned long limit, const unsigned long baseaddr,
   const DescripterType type, const unsigned long dpl,
   const PhysicalMemoryStatus p, const LimitStatus g)
{
   const unsigned short limit_low  = (0x0000ffff & limit);
   const unsigned short limit_high = (0x000f0000 & limit) >> 16;
   const unsigned short base_low   = (0x0000ffff & baseaddr);
   const unsigned char base_mid    = (0x00ff0000 & baseaddr) >> 16;
   const unsigned char base_high   = (0xff000000 & baseaddr) >> 24;

   s->limit_low = limit_low;
   s->limit_high = limit_high;
   s->base_low = base_low;
   s->base_mid = base_mid;
   s->base_high = base_high;

   s->type = (unsigned char) type;
   s->s = 1; 
   s->dpl  = dpl; 
   s->p  = p; 
   s->avl = 0;
   s->no_use = 0;
   s->d  = 1;
   s->g  = (unsigned char)g; 
}

void init_gdt(void)
{
   SegmentDescripter *s = (SegmentDescripter *)GDT_HEAD_ADDR;
   unsigned char *p;
   int i; 
   
   for(i = 0, p = (unsigned char *)s;
       i < GDT_SIZE; ++i)
   {
      p[i] = 0x0;
   }

   s++;

   set_segmentdescripter(
      s++, 
      0xfffff, 0x0, 
      CODE_EXE_R, 0,
      ON_PHYS_MEMORY, LIMIT_4KBYTES);

   set_segmentdescripter(
      s++, 
      0xfffff, 0x0, 
      DATA_R_W, 0,
      ON_PHYS_MEMORY, LIMIT_4KBYTES);

   io_lgdt(GDT_SIZE -1, GDT_HEAD_ADDR);

}
