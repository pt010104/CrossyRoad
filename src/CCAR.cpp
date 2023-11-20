#include "CCAR.h"

void CCAR::Move(int dx, int dy) {
    // Change the truck's position to simulate movement
    // If the truck reaches the end of the screen, reverse its direction
    if (mX + dx >= windowWidth) {
        direction = -1;
    } else if (mX + dx <= 0) {
        direction = 1;
    }
    mX += speed * direction;
}