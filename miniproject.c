#include<lpc21xx.h>
#include"lcd_header.h"
#define  LED 1<<12
#define  BUZZER 1<<13
#define SW 17
volatile unsigned int flag1=0;
volatile unsigned int flag2=0;
void LCD_DISPLAY(void);
unsigned int ENTRY=0;
unsigned int EXIT=0;
int count=0;
 void ext0__into__isr(void)__irq
 {
    IOCLR0=LED;
    EXTINT=0X01;
	flag1=1;
	VICVectAddr=0;
 }
 void ext1__into__isr(void)__irq
 {
    EXTINT=0X02;
	flag2=1;
	VICVectAddr=0;
 }
 int main()
 {
   PINSEL0|=0x20000000;
   PINSEL1|=0X01;
   IODIR0|=LED|BUZZER|LCD_D|RS|E;
   LCD_INIT();
   LCD_DISPLAY();
   
   
   VICIntSelect=0;
   VICVectCntl0=(1<<5)|14;
   VICVectAddr0=(unsigned long)ext0__into__isr;
   VICVectCntl1=(1<<5)|15;
   VICVectAddr1 =(unsigned long)ext1__into__isr;
   EXTMODE=0x00;
   EXTPOLAR=0x00;
   VICIntEnable=(1<<14)|(1<<15);
   while(1)
   {
   if(flag1)
   {  
   ++count;
   ++ENTRY;
   
   IOCLR0=BUZZER;
   delay_millisecond(500);
   IOSET0=BUZZER;
   delay_millisecond(500);
   flag1=0;
   }
   if(flag2)
   {
   if(count>0)
   {  
   count--;
   EXIT++;
   IOCLR0=BUZZER;
 delay_millisecond(500);
 IOSET0=BUZZER;
 delay_millisecond(500);
   }
   flag2=0;
   }
   
   if(((IOPIN0>>SW)&1)==0)
   {
     LCD_COMMAND(0X01);
     LCD_COMMAND(0X80);
     LCD_STR("VISITOR ENTRY:");
     LCD_INTEGER(ENTRY);
     LCD_COMMAND(0XC0);
     LCD_STR("VISITOR EXIT:");
     LCD_INTEGER(EXIT);
     delay_millisecond(3000);
     LCD_COMMAND(0X01);
   }
   if((flag1==0)&&(flag2==0))
   {
     if(count>0)
     {
     IOCLR0=LED;
     }
     else
     {
     IOSET0=LED;
     }
     LCD_COMMAND(0X80);
     LCD_STR("VISITOR COUNT");
     LCD_COMMAND(0XC6);
     LCD_INTEGER(count);
     delay_millisecond(500);
     }     
   }
}
void LCD_DISPLAY()
{
  LCD_INIT();
  LCD_COMMAND(0X80);
  LCD_STR("INTERRUPT DRIVEN    VISITOR COUNT SYSTEM");
  delay_second(2);
  LCD_COMMAND(0X01);
}
