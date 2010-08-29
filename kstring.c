#include "kstring.h"

void *memset(void *p, int c, unsigned long size)
{
   unsigned char *q = (unsigned char *)p;
   unsigned char data = (unsigned char)c;
   int i;

   for(i = 0; i < size; ++i)
   {
      q[i] = data;
   }
   
   return p;
}
