#ifndef CTRUCK_H
#define CTRUCK_H

#include "CVEHICLE.h"

class CTRUCK: public CVEHICLE {
public:
    void move(int, int) override;
};

#endif