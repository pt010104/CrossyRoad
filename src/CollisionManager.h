#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "CPEOPLE.h"
#include "CANIMAL.h"

class CollisionManager {
public:
    static bool checkCollisionAnimal( CPEOPLE& people, CANIMAL& animal);
    static bool checkCollisionObstacles( CPEOPLE& people, CANIMAL& animal);

};

#endif 