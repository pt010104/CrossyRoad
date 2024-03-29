#include "CVEHICLE.h"

// CVEHICLE.cpp
#include <iostream>
#include "CVEHICLE.h"

CVEHICLE::CVEHICLE() : windowWidth(1000), mX(0), mY(0) {}
CVEHICLE::CVEHICLE(int width, float startX, float startY, std::string name)
    : windowWidth(width), mX(startX), mY(startY), currentFrameIndex(0), frameTime(0.0f),animationSpeed(0.13f), name(name)
{
    indexSecond=-100;
}
void CVEHICLE::UpdateFrame(float deltaTime) {
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

void CVEHICLE::UpdateAnimation(const std::string& direction) {
    if (this->currentAnimation != direction) {
        this->currentAnimation = direction;
        this->currentFrameIndex = 0; 
        this->frameTime = 0; 
        Frame& newFrame = this->animations[direction].frames[currentFrameIndex];
        this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
        this->sprite.setTextureRect(rectSourceSprite);
    }
}
void CVEHICLE::draw(sf::RenderWindow& window) {
    sprite.setPosition(mX,mY);
    window.draw(sprite);

}
float CVEHICLE::getX() {
    return this->mX;
}

sf::FloatRect CVEHICLE::get_GlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

sf::Vector2f CVEHICLE::get_Position() {
    return this->sprite.getPosition();
}

float CVEHICLE::getRadius() const {
    return this->radius;
}
void CVEHICLE::setIndexSecond(int index){
    indexSecond = index;
}
std::string CVEHICLE::serialize(){//
    return name + " " +"\n" + std::to_string(mX) + " " + std::to_string(mY) +" "+ std::to_string(speed) + " " + std::to_string(direction);
}