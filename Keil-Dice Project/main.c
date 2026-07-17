#include <reg51.h>
#include "lcd.h"

sbit btn_select = P3^0;
sbit btn_roll   = P3^1;
sbit btn_reset  = P3^2;

unsigned char dice[6]={
0x06,0x5B,0x4F,0x66,0x6D,0x7D
};

unsigned char players=1;
unsigned char currentPlayer=1;

unsigned char i,index;

bit game_started=0;


//---------------- RESET ----------------

void soft_reset(){

players=1;

currentPlayer=1;

game_started=0;

P1=0x00;

LCD_clear();
}


//---------------- SETUP ----------------

void show_setup(){

LCD_set_cursor(0,0);

LCD_write_string("Players: ");

LCD_write_char(players+48);

LCD_write_string("   ");

LCD_set_cursor(1,0);

LCD_write_string("Press To Start");
}


//---------------- TURN ----------------

void show_turn(){

LCD_set_cursor(0,0);

if(currentPlayer==1)
LCD_write_string("Player 1 Turn ");

if(currentPlayer==2)
LCD_write_string("Player 2 Turn ");

if(currentPlayer==3)
LCD_write_string("Player 3 Turn ");

if(currentPlayer==4)
LCD_write_string("Player 4 Turn ");

LCD_set_cursor(1,0);

LCD_write_string("Roll Dice     ");
}


//---------------- TIMER ----------------

void timer0_init(){

TMOD=0x01;

TH0=0;

TL0=0;

TR0=1;

}



//---------------- MAIN ----------------

void main(){

P3=0xFF;

LCD_init();

timer0_init();

START:

game_started=0;

players=1;

currentPlayer=1;


//=========== SETUP ===========

while(game_started==0){

show_setup();


// RESET

if(btn_reset==0){

delay(3);

if(btn_reset==0){

soft_reset();

while(btn_reset==0);

goto START;

}

}


// SELECT

if(btn_select==0){

delay(3);

if(btn_select==0){

players++;

if(players>4)
players=1;

while(btn_select==0);

}

}


// START

if(btn_roll==0){

delay(3);

if(btn_roll==0){

game_started=1;

while(btn_roll==0);

}

}

}



//=========== GAME ===========

while(1){

show_turn();


// RESET

if(btn_reset==0){

delay(3);

if(btn_reset==0){

soft_reset();

while(btn_reset==0);

goto START;

}

}


// ROLL

if(btn_roll==0){

delay(3);

if(btn_roll==0){

index=((TH0+TL0+currentPlayer+P1)%6);


for(i=0;i<10;i++){

P1=dice[i%6];

delay(20);

}


P1=dice[index];


// BONUS TURN

if(index==5){

LCD_set_cursor(1,0);

LCD_write_string("Bonus Turn! ");

delay(20);

}
else{

currentPlayer++;

if(currentPlayer>players)

currentPlayer=1;

}

while(btn_roll==0);

}

}

}

}