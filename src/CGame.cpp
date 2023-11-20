#include "CGAME.h"

CGAME::CGAME(sf::RenderWindow& window) : window(window) {
}

CGAME::~CGAME() {
}

void CGAME::drawGame() {
    // Draw the game after having the data
}

CPEOPLE CGAME::getPeople() {
}

CVEHICLE* CGAME::getVehicle() {
}

CANIMAL* CGAME::getAnimal() {
}

void CGAME::resetGame() {
}

void CGAME::exitGame(sf::Thread& thread) {
    // Exit thread
}

void CGAME::startGame() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            int pos;
            //  player move
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cn.Up();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cn.Left();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cn.Down();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cn.Right();
            }
        }
    }
}

void CGAME::loadGame(std::istream& is) {
    // Load  saved game
}

void CGAME::saveGame(std::ostream& os) {
}

void CGAME::pauseGame(sf::Thread& thread) {
    // Pause the thread
}

void CGAME::resumeGame(sf::Thread& thread) {
    // Resume the thread
}

void CGAME::updatePosPeople(char direction) {
    // Control the movement of CPEOPLE
}

void CGAME::updatePosVehicle() {
    // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
    // Move CDINAUSOR and CBIRD
}