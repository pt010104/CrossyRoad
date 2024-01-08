#include "CCAR6.h"
#include <iostream>
CCAR6::CCAR6()
{}
CCAR6::CCAR6(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"cars6")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Vehicle/Car6.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Vehicle/Car6.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Car";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Vehicle/Car6.png"));
        sprite.setScale(4.5f,4.5);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setTextureRect(rectSourceSprite);
        sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
        radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;
        scale = sprite.getScale();
}
