#include "at91sam3x8.h"

int readKeyPad(void){
    int value = -1;
    * AT91C_PIOD_CODR = (1 << 2); 		//clear oe
    * AT91C_PIOC_OER = (7 << 7);		//make all column pin as output
    * AT91C_PIOC_SODR = (7 << 7);		//set all column pin as high

    for(int i = 0; i < 3; i++){
        *AT91C_PIOC_CODR = (1 << 7 + i);	//clear one column at the time
        for(int j = 0; j < 4; j++){
            unsigned int temp = *AT91C_PIOC_PDSR; 
            if((~temp & (1 << 2 + j)) == (1 << 2 + j)){
                value = j*3 + i+1;
            }
        }
        * AT91C_PIOC_SODR = (7 << 7);
    }
    * AT91C_PIOC_ODR = (7 << 7);
    * AT91C_PIOD_SODR = (1 << 2);
    if(value == 11){
        value = 0;
    }
    return value;
}

void initPorts(){
    * AT91C_PMC_PCER  = (3 << 13);	//enable clock on pio C and D
    * AT91C_PIOC_PER  = 0x3BC;		//enable pioc 2,3,4,5,7,8,9
    * AT91C_PIOC_ODR  = 0x3BC;		//set pins as input
    * AT91C_PIOD_PER  = (1 << 2);		//enable piod 2
    * AT91C_PIOD_OER  = (1 << 2);		//set as output
    * AT91C_PIOD_SODR = (1 << 2);		//set piod2 output as 1(turn off oe)
}



