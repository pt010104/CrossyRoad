#include "CTRUCK.h"

void CTRUCK::Move(int dx, int dy) {
    if (mX + dx >= windowWidth) {
        direction = -1;
    } else if (mX + dx <= 0) {
        direction = 1;
    }
    mX += speed * direction;
}