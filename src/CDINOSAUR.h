#ifndef CDINOSAUR_H
#define CDINOSAUR_H

#include "CANIMAL.h"

class CDINOSAUR : public CANIMAL {
private:
    int numFrames; 
public:
    CDINOSAUR();
    CDINOSAUR(int width, float startX, float startY, float birdSpeed, int direct);
    void Move()  override;
};

#endif