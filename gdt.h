#ifndef _GDT_H_
#define _GDT_H_

typedef enum DescripterType
{
   DATA_RONLY = 0x0,
   DATA_RONLY_ACCESS,
   DATA_R_W,
   DATA_R_W_ACCESS,
   DATA_RONLY_EXPDOWN,
   DATA_RONLY_EXPDOWN_ACCESS,
   DATA_R_W_EXPDOWN,
   DATA_R_W_EXPDOWN_ACCESS,
   CODE_EXEONLY = 0x8,
   CODE_EXEONLY_ACCESS,
   CODE_EXE_R,
   CODE_EXE_R_ACCESS,
   CODE_EXEONLY_CNFRMNG,
   CODE_EXEONLY_CNFRMNG_ACCESS,
   CODE_EXE_RONLY_CNFRMNG,
   CODE_EXE_RONLY_CNFRMNG_ACCESS = 0x15
} DescripterType;

typedef enum SegmentStatus
{
   IS_NOT_SEGMENT = 0x0,
   IS_SEGMENT = 0x1
} SegmentStatus;

typedef enum PhysicalMemoryStatus
{
   NOT_ON_PHYS_MEMORY = 0x0,
   ON_PHYS_MEMORY = 0x1
} PhysicalMemoryStatus;

typedef enum LimitStatus
{
   LIMIT_BYTE = 0x0,
   LIMIT_4KBYTES = 0x1
} LimitStatus;

typedef struct SegmentDescripter
{
      unsigned short limit_low;
      unsigned short base_low;
      unsigned char base_mid;
      unsigned char type : 4;       /* DescripterType */
      unsigned char s : 1;          /* SegmentStatus */
      unsigned char dpl : 2;        /* DescripterPrivilegeLevel */
      unsigned char p : 1;          /* PhysicalMemoryStatus */
      unsigned char limit_high : 4;
      unsigned char avl : 1;        /* user define freely */
      unsigned char no_use : 1;     /* always 0 */
      unsigned char d : 1;          /* D/B Flag */
      unsigned char g : 1;          /* G Flag */
      unsigned char base_high;
      
} SegmentDescripter;

enum GDTParams
{
   GDT_HEAD_ADDR = 0x168000,
   GDT_SIZE = 0x10000
};


void set_segmentdescripter(
   SegmentDescripter* s, 
   const unsigned long limit, const unsigned long baseaddr,
   const DescripterType type, const unsigned long dpl,
   const PhysicalMemoryStatus p, const LimitStatus g);

void init_gdt(void);
#endif
