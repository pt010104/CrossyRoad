#ifndef Map_H
#define Map_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include <random>
class Map{
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

    float frameTime;
    float animationSpeed;
public:
    Map();
    Map(int width, float startY,std::string tile);
    void draw(sf::RenderWindow& window);
};

#endif