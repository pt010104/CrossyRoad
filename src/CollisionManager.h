#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "CPEOPLE.h"
#include "CANIMAL.h"
#include "Obstacles.h"
<<<<<<< HEAD
class CollisionManager {
public:
    static bool checkCollisionAnimal( CPEOPLE& people, CANIMAL& animal);
    static bool checkCollisionObstacles( CPEOPLE& people, Obstacles& animal);
=======

class CollisionManager {
public:
    static bool checkCollisionAnimal( CPEOPLE& people, CANIMAL& animal);
    static bool checkCollisionObstacles( CPEOPLE& people, CANIMAL& animal);
    static bool checkCollision(CPEOPLE& people, Obstacles& obstacle);
>>>>>>> d8b7c20b3861c15c6ddb3b49996f877fb0ccf072
};

#endif 