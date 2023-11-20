#ifndef CTRUCK_H
#define CTRUCK_H

#include "CVEHICLE.h"

class CTRUCK: public CVEHICLE {
private:
    int speed = 1;
    int direction = 1;
public:
    void Move(int dx, int dy) override; 
};

#endif