#include <SFML/Graphics.hpp>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include <iostream> // Đảm bảo rằng bạn đã bao gồm thư viện iostream

class CollisionManager {
public:
    static bool checkCollision(const CPEOPLE& people, const CANIMAL& animal) {
        sf::FloatRect peopleBounds = people.getGlobalBounds();
        sf::FloatRect animalBounds = animal.getGlobalBounds();
        return peopleBounds.intersects(animalBounds);
    }
};