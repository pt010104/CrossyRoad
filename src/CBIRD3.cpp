#include "CBIRD3.h"
#include <iostream>
CBIRD3::CBIRD3()
{}
CBIRD3::CBIRD3(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"birds3")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 8;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Animal/Bird3.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Animal/Bird3.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Animal/Bird3.png"));
        sprite.setScale(6.0f,6.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setTextureRect(rectSourceSprite);
        sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
        radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;


            
}
void CBIRD3::Move()   {
    if (direction==-1)
        sprite.setScale(-5.0f, 5.0f);
    if (mX >= windowWidth) {
        mX = 2;
    } else if (mX+sprite.getGlobalBounds().width <= 0) {
        mX =955;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}