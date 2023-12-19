#ifndef CANIMAL_H
#define CANIMAL_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include "TextureManager.h"

class CANIMAL {
protected:

    float mX, mY;
    float radius;
    int windowWidth;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;
    std::unordered_map<std::string, Animation> animations;
    std::unordered_map<std::string, Frame> frames;
    std::string currentAnimation;
    int currentFrameIndex;
    float frameTime;
    float animationSpeed;

public:
    CANIMAL();
    CANIMAL(int width, float startX, float startY);
    virtual void Move()  = 0;
    void UpdateFrame(float deltaTime);
    void UpdateAnimation(const std::string& direction);
    virtual void draw(sf::RenderWindow& window);
    float getX() { return this->mX; }
    sf::FloatRect get_GlobalBounds() const {
        return this->sprite.getGlobalBounds();
    }
    sf::Vector2f get_Position() const{
            return sf::Vector2f(this->sprite.getGlobalBounds().width,this->sprite.getGlobalBounds().height);
    }
    float getRadius() const {
        return this->radius;
    }
    virtual ~CANIMAL() = default; 
};

#endif // CANIMAL_H