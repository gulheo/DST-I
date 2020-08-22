#ifndef TIMEKEEPER_H_  /* Include guard */
#define TIMEKEEPER_H_
extern int ndays;
extern int nsec;
extern int mode;
extern int resetFlag;
#define fast 60
#define normal 1

void resetTime();
void updateTime(int nSysticks);
void setNormalMode();
void setFastMode();
void setSuperMode();

#endif
