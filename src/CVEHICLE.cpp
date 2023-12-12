// #include "CVEHICLE.h"


//Constructor
CVEHICLE::CVEHICLE() : type(-1), velocity(-1), direction(-1), isDangerous(-1), mX(0), mY(0){} //-1 is error code
CVEHICLE::CVEHICLE(int itype, int ivelocity, int idirection, int iisDangerous) :
            type(itype), velocity(ivelocity), direction(idirection), isDangerous(iisDangerous), mX(0), mY(0){}

//Method
//Get method
int CVEHICLE::getDirection() {
    return direction;
}

int CVEHICLE::getVelocity() {
    return velocity;
}

int CVEHICLE::getIsDangerous() {
    return isDangerous;
};

int CVEHICLE::getMX() {
    return mX;
};

int CVEHICLE::getMY() {
    return mY;
};

//Set method
void CVEHICLE::setMX(int x) {
    mX = x;
}

void CVEHICLE::setMY(int y) {
    mY = y;
}