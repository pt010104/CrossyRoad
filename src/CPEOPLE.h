#ifndef CPEOPLE_H
#define CPEOPLE_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"

class CPEOPLE {
private:
    int mX, mY;
    bool mState;
    int windowWidth = 1000;
    int windowHeight = 800;
    
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect rectSourceSprite;

    std::unordered_map<std::string, Frame> frames;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation; 
    float animationSpeed; 
    float frameTime; 
    size_t currentFrameIndex; 

public:
    CPEOPLE();
    CPEOPLE(int startX, int startY);
    void Up();
    void Left();
    void Right();
    void Down();
    void draw(sf::RenderWindow& window); 
    void UpdateFrame(float deltaTime);
    void UpdateAnimation(const std::string& direction);


    bool getState() const { return mState; }
    void setState(bool state) { mState = state; }
};

#endif