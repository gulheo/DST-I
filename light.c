#include "at91sam3x8.h"

void initLight(){
  *AT91C_PMC_PCER1 = (1 << 5);	//ENABLE CLOCK FOR ADC
  *AT91C_PMC_PCER = (1 << 11);	//ENABLE CLOCK PIOA
  *AT91C_ADCC_MR = (2 << 8);	//SET PRESCALER TO 2
}

//get light value by measure voltage from light sens and convert to digital signal
int measureLight(){
  *AT91C_ADCC_CHER = (1 << 1);
  *AT91C_ADCC_CR = (1 << 1);
  //wait for ad conversion to finish
  while(1){
    if((*AT91C_ADCC_SR & (1 << 24)) == (1 << 24)){
       break;
    }
  }
  int light = *AT91C_ADCC_LCDR & 0xFFF;
  return light;
}