#include "CDINOSAUR.h"
#include <iostream>
CDINOSAUR::CDINOSAUR()
{}
CDINOSAUR::CDINOSAUR(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY), speed(birdSpeed), direction(direct)
{
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Animal/Dinausor.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Animal/Dinausor.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Animal/Dinausor.png"));
        sprite.setScale(6.0f,6.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
            
}
void CDINOSAUR::Move()  {
    if (mX >= windowWidth) {
        mX = 0;
    } else if (mX+sprite.getGlobalBounds().width <= 0) {
        mX =1000;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}

void CDINOSAUR::draw(sf::RenderWindow& window) {
    sprite.setPosition(mX,mY);
    window.draw(sprite);
}