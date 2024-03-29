#ifndef Obstacles_H
#define Obstacles_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include <random>
class Obstacles{
private:
    float mY;
    float mX;
    float radius;
    int numFrames; 
    int windowWidth;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;
    std::unordered_map<std::string, Animation> animations;
    std::unordered_map<std::string, Frame> frames;
    
    float frameTime;
    float animationSpeed;
public:
    std::string typeTile;
    Obstacles();
    Obstacles(int width,float startX, float startY,std::string tile);
    void draw(sf::RenderWindow& window);
    sf::FloatRect get_GlobalBounds() const;
    sf::Vector2f get_Position() const;
};

#endif