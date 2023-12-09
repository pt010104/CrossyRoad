#include "CBIRD.h"
CBIRD::CBIRD(int width, float startX, float startY, float birdSpeed)
        : CANIMAL(width), speed(birdSpeed), direction(1) 
{
        mX = startX;
        mY = startY;
        birdShape = sf::RectangleShape(sf::Vector2f(20.0f, 10.0f)); 
        birdShape.setPosition(mX, mY);
        birdShape.setFillColor(sf::Color::Yellow); // birds color
}
void CBIRD::Move() {
    if (mX >= windowWidth) {
        direction = -1;
    } else if (mX <= 0) {
        direction = 1;
    }
    mX += speed * direction;
}
void CBIRD::draw(sf::RenderWindow& window) {
    birdShape.setPosition(mX, mY);    
    window.draw(birdShape);
}