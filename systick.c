#include "core_cm3.h"


void init_systick(void){
  SysTick_Config((uint32_t)83999);	//set systick to 1 ms
}

int nSysticks = 0;
int nTicks = 0;
int nTicks2 = 0;
void SysTick_Handler(){
  nSysticks++;
  nTicks++;
  nTicks2++;
}
