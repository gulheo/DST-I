#include "at91sam3x8.h"
#include "core_cm3.h"
#include "delay.h"
#include "temp.h"
#include "print2display.h"
#include "display.h"
#include <stdio.h>
#include "timekeeper.h"
#include <stdlib.h>
#define ROW 0x1E

double tempList[7][1440];
int listSize[7];

double avgsum(int day){
    double sum = 0;
    int i = 0;
    for(; i < listSize[day]; i++){
        sum += tempList[day][i];
    }
    return sum/(double) i;
}

double minitemp(int day){
    int min = 999;
    for(int i = 0; i < listSize[day]; i++){
        if(tempList[day][i] < min){
            min = tempList[day][i];
        }
    }
    if(min == 999){min = 0;}
    return min;
}

double maxitemp(int day){
    int max = 0;
    for(int i = 0; i < listSize[day]; i++){
        if(tempList[day][i] > max){
            max = tempList[day][i];
        }
    }
    return max;
}

void resetTempList(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 1440; j++){
            tempList[i][j] = 0;
        }
        listSize[i] = 0;
    }
}

void writetemp(){
    Write_Data_2_Display(ROW);
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0x24);
    writeText("Dag:  1  2  3  4  5  6  7");

    Write_Data_2_Display(ROW*3);
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0x24);
    writeText("avg: ");
    for(int i = 0; i < 7; i++){
        writetemp2display(avgsum(i));
        writeText(" ");
    }


    Write_Data_2_Display(ROW*5);
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0x24);
    writeText("min: ");
    for(int i = 0; i < 7; i++){
        writetemp2display(minitemp(i));
        writeText(" ");

    }

    Write_Data_2_Display(ROW*7);
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0x24);
    writeText("max: ");
    for(int i = 0; i < 7; i++){
        writetemp2display(maxitemp(i));
        writeText(" ");
    }

    unsigned int pos = ROW*11;
    Write_Data_2_Display(pos & 0xFF);
    Write_Data_2_Display(pos >> 8);
    Write_Command_2_Display(0x24);
    writeText("0: Go back");

}

void logTemp(double temp){
    tempList[ndays%7][listSize[ndays]] = temp;
    listSize[ndays]++;

}




