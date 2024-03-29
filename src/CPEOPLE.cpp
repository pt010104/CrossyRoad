#include "CPEOPLE.h"
#include <iostream>
CPEOPLE::CPEOPLE() : mState(true), windowWidth(1000), windowHeight(800), currentAnimation("down"), animationSpeed(0.2f), 
    frameTime(0.f), currentFrameIndex(0)
{
    numFrames = 5;
    nearObs = false;
    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/Player/Player_Chicken.png", texture)) {
    }
    if (!loader.LoadAnimations("Assets/Player/Player_Chicken.json", frames, animations, numFrames)) {
    }
    sprite.setTexture(texture);
    sprite.setScale(4.5f, 4.5f);
    rectSourceSprite = sf::IntRect(
        frames["down_1"].x,
        frames["down_1"].y,
        frames["down_1"].width,
        frames["down_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
    mX = windowWidth/2-50;
    mY = windowHeight-sprite.getGlobalBounds().height; 
    spriteWidth = sprite.getGlobalBounds().width;
    spriteHeight = sprite.getGlobalBounds().height;
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;
    speed = 3;

}

CPEOPLE::CPEOPLE(int startX, int startY) : CPEOPLE() {
    mX = startX;
    mY = startY;
    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/Player/Player_Chicken.png", texture)) {
    }
    if (!loader.LoadAnimations("Assets/Player/Player_Chicken.json", frames, animations,numFrames)) {
    }
    sprite.setTexture(texture);
    sprite.setScale(4.5f, 4.5f);

    rectSourceSprite = sf::IntRect(
        frames["down_1"].x,
        frames["down_1"].y,
        frames["down_1"].width,
        frames["down_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
    spriteWidth = sprite.getGlobalBounds().width;
    spriteHeight = sprite.getGlobalBounds().height;
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;
    speed = 3;
}

void CPEOPLE::Up() {
    // if(!nearObs)
        mY = mY - speed;
    UpdateAnimation("up");
}

void CPEOPLE::Left() {
    // if(!nearObs)
        mX = std::max(0 + spriteWidth, mX - speed);
    UpdateAnimation("left");
}

void CPEOPLE::Right() {
    // if(!nearObs)
        mX = std::min(windowWidth - spriteWidth, mX + speed);
    UpdateAnimation("right");
}

void CPEOPLE::Down() {
    // if(!nearObs)
        mY = std::min(windowHeight - spriteHeight, mY + speed);
    UpdateAnimation("down");
}
void CPEOPLE::Died(){
    UpdateAnimation("die");
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
        if (currentAnimation == "die"&&currentFrameIndex == 4)
        {
                    mState=false;
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
    sprite.setPosition(mX,mY);
    window.draw(sprite);
}
bool CPEOPLE::getNearObs(){
    return nearObs;
}
void CPEOPLE::setNearobs(bool near){
    nearObs = near;
}
void CPEOPLE::reset(){
    currentAnimation = "down";
    mState = true;
    nearObs = false;
    
    numFrames = 5;

    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/Player/Player_Chicken.png", texture)) {
    }
    if (!loader.LoadAnimations("Assets/Player/Player_Chicken.json", frames, animations, numFrames)) {
    }
    sprite.setTexture(texture);
    sprite.setScale(4.5f, 4.5f);
    rectSourceSprite = sf::IntRect(
        frames["down_1"].x,
        frames["down_1"].y,
        frames["down_1"].width,
        frames["down_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
    mX = windowWidth/2-50;
    mY = windowHeight-sprite.getGlobalBounds().height-50; 
    spriteWidth = sprite.getGlobalBounds().width;
    spriteHeight = sprite.getGlobalBounds().height;
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    radius = std::min(rectSourceSprite.width, rectSourceSprite.height) / 2.0f * sprite.getScale().x;
    speed = 3;
}

void CPEOPLE::set_Position(int X, int Y){
    mX = X;
    mY = Y;
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
}

void CPEOPLE::finish(){

}