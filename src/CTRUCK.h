#ifndef CTRUCK_H
#define CTRUCK_H

#include "CVEHICLE.h"

class CTRUCK: public CVEHICLE {
public:
    void Move(int, int) override;
};

#endif