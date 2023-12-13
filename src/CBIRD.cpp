#include "CBIRD.h"
#include <iostream>
CBIRD::CBIRD()
{}
CBIRD::CBIRD(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY), speed(birdSpeed), direction(direct)
{
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Bird.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Bird.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Bird.png"));
        sprite.setScale(8.0f,8.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
            
}
void CBIRD::Move() {
    if (mX >= windowWidth) {
        mX = 0;
    } else if (mX+sprite.getGlobalBounds().width <= 0) {
        mX =1000;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}

void CBIRD::draw(sf::RenderWindow& window) {
    sprite.setPosition(mX,mY);
    window.draw(sprite);
}