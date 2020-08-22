#ifndef TEMP_H_   /* Include guard */
#define TEMP_H_
extern char tempFlag;
void initTemp();
void startTemp();
double readTemp();
void TC0_Handler();

#endif
