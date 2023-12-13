#ifndef CDINOSAUR_H
#define CDINOSAUR_H

#include "CANIMAL.h"

class CDINOSAUR : public CANIMAL {
private:
    float speed;
    int direction;
    int numFrames; 
public:
    CDINOSAUR();
    CDINOSAUR(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;
    void draw(sf::RenderWindow& window) override;
};

#endif