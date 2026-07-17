#include "lcd.h"


void delay(unsigned int d){

unsigned int i,j;

for(i=0;i<d;i++)
for(j=0;j<1275;j++);

}



void LCD_command(unsigned char cmd){

LCD_DATA_PORT=cmd;


LCD_CTRL_PORT&=~LCD_RS;


LCD_CTRL_PORT|=LCD_EN;

delay(2);


LCD_CTRL_PORT&=~LCD_EN;

delay(2);

}



void LCD_write_char(unsigned char dat){

LCD_DATA_PORT=dat;


LCD_CTRL_PORT|=LCD_RS;


LCD_CTRL_PORT|=LCD_EN;

delay(2);


LCD_CTRL_PORT&=~LCD_EN;

delay(2);

}



void LCD_write_string(char *str){

while(*str)

LCD_write_char(*str++);

}



void LCD_set_cursor(unsigned char row,unsigned char col){

if(row==0)

LCD_command(0x80+col);

else

LCD_command(0xC0+col);

}



void LCD_clear(){

LCD_command(0x01);

delay(5);

}



void LCD_init(){

delay(50);

LCD_command(0x38);

LCD_command(0x0C);

LCD_command(0x06);

LCD_command(0x01);

delay(20);

}