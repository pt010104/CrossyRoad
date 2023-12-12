#include "CBIRD.h"
#include <iostream>
CBIRD::CBIRD()
{}
CBIRD::CBIRD(int width, float startX, float startY, float birdSpeed)
        : CANIMAL(width), speed(birdSpeed), direction(1) 
{
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        std::cout<<"load here";

        if (!loader.LoadTexture("Assets/Bird.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/bird.json", frames, animations, numFrames)) {
        }
        sprite.setTexture(texture);
        sprite.setScale(4.0f, 4.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setTextureRect(rectSourceSprite);
            
}
void CBIRD::Move() {
    if (mX >= windowWidth) {
        mX = 5;
    } else if (mX <= 0) {
        mX = 870;
    }
    mX += speed * direction;
}
void CBIRD::draw(sf::RenderWindow& window) {
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    window.draw(sprite);
}