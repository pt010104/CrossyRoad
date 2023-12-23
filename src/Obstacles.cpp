#include "Obstacles.h"
#include <iostream>
#include "TextureManager.h"

Obstacles::Obstacles()
{}
Obstacles::Obstacles(int width,float startX, float startY,std::string tile): windowWidth(width), mX(startX),mY(startY),typeTile(tile)
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
            rectSourceSprite = sf::IntRect(
                frames[typeTile].x,
                frames[typeTile].y,
                frames[typeTile].width,
                frames[typeTile].height
            );    
            sprite.setScale(133*2/sprite.getGlobalBounds().width,133/sprite.getGlobalBounds().height);
}
void Obstacles::draw(sf::RenderWindow& window) {
        this->sprite.setTextureRect(rectSourceSprite);
        sprite.setPosition(mX,mY);
        window.draw(sprite);
}
sf::FloatRect Obstacles::get_GlobalBounds() const {
    return this->sprite.getGlobalBounds();
}