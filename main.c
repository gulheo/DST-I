#include <stdbool.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "temp.h"
#include "light.h"
#include "delay.h"
#include <stdio.h>
#include "servor.h"
#include "display.h"
#include "print2display.h"
#include "systick.h"
#include "logTemp.h"
#include "timekeeper.h"
#include "keypad.h"
#include "alarm.h"

#define MAINMENU 1
#define TEMPMENU 2
#define SETTINGSMENU 3
#define FINDSUN 4
#define FOUNDSUN 5
#define UPPER 1
#define LOWER 2
void updateDisplay(int menu);

int main(){
    SystemInit();
    init_systick();
    initDisplay();	
    init_Display();
    initPorts();
    initTemp();
    initLight();
    initPower();

    clear_display();
    writeMenu();
    resetTime();

    resetAlarm();


    int findSun = 0;
    int light = 0;
    int peakLight = 99999;
    int lightPos = 0;
    int servorPos = 0;

    bool isKeyDown = false;
    int key = -1;

    int menuShown = MAINMENU;


    nSysticks = 0;
    nTicks = 0;
    while(1){
        updateTime(nSysticks);
        if(resetFlag == 1){
            resetTempList();
            resetTime();
            nSysticks = 0;
            resetFlag = 0;
        }

        key = readKeyPad();
        if(!isKeyDown){
            if(menuShown == MAINMENU){
                switch(key){
                    case 1:
                        writetemp();
                        isKeyDown = true;
                        menuShown = TEMPMENU;
                        break;
                    case 2:
                        findSun = 1;
                        isKeyDown = true;
                        menuShown = FINDSUN;
                        printFindSun();
                        break;
                    case 3:
                        isKeyDown = true;
                        setAlarm();
                        break;
                    case 4:
                        isKeyDown = true;
                        menuShown = SETTINGSMENU;
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                }
            }
            else if(menuShown == TEMPMENU){
                writetemp();
                switch(key){
                    case 0:
                        writeMenu();
                        isKeyDown = true;
                        menuShown = MAINMENU;
                        break;
                }
            }
            else if(menuShown == SETTINGSMENU){
                switch(key){
                    case 0:
                        writeMenu();
                        isKeyDown = true;
                        menuShown = MAINMENU;
                        break;
                    case 1:
                        isKeyDown = true;
                        incUpper();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                    case 2:
                        isKeyDown = true;
                        decUpper();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                    case 3:
                        isKeyDown = true;
                        incLower();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                    case 4:
                        isKeyDown = true;
                        decLower();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                    case 5:
                        isKeyDown = true;
                        setFastMode();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                    case 6:
                        isKeyDown = true;
                        setNormalMode();
                        writeSettingsMenu(uBound, lBound, mode);
                        break;
                }
            }
            else if(menuShown == FOUNDSUN){
                switch(key){
                    case 0:
                        writeMenu();
                        isKeyDown = true;
                        menuShown = MAINMENU;
                        break;
                }
            }
        }
        else{
            if(key == -1){
                isKeyDown = false;
            }
        }

        if(findSun == 1){
            light = measureLight();
            if(light < peakLight){
                peakLight = light;
                lightPos = servorPos;
            }
        }
        if(nTicks * mode> 60000){
            nTicks = 0;
            startTemp();

        }

        if(nTicks2 > 500){
            if(findSun == 1){
                turnServor((servorPos++)*10);
                if(servorPos > 19){
                    servorPos = 0;
                    findSun = 0;
                    printFoundSun(lightPos*10);
                    menuShown = FOUNDSUN;
                    turnServor(0);
                    

                }
            }
            nTicks2 = 0;
        }
	//temp ready to read
        if(tempFlag == 1){
            tempFlag = 0;
            double temperature = readTemp();
            logTemp(temperature);
            int alarm = checkAlarm(temperature);
            if(alarm == UPPER){ //upperbound exceeded
                printAlarm(alarm);
                turnOffAlarm();
            }
            else if(alarm == LOWER){//lowerbound exceeded
                printAlarm(alarm);
                turnOffAlarm();
            }
        }
    }
}
