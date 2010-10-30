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

int abs_int(int x)
{
   return (x > 0) ? x : -1 * x;
}

int int_to_string(int x, int num, char *result)
{
   int remainder;
   int div_rslt = abs_int(x);
   int i;

   if(x == 0)
   {
      result[0] = '0';
      result[1] = '\0';
      return 0;
   }

   for(i = 0; div_rslt != 0; i++)
   {
      remainder = div_rslt % num;
      div_rslt = div_rslt / num;
      result[i] = int_to_char(remainder);
   }

   if(x < 0)
   {
      result[i++] = '-';
   }

   reverse_string(result, 0, i-1);

   result[i] = '\0';

   return x;
}

char int_to_char(int x)
{
   char result;
   switch(x)
   {
      case 0: result = '0'; break;
      case 1: result = '1'; break;
      case 2: result = '2'; break;
      case 3: result = '3'; break;
      case 4: result = '4'; break;
      case 5: result = '5'; break;
      case 6: result = '6'; break;
      case 7: result = '7'; break;
      case 8: result = '8'; break;
      case 9: result = '9'; break;
      default: result = 'x'; break;
   }
   return result;
}

int reverse_string(char *s, int begin, int end)
{
   char buf;
   for(;end > begin; ++begin, --end)
   {
      buf = s[begin];
      s[begin] = s[end];
      s[end] = buf;
   }
   return 1;
}
