#ifndef CCAR3_H
#define CCAR3_H
#include "CVEHICLE.h"

class CCAR3 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR3();
    CCAR3(int width, float startX, float startY, float birdSpeed, int direct);
     ~CCAR3() = default; 
};

#endif