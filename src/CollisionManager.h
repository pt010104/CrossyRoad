#include <SFML/Graphics.hpp>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include <iostream> // Đảm bảo rằng bạn đã bao gồm thư viện iostream

class CollisionManager {
public:
    static bool checkCollision(const CPEOPLE& people, const CANIMAL& animal) {
        sf::Vector2f pos1 = people.get_Position() + 
            sf::Vector2f(people.get_GlobalBounds().width / 2, people.get_GlobalBounds().height / 2);
        sf::Vector2f pos2 = animal.get_Position() + 
            sf::Vector2f(animal.get_GlobalBounds().width / 2, animal.get_GlobalBounds().height / 2);

        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        float radius1 = people.getRadius();
        float radius2 = animal.getRadius(); 

        return distance < (radius1 + radius2);
    }
};