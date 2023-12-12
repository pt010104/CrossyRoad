#ifndef CBIRD_H
#define CBIRD_H

#include "CANIMAL.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include "TextureManager.h"
class CBIRD : public CANIMAL {
private:
    float speed;
    int direction;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect rectSourceSprite;

    std::unordered_map<std::string, Frame> frames;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation; 
    float animationSpeed; 
    float frameTime; 
    size_t currentFrameIndex; 
    int numFrames; 
public:
    CBIRD();
    CBIRD(int width, float startX, float startY, float birdSpeed);
    void Move() override;
    void draw(sf::RenderWindow& window) override;
    float getX() {return mX;}
    void UpdateFrame(float deltaTime);
    void UpdateAnimation(const std::string& direction);

};

#endif