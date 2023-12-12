#include "CPEOPLE.h"
#include <iostream>
CPEOPLE::CPEOPLE() : mState(true), windowWidth(1000), windowHeight(800), currentAnimation("up"), animationSpeed(0.2f), 
    frameTime(0.f), currentFrameIndex(0)
{
    numFrames = 3;

    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/RedChicken.png", texture)) {
    }
    if (!loader.LoadAnimations("Assets/player_chicken.json", frames, animations, numFrames)) {
    }
    sprite.setTexture(texture);
    sprite.setScale(4.0f, 4.0f);
    rectSourceSprite = sf::IntRect(
        frames["up_1"].x,
        frames["up_1"].y,
        frames["up_1"].width,
        frames["up_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
    mX = windowWidth/2-50;
    mY = windowHeight-sprite.getGlobalBounds().height-100; 
    spriteWidth = sprite.getGlobalBounds().width;
    spriteHeight = sprite.getGlobalBounds().height;
}

CPEOPLE::CPEOPLE(int startX, int startY) : CPEOPLE() {
    mX = startX;
    mY = startY;
    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/RedChicken.png", texture)) {
    }
    if (!loader.LoadAnimations("Assets/Frame.json", frames, animations,numFrames)) {
    }
    sprite.setTexture(texture);
    sprite.setScale(4.0f, 4.0f);

    rectSourceSprite = sf::IntRect(
        frames["down_1"].x,
        frames["down_1"].y,
        frames["down_1"].width,
        frames["down_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
}

void CPEOPLE::Up() {
    mY = std::max(0 + spriteHeight, mY - 1);
    UpdateAnimation("up");
}

void CPEOPLE::Left() {
    mX = std::max(0 + spriteWidth, mX - 1);
    UpdateAnimation("left");
}

void CPEOPLE::Right() {
    mX = std::min(windowWidth - spriteWidth, mX + 1);
    UpdateAnimation("right");
}

void CPEOPLE::Down() {
    mY = std::min(windowHeight - spriteHeight, mY + 1);
    UpdateAnimation("down");
}

void CPEOPLE::UpdateFrame(float deltaTime) {
        frameTime += deltaTime;
        if (frameTime >= animationSpeed) {
            frameTime = 0.f; 
            currentFrameIndex = (currentFrameIndex + 1) % animations[currentAnimation].frames.size();
            Frame& newFrame = animations[currentAnimation].frames[currentFrameIndex];
            rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            sprite.setTextureRect(rectSourceSprite);
        }
}

void CPEOPLE::UpdateAnimation(const std::string& direction) {
    if (currentAnimation != direction) {
        currentAnimation = direction;
        currentFrameIndex = 0; 
        frameTime = 0; 
        Frame& newFrame = animations[direction].frames[currentFrameIndex];
        rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
        sprite.setTextureRect(rectSourceSprite);
    }
}

void CPEOPLE::draw(sf::RenderWindow& window) {
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    window.draw(sprite);
}