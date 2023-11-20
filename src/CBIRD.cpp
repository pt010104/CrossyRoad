#include "CBIRD.h"

void CBIRD::Move() {
    // Change the bird's position to simulate movement
    // If the bird reaches the end of the screen, reverse its direction
    if (mX >= windowWidth) {
        direction = -1;
    } else if (mX <= 0) {
        direction = 1;
    }
    mX += speed * direction;
}
