#ifndef __TEXTMODE_GRAPHIC_H__
#define __TEXTMODE_GRAPHIC_H__

enum TextModeColor
{
   BLACK = 0, BLUE, GREEN, SKY,
   RED, PURPLE, BRAWN, WHITE
};

enum TextModeDefine
{
   X_MAX = 79,
   Y_MAX = 24
};

typedef struct TextModeChar
{
      char c : 8;
      unsigned char cclr : 4;
      unsigned char bclr : 4;
} TextModeChar;


void tmode_putchar(
   const char c, const unsigned char cclr, const unsigned char bclr, 
   const unsigned int x, const unsigned int y);

void tmode_boxfill(
   const unsigned int bclr,
   const unsigned int begin_x, const unsigned int begin_y,
   const unsigned int end_x, const unsigned int end_y);

void tmode_puts(
   char *s, const unsigned char cclr, const unsigned char bclr, 
   const unsigned int x, const unsigned int y);


#endif
