#include "CCAR.h"

void CCAR::move(int, int) {
    int curx = this->getMX();
    int cury = this->getMY();

    int curdirection = this->getDirection();
    int curVelocity = this->getVelocity();

    //Moving to the opposite side
    while(curx >= 0 && curx <= 1000) {

        //Check wether object is to the left or right
        if(curdirection) {              //Left
            curx += curVelocity;
            this->setMX(curx);
        } 
        else {                          //Right
            curx -= curVelocity;
            this->setMX(curx);
        }
        _sleep(1000);
    }
    
}