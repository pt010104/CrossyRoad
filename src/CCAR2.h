#ifndef CCAR2_H
#define CCAR2_H
#include "CVEHICLE.h"

class CCAR2 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR2();
    CCAR2(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;    
     ~CCAR2() = default; 
};

#endif