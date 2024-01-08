#ifndef CCAR5_H
#define CCAR5_H
#include "CVEHICLE.h"

class CCAR5 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR5();
    CCAR5(int width, float startX, float startY, float birdSpeed, int direct);
     ~CCAR5() = default; 
};

#endif