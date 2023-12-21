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
    float radius;
    int numFrames; 
    std::string typeTile;

    int windowWidth;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;
    std::unordered_map<std::string, Animation> animations;
    std::unordered_map<std::string, Frame> frames;
    std::vector<int>orderFrame;
    std::vector<int>coordX;

    float frameTime;
    float animationSpeed;
public:
    Obstacles();
    Obstacles(int width, float startY,std::string tile);
    void draw(sf::RenderWindow& window);
};

#endif