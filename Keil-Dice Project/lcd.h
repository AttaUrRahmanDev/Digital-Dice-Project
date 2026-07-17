#ifndef LCD_H
#define LCD_H

#include <reg51.h>


#define LCD_DATA_PORT P2

#define LCD_CTRL_PORT P3


#define LCD_RS 0x20

#define LCD_EN 0x40



void LCD_init();

void LCD_command(unsigned char cmd);

void LCD_write_char(unsigned char dat);

void LCD_write_string(char *str);

void LCD_set_cursor(unsigned char row,unsigned char col);

void LCD_clear();

void delay(unsigned int d);


#endif