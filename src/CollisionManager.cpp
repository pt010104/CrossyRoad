#include "CollisionManager.h"
#include <cmath>

bool CollisionManager::checkCollision(CPEOPLE& people, CANIMAL& animal) {
    int bias = 0; //expand radius
    sf::Vector2f pos1 = people.get_Position();
    sf::Vector2f pos2 = animal.get_Position();
    float dx = (pos1.x - pos2.x);
    float dy = (pos1.y - pos2.y);
    float distance = std::sqrt(dx * dx + dy * dy);

    float radius1 = people.getRadius();
    float radius2 = animal.getRadius()+bias; 

    return distance < (radius1 + radius2);
}