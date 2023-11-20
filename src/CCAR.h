#ifndef CCAR_H
#define CCAR_H

#include "CVEHICLE.h"

class CCAR : public CVEHICLE {
public:
    void Move(int, int) override; 
};

#endif