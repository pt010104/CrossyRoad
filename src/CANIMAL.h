#ifndef CANIMAL_H
#define CANIMAL_H

class CANIMAL {
protected:
    sf::Sprite sprite;
    int windowWidth = 1000;
public:

    int mX, mY;
    int windowWidth;
    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
    virtual void Move() = 0;
};

#endif