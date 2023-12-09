#ifndef CGAME_H
#define CGAME_H

#include <fstream>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINAUSOR.h"
#include "CBIRD.h"
#include "CPEOPLE.h"
#include <thread>
#include <SFML/Graphics.hpp>

class CGAME {
    CTRUCK* axt;
    CCAR* axh;
    CDINAUSOR* akl;
    CBIRD* ac;
    CPEOPLE cn;
    sf::RenderWindow* window;
public:
    CGAME ();
    CGAME(sf::RenderWindow& window);
    ~CGAME();

    void drawGame();
    CPEOPLE getPeople();
    CVEHICLE* getVehicle();
    CANIMAL* getAnimal();
    void resetGame();
    void exitGame(std::thread& thread);
    void startGame(sf::Event& event);
    void loadGame(std::istream& is);
    void saveGame(std::ostream& os);
    void pauseGame(std::thread& thread);
    void resumeGame(std::thread& thread);
    void updatePosPeople(char direction);
    void updatePosVehicle();
    void updatePosAnimal();
};


#endif