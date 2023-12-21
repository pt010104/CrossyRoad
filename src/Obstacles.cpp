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
            sprite.setScale(133*2/sprite.getGlobalBounds().width,133/sprite.getGlobalBounds().height);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, numFrames - 1);
            std::uniform_int_distribution<int> dist2(2, 4);
            int numObsInLane = dist2(gen);
            for (int i =0; i<numObsInLane; ++i) {
                int indexFrame = dist(gen);
                orderFrame.push_back(indexFrame);
            }
            std::uniform_int_distribution<int> dist_x(1, 8);
            for (int i = 0; i<orderFrame.size();i++)
            {
                int randomX = dist_x(gen);
                coordX.push_back(randomX);
            }

            

        
}
void Obstacles::draw(sf::RenderWindow& window) {
        for (size_t i = 0; i < orderFrame.size(); ++i) {
            int x = coordX[i]*133;
            int frameIndex = orderFrame[i];
            Frame& newFrame = this->animations[typeTile].frames[frameIndex];
            this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
            this->sprite.setTextureRect(rectSourceSprite);
            sprite.setPosition(x,mY);
            window.draw(sprite);
        }
}