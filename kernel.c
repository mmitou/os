
#include "basic_io.h"
#include "textmode_graphic.h"

void init_graphic(void);

void kernel_start()
{
   init_graphic();
   halt();
}

void init_graphic(void)
{
   unsigned int x = 0;
   unsigned int y = 0;


   tmode_boxfill(WHITE, x, y, X_MAX, Y_MAX);

   tmode_putchar('a', WHITE, PURPLE, x++, y++);
   tmode_putchar('a', WHITE, PURPLE, x++, y++);
   tmode_putchar('a', WHITE, PURPLE, x++, y++);
   tmode_putchar('a', WHITE, PURPLE, x++, y++);
   tmode_putchar('a', WHITE, PURPLE, x++, y++);
   tmode_putchar('z', WHITE, PURPLE, x++, y++);

   tmode_boxfill(BLUE, x++, y++, X_MAX - 5, Y_MAX - 5);

   tmode_puts("hello, world! hello, world! ", WHITE, BLACK, x++, y++);

   
   tmode_putchar('1', WHITE, RED, X_MAX, 0);
   tmode_putchar('2', WHITE, RED, 0, Y_MAX);
   tmode_putchar('3', WHITE, RED, X_MAX, Y_MAX);
}

