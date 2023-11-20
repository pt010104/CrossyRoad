#include "CPEOPLE.h"

CPEOPLE::CPEOPLE() {
}

CPEOPLE::CPEOPLE(int startX, int startY) : mX(startX), mY(startY), mState(true) {
    // state to alive (true)
}

void CPEOPLE::Up() {
    mY--;
}

void CPEOPLE::Left() {
    mX--; 
}

void CPEOPLE::Right() {
    mX++; 
}
void CPEOPLE::Down() {
    mY++; 
}

