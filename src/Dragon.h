#ifndef Dragon_H
#define Dragon_H
#include "CANIMAL.h"

class Dragon {
private:
    int windowWidth = 1000;
    int windowHeight = 800;
    
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
    float timeDelay;
    size_t currentFrameIndex; 
    int numFrames; //num frames per row
public:
    float mX, mY;
    Dragon();
    std::string state;

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
    void appear(float deltaTime);
    void Died();
    void reset();
};

#endif