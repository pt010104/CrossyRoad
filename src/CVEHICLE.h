#ifndef CVEHICLE_H
#define CVEHICLE_H

class CVEHICLE {
public:
    //Constructor
    CVEHICLE();
    CVEHICLE(int itype, int ivelocity, int idirection, int iisDangerouss);

    //Method
    virtual void move(int, int) = 0; //To move object

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
    int type; //get image
    int velocity;   //how fast
    int direction; //0 is left, 1 is right
    int isDangerous; //0 is safe, 1 is dangerous
    int mX, mY; //position
};

#endif