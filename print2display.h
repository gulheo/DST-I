#ifndef PRINT2DISPLAY_H_  /* Include guard */
#define PRINT2DISPLAY_H_

void writetemp2display(int temp);
void writeText(char text[]);
void writeMenu();
void writeSettingsMenu(int upper, int lower, int mode);
void printAlarm(int limit);
void printFindSun();
void printFoundSun(int sunPos);

#endif
