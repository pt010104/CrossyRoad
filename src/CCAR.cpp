#include "CCAR.h"

void CCAR::Move(int dx, int dy) {
    if (mX + dx >= windowWidth) {
        direction = -1;
    } else if (mX + dx <= 0) {
        direction = 1;
    }
    mX += speed * direction;
}