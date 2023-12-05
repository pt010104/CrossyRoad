#include "CItem.h"

//Constructor
CItem::CItem() : type("Null"), velocity(-1), direction(-1), isDangerous(-1), mX(0), mY(0){} //-1 is error code
CItem::CItem(std::string itype, int ivelocity, int idirection, int iisDangerous) :
            type(itype), velocity(ivelocity), direction(idirection), isDangerous(iisDangerous), mX(0), mY(0){}

//Method
//Get method
int CItem::getDirection() {
    return direction;
}

int CItem::getVelocity() {
    return velocity;
}

int CItem::getIsDangerous() {
    return isDangerous;
};

int CItem::getMX() {
    return mX;
};

int CItem::getMY() {
    return mY;
};

//Set method
void CItem::setMX(int x) {
    mX = x;
}

void CItem::setMY(int y) {
    mY = y;
}