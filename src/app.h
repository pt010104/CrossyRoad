#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "CGAME.h"
class App {
public:
    App();
    ~App();
    void run();
private:
    sf::RenderWindow window;
    std::thread gameThread;
    sf::Clock clock;
    float deltaTime;
    CGAME game;
    void processEvents();
    void update();
    void render();
};

#endif 