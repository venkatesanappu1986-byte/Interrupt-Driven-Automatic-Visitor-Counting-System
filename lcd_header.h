#include<lpc21xx.h>
#include"delay.h"
#define LCD_D  0XFF<<0
#define RS 1<<8
#define E 1<<9

void LCD_COMMAND(unsigned char cmd) ;
void LCD_INIT(void)
{
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}
void LCD_COMMAND(unsigned char cmd)

{
IOCLR0=LCD_D;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=E;
delay_millisecond(2);
IOCLR0=E;
}
void LCD_DATA(unsigned char databyte)
{
IOCLR0=LCD_D;
IOSET0=databyte;
IOSET0=RS;
IOSET0=E;
delay_millisecond(2);
IOCLR0=E;
}
void LCD_STR(unsigned char *s)
{
  while(*s)
  {
    LCD_DATA(*s++);
	}
}
void LCD_INTEGER(int number)
{
  unsigned char arr[5];
  signed char i=0;
  if(number==0)
  LCD_DATA('0');
  else
  {
  if(number<0)
  {
  LCD_DATA('-');
  number=-number;
  }
  while(number>0)
  {
  arr[i++]=number%10;
  number=number/10;
  }
  for(--i;i>=0;i--)
  {
  LCD_DATA(arr[i]+48);
  }
  }
}




