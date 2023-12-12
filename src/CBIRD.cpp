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
        if (!loader.LoadTexture("Assets/Bird.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Bird.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Bird";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Bird.png"));
        sprite.setScale(4.0f, 4.0f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
            
}
void CBIRD::Move() {
    if (mX >= windowWidth) {
        mX = 5;
    } else if (mX <= 0) {
        mX = 870;
    }
    mX += speed * direction;
    UpdateAnimation("right");
}


void CBIRD::UpdateFrame(float deltaTime) {
        frameTime += deltaTime;
        if (frameTime >= animationSpeed) {
            frameTime = 0.f; 
            currentFrameIndex = (currentFrameIndex + 1) % animations[currentAnimation].frames.size();
            Frame& newFrame = animations[currentAnimation].frames[currentFrameIndex];
            rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            sprite.setTextureRect(rectSourceSprite);
        }
}

void CBIRD::UpdateAnimation(const std::string& direction) {
    if (currentAnimation != direction) {
        currentAnimation = direction;
        currentFrameIndex = 0; 
        frameTime = 0; 
        Frame& newFrame = animations[direction].frames[currentFrameIndex];
        rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
        sprite.setTextureRect(rectSourceSprite);
    }
}

void CBIRD::draw(sf::RenderWindow& window) {
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    window.draw(sprite);
}