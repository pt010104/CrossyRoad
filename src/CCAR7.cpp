#include "CCAR7.h"
#include <iostream>
CCAR7::CCAR7()
{}
CCAR7::CCAR7(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"cars7")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 8;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Vehicle/Car7.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Vehicle/Car7.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Car";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Vehicle/Car7.png"));
        sprite.setScale(1.75f,1.75);
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
