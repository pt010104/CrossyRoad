#include "CDINOSAUR.h"
#include <iostream>
CDINOSAUR::CDINOSAUR()
{}
CDINOSAUR::CDINOSAUR(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"dinosaurs")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Animal/Dinosaur.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Animal/Dinosaur.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Animal/Dinosaur.png"));
        sprite.setScale(7.0f,7.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
        radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;
            
}
void CDINOSAUR::Move()  {
    if (direction==-1)
        sprite.setScale(-7.0f, 7.0f);
    if (mX >= windowWidth) {
        mX = 2;
    } else if (mX+sprite.getGlobalBounds().width <= 0) {
        mX =955;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}
