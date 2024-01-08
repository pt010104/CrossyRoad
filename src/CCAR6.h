#ifndef CCAR6_H
#define CCAR6_H
#include "CVEHICLE.h"

class CCAR6 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR6();
    CCAR6(int width, float startX, float startY, float birdSpeed, int direct);
     ~CCAR6() = default; 
};

#endif