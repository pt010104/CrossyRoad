#ifndef CCAR_H
#define CCAR_H

#include "CVEHICLE.h"

class CCAR : public CVEHICLE {
private:
    int speed = 1;
    int direction = 1;
public:
    void Move(int dx, int dy) override; 
};
#endif