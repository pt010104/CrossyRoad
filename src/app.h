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
    sf::CircleShape circle;
    void processEvents();
    void update();
    void render();
    CGAME game;
};

#endif 