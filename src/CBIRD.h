#ifndef CBIRD_H
#define CBIRD_H

#include "CANIMAL.h"

class CBIRD : public CANIMAL {
private:
    float speed;
    int direction;
    sf::RectangleShape birdShape;
public:
    CBIRD(int width, float startX, float startY, float birdSpeed);
    void Move() override;
    void draw(sf::RenderWindow& window) override;
    float getX() {return mX;}
};

#endif