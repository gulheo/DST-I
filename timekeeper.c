#define normal 1
#define fast 60
int ndays;
int nhours;
int nsec;
int mode = normal;
int resetFlag;

void resetTime(){
    ndays = 0;
    nhours = 0;
    nsec = 0;
    resetFlag = 0;
}
void updateTime(int nSysticks){
    nsec =mode*nSysticks/1000;
    nhours = nsec/3600;
    ndays = (nhours/24);
    if(ndays == 7){
        resetFlag = 1;
    }
}

void setNormalMode(){
    mode = normal;
}

void setFastMode(){
    mode = fast;
}

//used purely for certain debugging
void setSuperMode(){
    mode = 60*24;
}
