#ifndef CCAR_H
#define CCAR_H
#include "CVEHICLE.h"

class CCAR : public CANIMAL {
private:

    int numFrames; 
public:
    CCAR();
    CCAR(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;    
     ~CCAR() = default; 
};

#endif