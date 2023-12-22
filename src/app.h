#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <atomic>
#include "CGAME.h"
#include "GameState.h"

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
    float deltaTime;
    CGAME game;
    void processEvents();
    void update();
    void render();
    void gameLoop();
    void startGame();
    void pauseGame();
    void resumeGame();
    void exitGame();
};

#endif 