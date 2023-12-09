#include "CPEOPLE.h"
#include <iostream>
CPEOPLE::CPEOPLE() : mState(true) {
    mX = windowWidth/2;
    mY = windowHeight-50;
    rectangle.setSize(sf::Vector2f(50.0f, 50.0f)); 
    rectangle.setFillColor(sf::Color::Red); 
    rectangle.setPosition(static_cast<float>(mX), static_cast<float>(mY));
}

CPEOPLE::CPEOPLE(int startX, int startY) : mX(startX), mY(startY), mState(true) {
    rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
    rectangle.setFillColor(sf::Color::Red); 
    rectangle.setPosition(static_cast<float>(mX), static_cast<float>(mY));
}

void CPEOPLE::Up() {
    if (mY > 0) {
        mY -= 10;
        rectangle.move(0, -10);
    }
}

void CPEOPLE::Left() {
    if (mX > 0) {
        mX -= 10;
        rectangle.move(-10, 0);
    }
}

void CPEOPLE::Right() {
    if (mX < windowWidth - rectangle.getSize().x) {
        mX += 10;
        rectangle.move(10, 0);
    }
}

void CPEOPLE::Down() {
    if (mY < windowHeight - rectangle.getSize().y) {
        mY += 10;
        rectangle.move(0, 10);
    }
}
void CPEOPLE::draw(sf::RenderWindow& window) {
    rectangle.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    window.draw(rectangle);
}