#include "stm32f10x.h"

#define RCC (*(volatile unsigned *)0x40021018)

#define Selection (*(volatile unsigned *)0x40010C04) // No reaction, modify plz.
#define User (*(volatile unsigned *)0x40011404) //input
#define JOY (*(volatile unsigned *)0x40011000) //input
#define RELAY (*(volatile unsigned *)0x40011004) 
#define LED (*(volatile unsigned *)0x40011400)

#define INPUT_S (*(volatile unsigned *)0x40010C08)
#define INPUT_U (*(volatile unsigned *)0x40011408)
#define INPUT_JOY (*(volatile unsigned *)0x40011008)

#define OUTPUT_RELAY (*(volatile unsigned *)0x40011010)
#define OUTPUT_LED (*(volatile unsigned *)0x40011410)


void delay() {
  int i;
  for (i=0; i<10000000;i++) {}
}

void up() {
  //delay();
  OUTPUT_RELAY = 0xffffffff; 
  delay();
  OUTPUT_RELAY = ~0x00000200;
}

void led1() {
  OUTPUT_LED |=0x04; 
  delay();
  OUTPUT_LED =0x1C0000;
}

void led2() {
  OUTPUT_LED |= 0x08;
  delay();
  OUTPUT_LED = 0x1C0000;
}

void led3() {
  OUTPUT_LED |=0x10; 
  delay();
  OUTPUT_LED |= 0x1C0000;
}

int main(void) {
  RCC |= 0x38;
  
  Selection &= 0x00000000;
  Selection |= 0x00000008;
  
  JOY &= 0x00000000;
  JOY |= 0x00800000;
  
  User &= 0x00000000;
  User |= 0x00088000;

  RELAY &= 0x00000000;
  RELAY |= 0x00000030;
  
  LED &= 0x00000000;
  LED |= 0x00033300;
  
  INPUT_JOY &=0x00000000;
  INPUT_JOY |= 0x20;
  
  INPUT_S &= 0x00000000;
  INPUT_S |= 0x100;
  
  INPUT_U &= 0x00000000;
  INPUT_U |= 0x1800;
  
  OUTPUT_RELAY &= 0x0000ffff;
  OUTPUT_LED &= 0x00000000;

  while(1) {
   if( !(INPUT_U & 0x0800)) 
     led1();
   else if(!(INPUT_U & 0x1000)) 
     led2();
   else if(!(INPUT_JOY & 0x0020)) 
     up();
   else if(!(INPUT_S & 0x0100)) 
     led3();
   //delay();
  }
  
  return 0;
}
    
  