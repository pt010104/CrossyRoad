#include "CPEOPLE.h"
#include <iostream>


CPEOPLE::CPEOPLE() : mState(true), currentFrame(0),currentRow(0) {
    mX = windowWidth / 2;
    mY = 50;
    frameWidth = 326;
    frameHeight = 449;
    frameCount = 4;
    if (!texture.loadFromFile("Assets\\People.png")) {
        std::cerr << "Error loading texture" << std::endl;
    }
    else{
        sprite.setTexture(texture);
        sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
        rectSourceSprite = sf::IntRect(25,100, frameWidth, frameHeight);
        sprite.setTextureRect(rectSourceSprite);
    }
}

CPEOPLE::CPEOPLE(int startX, int startY) : mX(startX), mY(startY), mState(true), currentFrame(0), currentRow(0) {
    if (!texture.loadFromFile("Assets\\People.png")) {
        std::cerr << "Error loading texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    rectSourceSprite = sf::IntRect(0, 0, frameWidth, frameHeight);
}

void CPEOPLE::Up() {
    if (mY > 0) {
        mY -= 10;
        currentRow = 1; // Assuming second row is for moving up
        UpdateFrame();
    }
}

void CPEOPLE::Down() {
    if (mY < windowHeight - rectSourceSprite.height) {
        mY += 10;
        currentRow = 0; 
        UpdateFrame();
    }
}

void CPEOPLE::Left() {
    if (mX > 0) {
        mX -= 10;
        currentRow = 2; // Assuming third row is for moving left
        UpdateFrame();
    }
}

void CPEOPLE::Right() {
    if (mX < windowWidth - rectSourceSprite.width) {
        mX += 10;
        currentRow = 3; // Assuming fourth row is for moving right
        UpdateFrame();
    }
}

void CPEOPLE::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void CPEOPLE::UpdateFrame() {
    rectSourceSprite.left = 25 + currentFrame * (frameWidth+75);
    rectSourceSprite.top = 100 + currentRow * (frameHeight+197);
    sprite.setTextureRect(rectSourceSprite);
    sprite.setPosition(static_cast<float>(mX), static_cast<float>(mY));
    currentFrame = (currentFrame + 1) % frameCount;
}
