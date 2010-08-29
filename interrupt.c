#include "interrupt.h"
#include "basic_io.h"

typedef struct GateDescripter
{
      unsigned short handler_low;
      unsigned short codesegment;
      unsigned char no_use;
      unsigned char type;
      unsigned short hadler_high;
} GateDescripter;

enum IdtDefine
{
   GATE_NUM = 256
};

/*
static GateDescripter idtable[GATE_NUM];
*/


void* make_idiscripter(void)
{
   return 0;
}

void init_idt(void)
{
/*
   GateDescripter *p = idtable;

   load_idtr(p);
*/ 
}


