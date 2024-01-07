#include "CCAR2.h"
#include <iostream>
CCAR2::CCAR2()
{}
CCAR2::CCAR2(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"cars2")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 3;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Vehicle/Car2.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Vehicle/Car2.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Car";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Vehicle/Car2.png"));
        sprite.setScale(1.0f,1.0);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
        radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;


            
}
void CCAR2::Move()   {
    if (direction==-1)
        sprite.setScale(-1.0f,1.0);
    if (mX >= windowWidth) {
        mX = 2;
    } else if (mX+sprite.getGlobalBounds().width <= 0) {
        mX =955;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}