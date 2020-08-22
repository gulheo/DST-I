#include <stdbool.h>
#define OFF 0
#define ON 1
int lBound;
int uBound;
int alarm;

void setAlarm(){
    alarm = ON;
}

void resetAlarm(){
    lBound = 15;
    uBound = 30;
    alarm = OFF;
}

void turnOffAlarm(){
    alarm = OFF;
}

void incUpper(){
    ++uBound;
}

void decUpper(){
    --uBound;
}

void incLower(){
    ++lBound;
}

void decLower(){
    --uBound;
}

//check if temp exceeds lower and upper temperature limits
//return 1 if temperature exceeds upper limit, 2 if lower limit, 
// 0 otherwise.
int checkAlarm(int temp){
    if(alarm == ON){
        if(temp > uBound){
            return 1;
        }
        else if(temp < lBound){
            return 2;
        }
    }
    return 0;
}
