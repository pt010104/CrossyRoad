#include "App.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
App::App() : window(sf::VideoMode(1000, 800), "Crossy Road"), game(window) {
}
App::~App() {
    if (gameThread.joinable()) {
        gameThread.join();
    }
}
    
void App::run() {
    while (window.isOpen()) {
        try{
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            game.startGame();
            update(); 
            render(); 
        }
        catch(const std::exception& e){
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
}

void App::processEvents() {
    
}

void App::update() {
    deltaTime = clock.restart().asSeconds();
    game.updateAnimation(deltaTime);
    game.updatePosAnimal();
    game.updatePosVehicle();
}

void App::render() {
    window.clear();
    game.drawGame(); 
    window.display();
}