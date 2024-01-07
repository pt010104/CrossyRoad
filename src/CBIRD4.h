#ifndef CBIRD4_H
#define CBIRD4_H
#include "CANIMAL.h"

class CBIRD4 : public CANIMAL {
private:

    int numFrames; 
public:
    CBIRD4();
    CBIRD4(int width, float startX, float startY, float birdSpeed, int direct);
     ~CBIRD4() = default; 
};

#endif