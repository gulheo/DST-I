#include "at91sam3x8.h"
#include "delay.h"
#include "systick.h"

void initDisplay(){
  * AT91C_PMC_PCER  = (3 << 13);		//enable clock on pio C and D
  * AT91C_PIOC_PER  = (0xFF << 2); 	//enable pioc 2-9
  * AT91C_PIOC_PER  = (0xFF << 12);	//enable pioc 12-19
  * AT91C_PIOC_ODR  = (0xFF << 2);	//set pins 2-9 as input(databus)
  * AT91C_PIOC_OER  = (0xFF << 12);	//set pins 12-19 as output
  * AT91C_PIOC_SODR = (0x9 << 14);	//set wr, rd, ce as high
  * AT91C_PIOC_SODR = (1 << 12);		//set pins 12 to 1 (oe = 1)
  * AT91C_PIOD_PER  = 1;			//enable pin0 piod
  * AT91C_PIOD_OER  = 1;			//set pin0 as output
}

unsigned char Read_status_Display(void){
  unsigned char temp;
  * AT91C_PIOC_ODR  = (0xFF << 2);	//set databus as input
  * AT91C_PIOC_SODR = (1 << 13);		//set dir as input
  * AT91C_PIOC_CODR = (1 << 12);		//clear oe output
  * AT91C_PIOC_SODR = (1 << 17);		//set CD
  * AT91C_PIOC_CODR = (1 << 16); 	//clear chip select
  * AT91C_PIOC_CODR = (1 << 15); 	//clear read display
  delay(20);				//makes a delay
  temp = *AT91C_PIOC_PDSR >> 2;		//read data bus
  * AT91C_PIOC_SODR = (1 << 16);		//set chip select display
  * AT91C_PIOC_SODR = (1 << 15);		//set read display
  * AT91C_PIOC_SODR = (1 << 12);		//disable output
  * AT91C_PIOC_CODR = (1 << 13);		//set dir as output
  return temp;
}

void Write_Command_2_Display(unsigned char Command){
  while((~Read_status_Display() & (3 << 0)) == 3){
  }
  * AT91C_PIOC_CODR = (0xFF << 2);	//clear databus
  * AT91C_PIOC_SODR = ((unsigned int)Command << 2);	//set command to databus
  * AT91C_PIOC_CODR = (1 << 13); 	//set dir as output
  * AT91C_PIOC_CODR = (1 << 12);		//enable output
  * AT91C_PIOC_OER  = (0xFF << 2);	//set databus as output
  * AT91C_PIOC_SODR = (1 << 17);		//set CD signal high
  * AT91C_PIOC_CODR = (1 << 16);		//clear chip select
  * AT91C_PIOC_CODR = (1 << 14);		//clear write display
  delay(20);				//makes a delay
  * AT91C_PIOC_SODR = (1 << 16);		//set chip enable display
  * AT91C_PIOC_SODR = (1 << 14);		//set write display
  * AT91C_PIOC_SODR = (1 << 12); 	//disable output
  * AT91C_PIOC_ODR  = (0xFF << 2); 	//make databus as input
}

void Write_Data_2_Display(unsigned char Data){
  while((~Read_status_Display() & (3 << 0)) == 3){
  }
  * AT91C_PIOC_CODR = (0xFF << 2);	//clear databus
  * AT91C_PIOC_SODR = ((unsigned int)Data << 2);	//set data to databus
  * AT91C_PIOC_CODR = (1 << 13); 	//set dir as output
  * AT91C_PIOC_CODR = (1 << 12);		//enable output
  * AT91C_PIOC_OER  = (0xFF << 2);	//set databus as output
  * AT91C_PIOC_CODR = (1 << 17);		//set CD signal low
  * AT91C_PIOC_CODR = (1 << 16);		//clear chip select
  * AT91C_PIOC_CODR = (1 << 14);		//clear write display
  delay(20);				//makes a delay
  * AT91C_PIOC_SODR = (1 << 16);		//set chip enable display
  * AT91C_PIOC_SODR = (1 << 14);		//set write display
  * AT91C_PIOC_SODR = (1 << 12); 	//disable output
  * AT91C_PIOC_ODR  = (0xFF << 2); 	//make databus as input
}

void init_Display(void){
  * AT91C_PIOD_CODR = 1;			//clear reset display
  nSysticks = 0;
  while(nSysticks < 1000){
    
  }
  * AT91C_PIOD_SODR = 1;			//set reset display
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40);		//Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); 		//Set graphic home address
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41); 		// Set text area
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); 		// Set graphic area
  Write_Command_2_Display(0x80); 		// text mode
  Write_Command_2_Display(0x94); 		// Text on graphic off 
}

void clear_display(void){
 Write_Data_2_Display(0x0);
 Write_Data_2_Display(0x0);
 Write_Command_2_Display(0x24);
  for(int i = 0; i < 16*30; i++){
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0xC0);
  }
}
