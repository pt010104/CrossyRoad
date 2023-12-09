#ifndef CANIMAL_H
#define CANIMAL_H
#include <SFML/Graphics.hpp>

class CANIMAL {
protected:
    float mX, mY;
    int windowWidth;
public:
    CANIMAL(int width) : windowWidth(width), mX(0), mY(0) {}
    virtual void Move() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~CANIMAL() = default; 
};

#endif