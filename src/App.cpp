#include "App.h"

App::App() : window(sf::VideoMode(1000, 800), "Crossy Road"), game(window) {
}
App::~App() {
    if (gameThread.joinable()) {
        gameThread.join();
    }
}

void App::run() {
    while (window.isOpen()) {
        processEvents(); // Process window events
        update(); // Update game state if necessary
        render(); // Render the game state
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        game.startGame(event);
    }
}

void App::update() {
    game.updatePosAnimal();
    game.updatePosVehicle();
}

void App::render() {
    window.clear();
    game.drawGame(); 
    window.display();
}