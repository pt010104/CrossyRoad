#ifndef CBIRD5_H
#define CBIRD5_H

#include "CANIMAL.h"

class CBIRD5 : public CANIMAL {
private:
    int numFrames; 
public:
    CBIRD5();
    CBIRD5(int width, float startX, float startY, float birdSpeed, int direct);
     ~CBIRD5() = default; 
};

#endif