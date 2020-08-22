#include "display.h"
#include <math.h>
#include <stdio.h>

#define ASCIICONSTANT 64
#define BLANK  0
#define NUMBER 0x10
#define ROW 0x1E

//take a two digit int and print it on the display at current adress pointer
void writetemp2display(int temp){
 int firstdigit = temp%10;
 int seconddigit = temp/10;
 
 Write_Data_2_Display((unsigned char)(NUMBER + seconddigit));
 Write_Command_2_Display(0xC0);
 Write_Data_2_Display((unsigned char)(NUMBER + firstdigit));
 Write_Command_2_Display(0xC0);
}

/*
Write text to the display. Assumes the adress pointer has been set before function is called
*/
void writeText(char text[]){
  int i = 0;
  while(text[i] != 0){
    Write_Data_2_Display(0x20 + (text[i]-ASCIICONSTANT));
    Write_Command_2_Display(0xC0);
    i++;
  }
}
void writeMenu(){
  clear_display();
  Write_Data_2_Display(ROW*1);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("1. Show Temperatures");

  Write_Data_2_Display(ROW*3);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("2. Find Sun");

  Write_Data_2_Display(ROW*5);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("3. Enable Alarm");

  Write_Data_2_Display(ROW*7);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("4. Settings");
}

void writeSettingsMenu(int upper, int lower, int mode){
  clear_display();
  Write_Data_2_Display(ROW*1);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("1. Increase Upperbound");

  Write_Data_2_Display(ROW*2);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("2. Decrease Upperbound");
  
  Write_Data_2_Display(ROW*4);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("3. Increase Lowerbound");

  Write_Data_2_Display(ROW*5);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("4. Decrease Lowerbound");

  Write_Data_2_Display(ROW*7);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("5. Set to Fast Mode");

  Write_Data_2_Display(ROW*8);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeText("6. Set to Normal Mode");

  int pos = ROW*10;
  Write_Data_2_Display(pos & 0xFF);
  Write_Data_2_Display(pos >> 8);
  Write_Command_2_Display(0x24);
  if(mode == 1){
      writeText("Mode: Normal");
  }
  else{
      writeText("Mode: Fast");
  }
  pos = ROW*10+15;
  Write_Data_2_Display(pos & 0xFF);
  Write_Data_2_Display(pos >> 8);
  Write_Command_2_Display(0x24);
  char string[12];
  sprintf(string, "Upper: %d", upper);
  writeText(string);

  pos = ROW*11+15;
  Write_Data_2_Display(pos & 0xFF);
  Write_Data_2_Display(pos >> 8);
  Write_Command_2_Display(0x24);
  sprintf(string, "Lower: %d", lower);
  writeText(string);

}

void printAlarm(int limit){
    int pos = ROW*15;
    Write_Data_2_Display(pos & 0xFF);
    Write_Data_2_Display(pos >> 8);
    Write_Command_2_Display(0x24);
    if(limit == 1){
        writeText("Upper temperature exceeded!");
    }
    else if(limit == 2){
        writeText("Lower temperature exceeded!");
    }
}

void printFindSun(){
    clear_display();
    int pos = ROW*8;
    Write_Data_2_Display(pos & 0xFF);
    Write_Data_2_Display(pos >> 8);
    Write_Command_2_Display(0x24);
    writeText("Searchig for sun...");
}

void printFoundSun(int sunPos){
    clear_display();
    int pos = ROW*8;
    Write_Data_2_Display(pos & 0xFF);
    Write_Data_2_Display(pos >> 8);
    Write_Command_2_Display(0x24);
    char string[30];
    sprintf(string, "Sun's position at: %d degree", sunPos);
    writeText(string);

    pos = ROW*10;
    Write_Data_2_Display(pos & 0xFF);
    Write_Data_2_Display(pos >> 8);
    Write_Command_2_Display(0x24);
    writeText("0: Go Back");
}
