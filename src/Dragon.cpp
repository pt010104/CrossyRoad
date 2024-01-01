#include "Dragon.h"
#include <iostream>
Dragon::Dragon():windowWidth(1000), windowHeight(800), animationSpeed(0.2f), frameTime(0.f), currentFrameIndex(0)
{
        mY = 0;
        numFrames = 8;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Traffic Light/Dragon.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Traffic Light/Dragon.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json dragon";
        }
        sprite.setTexture(texture);
        sprite.setScale(4.5f,4.5f);
        rectSourceSprite = sf::IntRect(
            frames["right_1"].x,
            frames["right_1"].y,
            frames["right_1"].width,
            frames["right_1"].height
        );
        sprite.setTextureRect(rectSourceSprite);
        mX = 50; 
        sprite.setPosition(mX, mY);  
        currentAnimation = "right";
        state = "disap";
}
void Dragon::appear(float deltaTime){
    sprite.setPosition(mX, mY);   
    timeDelay = deltaTime;
    if (state != "disap")
    {
        if(state == "appear")
        {
            UpdateAnimation("right");
            state = "right";
        }
        else
        if(timeDelay >= 2.0f && state == "right"){
            UpdateAnimation("fire");
            timeDelay = 0;
            state = "fire";
        }
        else
        if(timeDelay >= 7.0f && state =="fire"){
            UpdateAnimation("right");
            timeDelay = 0;
            state = "explode";
        }
        else
        if(timeDelay >= 2.0f && state == "explode"){
            UpdateAnimation("appear");
            timeDelay = 0;
        }
    }

}
void Dragon::UpdateFrame(float deltaTime) {
        frameTime += deltaTime;

        if (frameTime >= animationSpeed) {
            frameTime = 0.f; 
            currentFrameIndex = (currentFrameIndex + 1) % animations[currentAnimation].frames.size();
            Frame& newFrame = animations[currentAnimation].frames[currentFrameIndex];
            rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            sprite.setTextureRect(rectSourceSprite);
        }
        if(state == "explode" && currentFrameIndex == 2)
            state = "disap";
}

void Dragon::UpdateAnimation(const std::string& direction) {
    if (currentAnimation != direction) {
        currentAnimation = direction;
        currentFrameIndex = 0; 
        frameTime = 0; 
        Frame& newFrame = animations[direction].frames[currentFrameIndex];
        rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
        sprite.setTextureRect(rectSourceSprite);
    }
}

void Dragon::draw(sf::RenderWindow& window) {
    sprite.setPosition(mX,mY);
    window.draw(sprite);
}
void Dragon::reset(){    
    mY = 0;
    numFrames = 8;
    SpriteLoader loader;
    if (!loader.LoadTexture("Assets/Traffic Light/Dragon.png", texture)) {
        std::cerr<<"Failed to load texture";
    }
    if (!loader.LoadAnimations("Assets/Traffic Light/Dragon.json", frames, animations, numFrames)) {
        std::cerr<<"Failed to load Json dragon";
    }
    sprite.setTexture(texture);
    sprite.setScale(4.5f,4.5f);
    rectSourceSprite = sf::IntRect(
        frames["right_1"].x,
        frames["right_1"].y,
        frames["right_1"].width,
        frames["right_1"].height
    );
    sprite.setTextureRect(rectSourceSprite);
    mX = 50; 
    sprite.setPosition(mX, mY);  
    currentAnimation = "right";
    state = "disap";
}