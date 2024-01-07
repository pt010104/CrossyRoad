#include "CollisionManager.h"
#include <cmath>
bool CollisionManager::checkCollisionAnimal(CPEOPLE& people, CANIMAL& animal) {
    sf::Vector2f posPeople = people.get_Position();
    float widthPeople = people.get_GlobalBounds().width;
    float heightPeople = people.get_GlobalBounds().height;

    sf::Vector2f posAnimal = animal.get_Position();
    float widthAnimal = animal.get_GlobalBounds().width;
    float heightAnimal = animal.get_GlobalBounds().height;

    bool isAbove = posPeople.y + heightPeople <= (posAnimal.y+heightAnimal/2+10);
    if (isAbove) {
        return false;
    }
    bool isBelow = posPeople.y >= (posAnimal.y+heightAnimal/2-10);
    if (isBelow) {
        return false;
    }
    float dx = (posPeople.x - posAnimal.x);
    float dy = (posPeople.y - posAnimal.y);
    float distance = std::sqrt(dx * dx + dy * dy);
    float radius1 = people.getRadius();
    float radius2 = animal.getRadius();
    return distance < (radius1 + radius2);
}
bool CollisionManager::checkCollisionInDirection(CPEOPLE& people, Obstacles& obs, char direction){
    sf::FloatRect peopleBounds = people.get_GlobalBounds();
    sf::FloatRect obstaclesBounds = obs.get_GlobalBounds();

    sf::Vector2f posPeople = people.get_Position();
    sf::Vector2f posObs = obs.get_Position();

    float threshold = 10;

    if(peopleBounds.width == 0 &&peopleBounds.height == 0)
        return false;
    switch (direction) {
        case 'W':
            if (std::abs((posPeople.y) - ((posObs.y) + obstaclesBounds.height)) > threshold)
                return false;
            return peopleBounds.intersects(obstaclesBounds);
        case 'A':
            if (std::abs((posPeople.x) - (posObs.x + obstaclesBounds.width)) > threshold)
                return false;
            if(peopleBounds.intersects(obstaclesBounds)){
                if (std::abs(posPeople.y - (posObs.y + obstaclesBounds.height)) <= 3)
                    return false;
                if (std::abs(posPeople.y + peopleBounds.height - posObs.y) <= 3)
                    return false;
                return true;
            }
            return false;
        case 'S':
            if (std::abs((posPeople.y + peopleBounds.height) - (posObs.y)) > threshold)
                return false;
            return peopleBounds.intersects(obstaclesBounds);
        case 'D':
            if (std::abs((posPeople.x + peopleBounds.width) - (posObs.x)) > threshold)
                return false;
            if (std::abs(posPeople.y - (posObs.y + obstaclesBounds.height)) <= 3)
                    return false;
            if (std::abs(posPeople.y + peopleBounds.height - posObs.y) <= 3)
                    return false;
            if (((posPeople.y + peopleBounds.height) - (posObs.y)) >= 0 && ((posPeople.y) - ((posObs.y) + obstaclesBounds.height) <= 0)){
                float distance = (posPeople.x + peopleBounds.width) - (posObs.x);
                if ((distance) <= 10 && (distance >= -6)) {
                    return true;
                }
            }
            return peopleBounds.intersects(obstaclesBounds);
        default:
            return false;
    }
}