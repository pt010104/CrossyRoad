#ifndef CGAME_H
#define CGAME_H

#include <fstream>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINAUSOR.h"
#include "CBIRD.h"
#include "CPEOPLE.h"
#include <SFML/System/Thread.hpp>
#include <SFML/Graphics.hpp>

class CGAME {
    CTRUCK* axt;
    CCAR* axh;
    // CDINAUSOR* akl;
    // CBIRD* ac;
    CPEOPLE cn;
public:
    CGAME ();
    CGAME(sf::RenderWindow& window);
    ~CGAME();

    void drawGame();
    CPEOPLE getPeople();
    //CVEHICLE* getVehicle();
    CANIMAL* getAnimal();
    void resetGame();
    void exitGame(sf::Thread& thread);
    void startGame();
    void loadGame(std::istream& is);
    void saveGame(std::ostream& os);
    void pauseGame(sf::Thread& thread);
    void resumeGame(sf::Thread& thread);
    void updatePosPeople(char direction);
    void updatePosVehicle();
    void updatePosAnimal();
private:
    sf::RenderWindow& window;
};


#endif