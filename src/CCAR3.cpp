#include "CCAR3.h"
#include <iostream>
CCAR3::CCAR3()
{}
CCAR3::CCAR3(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"cars3")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 2;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Vehicle/Car3.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Vehicle/Car3.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Car";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Vehicle/Car3.png"));
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
void CCAR3::Move()   {
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