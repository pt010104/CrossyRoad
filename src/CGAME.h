#ifndef CGAME_H
#define CGAME_H
#include <fstream>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINOSAUR.h"
#include "CBIRD.h"
#include "CBIRD2.h"
#include "CPEOPLE.h"
#include "Map.h"
#include "Obstacles.h"
#include "Dragon.h"
#include "CollisionManager.h"
#include <thread>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm> 
#include "Global.h"
#include "SpriteLoader.h"

class CGAME {
protected:
    sf::RenderWindow* window;
    float moveCooldown;
    float moveCooldown_animal;
    float deltaTime;
    bool stopGame;
    int threshold;
    float timeAppear;
    bool isPress;
    int level;
    int finishLine;
    bool endless = false;
    CPEOPLE cn;
    Dragon drag;
    std::vector<std::string> object_rand = {"birds","dinosaurs","birds2","cars","trucks"};
    int numLanes;
    std::vector<bool> isSecond;
    std::vector<bool> isDraw;
    std::vector<float> speed_lane;
    std::vector<float> time_obj2;
    std::vector<float> TrafficLight_pos;
    const int laneHeight = 132;
    const int multiplier = laneHeight*1;
    std::vector <int> ObjInLane;
    std::vector <int> direction;
    std::vector<bool> secondObjCreated;
    std::vector<std::shared_ptr<CANIMAL>> objects;
    std::vector<Map> maps;
    std::vector<Obstacles> obstacles;
    std::vector<Obstacles> currentObs;
     std::vector<std::shared_ptr<CANIMAL>> currentObjects;
    sf::View view;
    sf::View newGameMainView;
public:
    CGAME ();
    CGAME(sf::RenderWindow& window);
    void GenObj(sf::RenderWindow& window);
    ~CGAME();

    void drawGame(float& realTime);
    CPEOPLE getPeople();
    std::vector<CVEHICLE*> getVehicles();
    std::vector<CANIMAL*> getAnimals();
    void resetGame();
    void exitGame(std::thread& thread);
    void startGame(sf::RenderWindow& window);
    void loadGame(const std::string& filename,sf::RenderWindow& window);
    void saveGame(const std::string& filename);
    void pauseGame(std::thread& thread);
    void resumeGame(std::thread& thread);
    void updatePosPeople(char direction);
    void updateAnimation(float deltatime);
    void updatePosVehicle();
    void updatePosAnimal();
    bool checkwindow();
    void setEndless(bool mode);
    bool getEndless();
    void setLevel(int l);
    int getLevel();
};


#endif