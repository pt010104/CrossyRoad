#ifndef CBIRD_H
#define CBIRD_H
#include "CANIMAL.h"

class CBIRD : public CANIMAL {
private:
    float speed;
    int direction;
    int numFrames; 
public:
    CBIRD();
    CBIRD(int width, float startX, float startY, float birdSpeed, int direct);
    void Move() override;
    void draw(sf::RenderWindow& window) override;
};

#endif