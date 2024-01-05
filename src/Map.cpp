#include "Map.h"
#include <iostream>
#include "TextureManager.h"

Map::Map()
{}
Map::Map(int width, float startY,std::string tile): windowWidth(width), mY(startY),typeTile(tile)
{
            numFrames = 6;
            SpriteLoader loader;
            if (!loader.LoadTexture("Assets/Map/Dungeon.png", texture)) {
                std::cerr<<"Failed to load texture";
            }
            if (!loader.LoadAnimations("Assets/Map/Dungeon.json", frames, animations, numFrames)) {
                std::cerr<<"Failed to load Json Map";
            }
            sprite.setTexture(TextureManager::GetTexture("Assets/Map/Dungeon.png"));
            sprite.setScale(16.625f,16.625f);
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, numFrames - 1);
            int numTileInLane = 8;
            for (size_t i = 0; i<numTileInLane; ++i) {
                int indexFrame = dist(mt);
                orderFrame.push_back(indexFrame);
            }

        
}
void Map::draw(sf::RenderWindow& window) {
    for (size_t x = 0; x < orderFrame.size(); ++x) {
                int frameIndex = orderFrame[x];
                Frame& newFrame = this->animations[typeTile].frames[frameIndex];
                this->rectSourceSprite = sf::IntRect(newFrame.x, newFrame.y, newFrame.width, newFrame.height);
                this->sprite.setTextureRect(rectSourceSprite);
                sprite.setPosition(x * 133,mY);
                window.draw(sprite);
    }
}