#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "CPEOPLE.h"
#include "CANIMAL.h"
#include "Obstacles.h"

class CollisionManager {
public:
    static bool checkCollisionAnimal( CPEOPLE& people, CANIMAL& animal);
    static bool checkCollision(CPEOPLE& people, Obstacles& obstacle);
    static bool checkCollisionInDirection(CPEOPLE& people, Obstacles& obs, char direction);
};

#endif 