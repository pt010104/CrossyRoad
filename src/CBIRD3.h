#ifndef CBIRD3_H
#define CBIRD3_H
#include "CANIMAL.h"

class CBIRD3 : public CANIMAL {
private:

    int numFrames; 
public:
    CBIRD3();
    CBIRD3(int width, float startX, float startY, float birdSpeed, int direct);
     ~CBIRD3() = default; 
};

#endif