#include "CBIRD.h"
#include <iostream>

CBIRD::CBIRD()
{}
CBIRD::CBIRD(int width, float startX, float startY, float birdSpeed, int direct)
    : CANIMAL(width, startX, startY,"birds")
{
        speed = birdSpeed;
        direction = direct;
        mX = startX;
        mY = startY;
        numFrames = 4;
        SpriteLoader loader;
        
        if (!loader.LoadTexture("Assets/Animal/Bird.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Animal/Bird.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Animal/Bird.png"));
        sprite.setScale(7.0f,7.0f);
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

