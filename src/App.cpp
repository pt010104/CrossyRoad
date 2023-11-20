#include "App.h"

App::App() : window(sf::VideoMode(1000, 800), "Crossy Road") {
    game.startGame(); 
}

App::~App() {
}

void App::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void App::update() {
    game.updatePosVehicle();
    game.updatePosAnimal();
}

void App::render() {
    window.clear(sf::Color::Black);
    window.draw(circle);
    window.display();
}