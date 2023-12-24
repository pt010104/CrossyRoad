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

    float dx = (posPeople.x - posAnimal.x);
    float dy = (posPeople.y - posAnimal.y);
    float distance = std::sqrt(dx * dx + dy * dy);
    float radius1 = people.getRadius();
    float radius2 = animal.getRadius();
    return distance < (radius1 + radius2);
}
bool CollisionManager::checkCollision(CPEOPLE& people, Obstacles& obs) {
    sf::FloatRect peopleBounds = people.get_GlobalBounds();
    sf::FloatRect obstaclesBounds = obs.get_GlobalBounds();

    sf::Vector2f posPeople = people.get_Position();
    sf::Vector2f posObs = obs.get_Position();

    if(peopleBounds.width == 0 &&peopleBounds.height == 0)
        return false;
    if (std::abs(posPeople.y - posObs.y) > 10) 
        return false; 
    return peopleBounds.intersects(obstaclesBounds);
}