#pragma once
#include <string>

class CItem{
public:
    //Constructor
    CItem();
    CItem(std::string itype, int ivelocity, int idirection, int iisDangerouss);

    //Method
    virtual void Conmove(int, int) = 0; //To move object

protected:
    //Getting information
    int getDirection();
    int getIsDangerous();
    int getMX();
    int getMY();
    int getVelocity();

    //Set information
    void setMX(int x);
    void setMY(int y);

private:
    std::string type; //get image
    int velocity;   //how fast
    int direction; //0 is left, 1 is right
    int isDangerous; //0 is safe, 1 is dangerous
    int mX, mY; //position
};