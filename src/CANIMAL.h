#ifndef CANIMAL_H
#define CANIMAL_H

class CANIMAL {
protected:
    int windowWidth = 1000;
public:
    int mX, mY;
    virtual void Move() = 0;
};

#endif