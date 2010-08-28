#include "textmode_graphic.h"

static const unsigned long tmode_vram_head = 0xb8000;
static const unsigned long tmode_vram_tail = 0xc0000;

int in_range(const unsigned int x, const unsigned int y)
{
   return (x <= X_MAX) || (y <= Y_MAX) ? 1 : 0;
}

unsigned long pos_to_vram_addr(const unsigned int x, const unsigned int y)
{
   return (tmode_vram_head + sizeof(TextModeChar)*((X_MAX + 1)* y + x));
}

void tmode_putc(TextModeChar c, const unsigned long addr)
{
   TextModeChar *p = (TextModeChar *)addr;
   if((tmode_vram_head <= addr) && (addr <= tmode_vram_tail))
   {
      *p = c;
   }
}

void tmode_putchar(
   const char c, 
   const unsigned char cclr, const unsigned char bclr, 
   const unsigned int x, const unsigned int y)
{
   TextModeChar q;
   if(!in_range(x,y)) return;

   q.c = c;
   q.cclr = cclr;
   q.bclr = bclr;

   tmode_putc(q, pos_to_vram_addr(x,y));
}

void tmode_boxfill(
   const unsigned int bclr,
   const unsigned int begin_x, const unsigned int begin_y,
   const unsigned int end_x, const unsigned int end_y)
{
   unsigned int x, y;

   if(!in_range(begin_x, begin_y)) return;
   if(!in_range(end_y, end_y)) return;
   if((begin_x > end_x) || (begin_y > end_y)) return;

   for(y = begin_y; y <= end_y; ++y)
   {
      for(x = begin_x; x <= end_x; ++x)
      {
         tmode_putchar(' ', BLACK, bclr, x, y);
      }
   }
}

void tmode_puts(
   char *s, const unsigned char cclr, const unsigned char bclr, 
   const unsigned int x, const unsigned int y)
{
   char *p;
   unsigned long pos_addr = pos_to_vram_addr(x, y);
   TextModeChar c;
   if(!in_range(x,y)) return;

   c.cclr = cclr;
   c.bclr = bclr;

   for(p = s; *p != '\0'; ++p)
   {
      c.c = *p;
      tmode_putc(c, pos_addr);
      pos_addr = pos_addr + sizeof(TextModeChar);
   }
}

