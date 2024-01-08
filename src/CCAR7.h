#ifndef CCAR7_H
#define CCAR7_H
#include "CVEHICLE.h"

class CCAR7 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR7();
    CCAR7(int width, float startX, float startY, float birdSpeed, int direct);
     ~CCAR7() = default; 
};

#endif