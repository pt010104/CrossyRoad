#ifndef CVEHICLE_H
#define CVEHICLE_H

class CVEHICLE {
protected:
    int mX, mY;
    int windowWidth=1000;
public:
    virtual void Move(int dx, int dy) = 0; 
};

#endif