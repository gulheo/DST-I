#ifndef SYSTICK_H_  /* Include guard */
#define SYSTICK_H_
extern int nSysticks;
extern int nTicks;
extern int nTicks2;
extern int resetFlag;
void init_systick(void);
void SysTick_Handler();

#endif
