#include "at91sam3x8.h"
#include "core_cm3.h"
#include "delay.h"
char tempFlag = 0;
void initTemp(){
  *AT91C_PMC_PCER = 0x8001000;		//ENABLE CLOCK FOR TC0 and PIOB
  *AT91C_TC0_CMR = 0;	//CHOOSE TIMER_CLOCK1 AS TCCLK
  *AT91C_TC0_CCR = 5;			//ENABLE CLOCK AND SW RESET
  *AT91C_TC0_CMR = (3 << 17);		//SET REGB TO RISING
  *AT91C_PIOB_PER = (1 << 25);		//ENABLE PIOB25
  NVIC_ClearPendingIRQ((IRQn_Type)27);
  NVIC_EnableIRQ((IRQn_Type)27);
}

//tell the temp sensor to start measure temp
void startTemp(){
  *AT91C_PIOB_OER = (1 << 25);		//LOW START PULSE
  delay(25);
  *AT91C_PIOB_ODR = (1 << 25);		//END START PULSE
  delay(35000);
  *AT91C_TC0_CCR = 4;			//RESET TC
  *AT91C_TC0_IER = (1 << 6);		//ENABLE INTERRUPT ON LDRBS
}

//get the temperature by calc time diff from timer counter
double readTemp(){
  unsigned int a = *AT91C_TC0_RA;
  unsigned int b = *AT91C_TC0_RB;
  double timeUs = (double)(b - a)/42.0; 
  double temp = timeUs/5 - 273.15;
  return temp;
}

void TC0_Handler(){
  *AT91C_TC0_IDR = (1 << 6);		//DISABLE INTERRUPT ON LDRBS
  tempFlag = 1;
}

