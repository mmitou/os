
#include "basic_io.h"
#include "gdt.h"
#include "idt.h"
#include "textmode_graphic.h"

void init_graphic(void);

void kernel_start()
{
   init_pic();
   init_gdt();
   init_idt();
   init_graphic();

   io_sti();

   while(1);
//   halt();

}

void init_graphic(void)
{
   unsigned int x = 0;
   unsigned int y = 0;

   textmode_boxfill(WHITE, x, y, X_MAX, Y_MAX);

   textmode_putchar('a', WHITE, PURPLE, x++, y++);
   textmode_putchar('a', WHITE, PURPLE, x++, y++);
   textmode_putchar('a', WHITE, PURPLE, x++, y++);
   textmode_putchar('a', WHITE, PURPLE, x++, y++);
   textmode_putchar('a', WHITE, PURPLE, x++, y++);
   textmode_putchar('z', WHITE, PURPLE, x++, y++);

   textmode_boxfill(BLUE, x++, y++, X_MAX - 10, Y_MAX - 5);

   textmode_puts("hello, world! hello, world! ", WHITE, BLACK, x++, y++);
   
   textmode_putchar('1', BLACK, GREEN, X_MAX, 0);
   textmode_putchar('2', SKY, RED, 0, Y_MAX);
   textmode_putchar('3', PURPLE, BRAWN, X_MAX, Y_MAX);
}

