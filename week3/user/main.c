#include "stm32f10x.h"

#define RCC (*(volatile unsigned int *)0x40021018)
#define JOY (*(volatile unsigned int *)0x40011000)
#define LED (*(volatile unsigned int *)0x40011400)
#define INPUT_JOY (*(volatile unsigned int *)0x40011008)
#define OUTPUT_LED (*(volatile unsigned int *)0x40011410)

int main(void) {
  RCC |=0x30;

  JOY &=0x00000000;
  LED &=0x00000000;

  JOY |=0x00888800;
  LED |=0x30033300;

  INPUT_JOY &=0x00000000;
  //INPUT_JOY |=0x3C;

  OUTPUT_LED &=0x00000000;

  while(1) {
    if(!(INPUT_JOY&0x20)) {
      OUTPUT_LED |=0x80;
    }
    else if(!(INPUT_JOY&0x04)) {
      OUTPUT_LED |= 0x08;
    }
    else if(!(INPUT_JOY&0x08)) {
      OUTPUT_LED |= 0x10;
    }
    else if(!(INPUT_JOY&0x10)) {
      OUTPUT_LED |= 0x04;
    }
    OUTPUT_LED |= 0x9C0000;
  }

  return 0;

}
