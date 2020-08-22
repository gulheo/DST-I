#include "at91sam3x8.h"

#define turndegree 28
#define zerodegree 6700

void initPower(){
  *AT91C_PMC_PCER1 = (1 << 4);
  *AT91C_PMC_PCER = (1 << 12);
  *AT91C_PIOB_ABMR = (1 << 17);
  *AT91C_PIOB_PDR = (1 << 17);
  *AT91C_PWMC_ENA = (1 << 1);
  *AT91C_PWMC_CH1_CMR = 5;
  *AT91C_PWMC_CH1_CPRDR = 52500; //52500
  *AT91C_PWMC_CH1_CDTYR = 3700;  //left = 1837, neutral = 3937, right = 6037
}

void turnServor(int degree){
    if(degree > 180){
        degree = 180;
    }  
    else if(degree < 0){
        degree = 0;
    }
    
    *AT91C_PWMC_CH1_CDTYR = zerodegree-turndegree*degree;
}
