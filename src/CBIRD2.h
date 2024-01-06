#ifndef CBIRD2_H
#define CBIRD2_H
#include "CANIMAL.h"

class CBIRD2 : public CANIMAL {
private:

    int numFrames; 
public:
    CBIRD2();
    CBIRD2(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;    
     ~CBIRD2() = default; 
};

#endif