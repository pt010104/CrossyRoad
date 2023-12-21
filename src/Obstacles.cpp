#include "Obstacles.h"
#include <iostream>
#include "TextureManager.h"

Obstacles::Obstacles()
{}
Obstacles::Obstacles(int width, float startY,std::string tile): windowWidth(width), mY(startY),typeTile(tile)
{
            numFrames = 7;
            SpriteLoader loader;
            if (!loader.LoadTexture("Assets/Map/Obstacles.png", texture)) {
                std::cerr<<"Failed to load texture";
            }
            if (!loader.LoadAnimations("Assets/Map/Obstacles.json", frames, animations, numFrames)) {
                std::cerr<<"Failed to load Json Map";
            }
            sprite.setTexture(TextureManager::GetTexture("Assets/Map/Obstacles.png"));
            sprite.setScale(16.625f,16.625f);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, numFrames - 1);
            std::uniform_int_distribution<int> dist2(0, 3);
            int numObsInLane = dist2(gen);
            for (int i = 1; i<=numObsInLane; ++i) {
                int indexFrame = dist(gen);
                orderFrame.push_back(indexFrame);
            }

        
}
void Obstacles::draw(sf::RenderWindow& window) {
        for (size_t x = 0; x < orderFrame.size(); ++x) {
            int frameIndex = orderFrame[x];
            Frame& newFrame = this->animations[typeTile].frames[frameIndex];
            this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            this->sprite.setTextureRect(rectSourceSprite);
            sprite.setPosition(x * 133,mY);
            window.draw(sprite);
        }
}