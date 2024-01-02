#ifndef APP_H
#define APP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <atomic>
#include "CGAME.h"
#include "GameState.h"
#include "Menu.h"
#include <mutex>               
#include <condition_variable>   
#include <iostream>
#include "Global.h"

class App {
public:
    App();
    ~App();
    void run();
private:
    sf::RenderWindow window;
    std::thread gameThread;
    std::atomic<GameState> currentGameState { GameState::MENU };
    sf::Texture menuTexture;
    sf::Sprite menuSprite;
    sf::Clock clock;
    sf::Clock realTimeClock;
    Menu menu;
    float deltaTime;
    float realTime;
    CGAME game;
    bool gameRunning;
    bool exitGameFlag;

    void processEvents();
    void handleMouseClick(const sf::Event& event);
    void handleKeyPress(const sf::Event& event);
    void update();
    void render();
    void gameLoop();
    void startGame();
    void pauseGame();
    void resumeGame();
    void exitGame();
    std::mutex gameMutex;
    std::condition_variable gameCondition;
};

#endif 