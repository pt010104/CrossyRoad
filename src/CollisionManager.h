#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "CPEOPLE.h"
#include "CANIMAL.h"

class CollisionManager {
public:
    static bool checkCollision( CPEOPLE& people, CANIMAL& animal);
};

#endif 