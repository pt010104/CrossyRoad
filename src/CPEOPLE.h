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
    float radius;
    bool nearObs;

    bool canMoveUp;
    bool canMoveDown;
    bool canMoveLeft;
    bool canMoveRight;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect rectSourceSprite;
    int spriteWidth;
    int spriteHeight;

    std::unordered_map<std::string, Frame> frames;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation; 
    float animationSpeed; 
    float frameTime; 
    size_t currentFrameIndex; 
    int numFrames; //num frames per row

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
    int getX(){return mX;};
    sf::FloatRect get_GlobalBounds() const {
        return sprite.getGlobalBounds();
    }
    sf::Vector2f get_Position() const{
        return sprite.getPosition();
    }
    float getRadius() const {
        return radius;
    }
    bool getState() const { return mState; }
    bool getNearObs();
    void setNearobs(bool near);
    void Died();
    void reset();

    void setCanMoveUp(bool value) { canMoveUp = value; }
    void setCanMoveDown(bool value) { canMoveDown = value; }
    void setCanMoveLeft(bool value) { canMoveLeft = value; }
    void setCanMoveRight(bool value) { canMoveRight = value; }

    bool getCanMoveUp() const { return canMoveUp; }
    bool getCanMoveDown() const { return canMoveDown; }
    bool getCanMoveLeft() const { return canMoveLeft; }
    bool getCanMoveRight() const { return canMoveRight; }
};

#endif