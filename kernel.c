
#include "basic_io.h"
#include "gdt.h"
#include "idt.h"
#include "textmode_graphic.h"

void init_graphic(void);

void kernel_start()
{
   io_cli();
   init_gdt();
   init_idt();
   io_sti();

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

   tmode_boxfill(BLUE, x++, y++, X_MAX - 10, Y_MAX - 5);

   tmode_puts("hello, world! hello, world! ", WHITE, BLACK, x++, y++);
   
   tmode_putchar('1', BLACK, GREEN, X_MAX, 0);
   tmode_putchar('2', SKY, RED, 0, Y_MAX);
   tmode_putchar('3', PURPLE, BRAWN, X_MAX, Y_MAX);
}

