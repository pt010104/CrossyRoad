#ifndef CBIRD_H
#define CBIRD_H

#include "CANIMAL.h"

class CBIRD : public CANIMAL {
private:
    int speed = 1;
    int direction = 1;
public:
    void Move() override; 
};

#endif