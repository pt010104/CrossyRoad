#ifndef CANIMAL_H
#define CANIMAL_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include "TextureManager.h"
#include <iostream>

class CANIMAL {
protected:

    float mX, mY;
    float speed;
    
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
    int indexSecond=-100;
    std::string name;
public:
    int direction;
    CANIMAL();
    CANIMAL(int width, float startX, float startY,std::string name);
    virtual void Move()  = 0;
    void UpdateFrame(float deltaTime);
    void UpdateAnimation(const std::string& direction);
    virtual void draw(sf::RenderWindow& window);
    float getX();
    sf::FloatRect get_GlobalBounds() const;
    sf::Vector2f get_Position();
    void setIndexSecond(int index);
    float getRadius() const;
    std::string serialize();
    virtual ~CANIMAL() = default; 
};

#endif // CANIMAL_H