#ifndef CPEOPLE_H
#define CPEOPLE_H
#include <SFML/Graphics.hpp>

class CPEOPLE {
private:
    int mX, mY;
    bool mState;
    sf::RectangleShape rectangle;
    int windowWidth = 1000;
    int windowHeight = 800;
public:
    CPEOPLE();
    CPEOPLE(int startX, int startY);
    void Up();
    void Left();
    void Right();
    void Down();
    void draw(sf::RenderWindow& window); 
    bool getState() const { return mState; }
    void setState(bool state) { mState = state; }


};

#endif