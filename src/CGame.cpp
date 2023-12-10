#include "CGAME.h"
CGAME::CGAME() : window(nullptr) {
}
CGAME::CGAME(sf::RenderWindow& window) : window(&window){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(50, 950); 
    std::uniform_real_distribution<> speedDis(0.1f, 0.3f); 
     const int birdHeight = 80; 
    const int numLanes = window.getSize().y / birdHeight;
    std::vector<bool> lanesOccupied(numLanes, false);

    // random birds
    int numBirds = numLanes; 
    for (int i = 0; i < numBirds; ++i) {
        float randomSpeed = speedDis(gen);

        int lane = -1;
        for (int j = 0; j < numLanes; ++j) {
            if (!lanesOccupied[j]) {
                lane = j;
                lanesOccupied[j] = true; 
                break;
            }
        }

        if (lane != -1) {
            int randomX = dis(gen);
            int randomY = lane * birdHeight; /
            birds.emplace_back(window.getSize().x, randomX, randomY, randomSpeed);
        }
    }
}
CGAME::~CGAME() {

}

void CGAME::drawGame() 
{
    if (window) {
        cn.draw(*window);
        for (auto& bird : birds) 
            bird.draw(*window);
    }
}
CPEOPLE CGAME::getPeople() {
    return cn;
}

std::vector<CVEHICLE*> CGAME::getVehicles() {
    std::vector<CVEHICLE*> vehicles;
    for (auto& truck : trucks) {
        vehicles.push_back(&truck);
    }
    for (auto& car : cars) {
        vehicles.push_back(&car);
    }
    return vehicles;
}
std::vector<CANIMAL*> CGAME::getAnimals() {
    std::vector<CANIMAL*> animals;
    for (auto& dino : dinos) {
        animals.push_back(&dino);
    }
    for (auto& bird : birds) {
        animals.push_back(&bird);
    }
    return animals;
}
void CGAME::resetGame() {
}
void CGAME::exitGame(std::thread& thread) {
        // Exit thread
}

void CGAME::startGame(sf::Event& event) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->updatePosPeople('W');
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->updatePosPeople('A');
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            this->updatePosPeople('S');
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->updatePosPeople('D');
        }
        updatePosAnimal();
}

void CGAME::loadGame(std::istream& is) {
}

void CGAME::saveGame(std::ostream& os) {
}

void CGAME::pauseGame(std::thread& thread) {
        // Pause the thread
}

void CGAME::resumeGame(std::thread& thread) {
        // Resume the thread
}

void CGAME::updatePosPeople(char direction) {
    if(cn.getState())
    {
        switch (direction)
        {
            case 'W':
                cn.Up();
                break;
            case 'A':
                cn.Left();
                break;
            case 'S':
                cn.Down();
                break;
            case 'D':
                cn.Right();
                break;
            default:
                break;
        }
    }
}

void CGAME::updatePosVehicle() {
        // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
     for (auto& bird : birds) {
        bird.Move();
     }
}