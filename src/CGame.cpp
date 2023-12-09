#include "CGAME.h"
CGAME::CGAME() : window(nullptr), axh(nullptr), ac(nullptr) {
}
CGAME::CGAME(sf::RenderWindow& window) : window(&window), axh(new CCAR()), ac(new CBIRD()) {
}

CGAME::~CGAME() {
     delete axh;
    delete ac;
}

void CGAME::drawGame() {
    if (window) {
            cn.draw(*window);
    }
}
CPEOPLE CGAME::getPeople() {
    return cn;
}

CVEHICLE* CGAME::getVehicle() {
    return axh; 
}

CANIMAL* CGAME::getAnimal() {
    return ac; 
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
        // Move CDINAUSOR and CBIRD
}