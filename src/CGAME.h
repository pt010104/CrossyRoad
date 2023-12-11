#ifndef CGAME_H
#define CGAME_H

#include <fstream>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINAUSOR.h"
#include "CBIRD.h"
#include "CPEOPLE.h"
#include <thread>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

class CGAME {
    float moveCooldown;
    float deltaTime;

    std::vector<CTRUCK> trucks; 
    std::vector<CCAR> cars;    
    std::vector<CDINAUSOR> dinos;
    std::vector<CBIRD> birds;   
    CPEOPLE cn;
    sf::RenderWindow* window;
    int numLanes;
    std::vector<bool> lanes_visited;
    std::vector<float> speed_lane;
    std::vector<float> time_bird2;
    const int laneHeight = 200;
    std::vector <int> BirdsInLane;
    std::vector<bool> secondBirdCreated;
public:
    CGAME ();
    CGAME(sf::RenderWindow& window);
    ~CGAME();

    void drawGame();
    CPEOPLE getPeople();
    std::vector<CVEHICLE*> getVehicles();
    std::vector<CANIMAL*> getAnimals();
    void resetGame();
    void exitGame(std::thread& thread);
    void startGame(sf::Event& event);
    void loadGame(std::istream& is);
    void saveGame(std::ostream& os);
    void pauseGame(std::thread& thread);
    void resumeGame(std::thread& thread);
    void updatePosPeople(char direction);
    void updateAnimation(float deltatime);
    void updatePosVehicle();
    void updatePosAnimal();
};


#endif