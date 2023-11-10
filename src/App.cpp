#include "App.h"

App::App() : window(sf::VideoMode(800, 600), "SFML Application"), circle(50.f) {
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(375, 275); 
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
}

void App::render() {
    window.clear(sf::Color::Black);
    window.draw(circle);
    window.display();
}