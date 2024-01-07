#ifndef CCAR4_H
#define CCAR4_H
#include "CVEHICLE.h"

class CCAR4 : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR4();
    CCAR4(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;    
     ~CCAR4() = default; 
};

#endif