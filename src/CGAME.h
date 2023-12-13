#ifndef CGAME_H
#define CGAME_H

#include <fstream>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINOSAUR.h"
#include "CBIRD.h"
#include "CPEOPLE.h"
#include "CollisionManager.h"
#include <thread>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>


class CGAME {
    float moveCooldown;
    float moveCooldown_animal;
    float deltaTime;
    bool stopGame;
    std::vector<CTRUCK> trucks; 
    std::vector<CCAR> cars;    
    std::vector<CDINOSAUR> dinos;
    CPEOPLE cn;
    std::vector<std::string> object_rand = {"birds","dinosaurs","cars","trucks"};

    sf::RenderWindow* window;
    int numLanes;
    std::vector<bool> lanes_visited;
    std::vector<float> speed_lane;
    std::vector<float> time_obj2;
    const int laneHeight = 200;
    std::vector <int> ObjInLane;
    std::vector <char> direction;
    std::vector<bool> secondObjCreated;
    std::vector<std::shared_ptr<CANIMAL>> objects;

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