// CANIMAL.cpp
#include <iostream>
#include "CANIMAL.h"

CANIMAL::CANIMAL() : windowWidth(1000), mX(0), mY(0) {}
CANIMAL::CANIMAL(int width, float startX, float startY, std::string name)
    : windowWidth(width), mX(startX), mY(startY), currentFrameIndex(0), frameTime(0.0f),animationSpeed(0.13f), name(name)
{
    timeAppear = 0;
    indexSecond=-100;
    time = 0;
}
void CANIMAL::UpdateFrame(float deltaTime) {
    //std::cout<<"Update frame test";
    this->frameTime += deltaTime;
    if (this->frameTime >= this->animationSpeed) {
        this->frameTime = 0.f; 
        if (animations.find(this->currentAnimation) != animations.end()) { //check
            this->currentFrameIndex = (this->currentFrameIndex + 1) % this->animations[this->currentAnimation].frames.size();
            Frame& newFrame = this->animations[currentAnimation].frames[currentFrameIndex];
            this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            this->sprite.setTextureRect(rectSourceSprite);
        }
    }
}

void CANIMAL::UpdateAnimation(const std::string& direction) {
    if (this->currentAnimation != direction) {
        this->currentAnimation = direction;
        this->currentFrameIndex = 0; 
        this->frameTime = 0; 
        Frame& newFrame = this->animations[direction].frames[currentFrameIndex];
        this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
        this->sprite.setTextureRect(rectSourceSprite);
    }
}
void CANIMAL::Move()   {
    if (direction==-1)
        sprite.setScale(-scale.x, scale.y);

    if (mX >= windowWidth+6) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(3.0, 6.0);
        float randomTime = dis(gen);
        if (realTimeClock.getElapsedTime().asSeconds() >= time+ timeAppear)
        {
            mX = 0;
            time = realTimeClock.getElapsedTime().asSeconds() + randomTime ;
        }
    }
    else if (mX+sprite.getGlobalBounds().width < 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(3.0, 6.0);
        float randomTime = dis(gen);
        if (realTimeClock.getElapsedTime().asSeconds() >= time)
        {
            mX = 1005;
            time = realTimeClock.getElapsedTime().asSeconds() + randomTime + timeAppear;
        }
    }
    if (realTimeClock.getElapsedTime().asSeconds() >= timeAppear)
    {
        mX += speed * direction;
    }
    UpdateAnimation("right");
}
void CANIMAL::draw(sf::RenderWindow& window) {
    sprite.setPosition(mX,mY);
    window.draw(sprite);

}
float CANIMAL::getX() {
    return this->mX;
}

sf::FloatRect CANIMAL::get_GlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

sf::Vector2f CANIMAL::get_Position() {
    return this->sprite.getPosition();
}

float CANIMAL::getRadius() const {
    return this->radius;
}
void CANIMAL::setIndexSecond(int index){
    indexSecond = index;
}
std::string CANIMAL::serialize(){//
    return name + " " +"\n" + std::to_string(mX) + " " + std::to_string(mY) +" "+ std::to_string(speed) + " " + std::to_string(direction) + " " + std::to_string(timeAppear);
}