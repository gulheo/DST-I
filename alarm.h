#ifndef ALARM_H_   /* Include guard */
#define ALARM_H_

extern int lBound;
extern int uBound;
void resetAlarm();
void setAlarm();
int incUpper();
int decUpper();
int incLower();
int decLower();
int checkAlarm(int temp);
void turnOffAlarm();

#endif
