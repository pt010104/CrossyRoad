#include "App.h"
#include <stdlib.h>
App::App() : window(sf::VideoMode(1000, 800), "Crossy Road"), game(window) {
    try {
            if (!menuTexture.loadFromFile("Assets/Menu/Tmp.png")) {
                throw std::runtime_error("Failed to load menu image.");
            }

            menuSprite.setTexture(menuTexture);
            // menuSprite.setPosition(/* set position */);
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            sf::Image errorImage;
            errorImage.create(1000, 800, sf::Color::Red); // Create a red placeholder image
            menuTexture.loadFromImage(errorImage);
            menuSprite.setTexture(menuTexture);
        }
    gameThread = std::thread(&App::gameLoop, this);
}
App::~App() {
    if (gameThread.joinable()) {
        gameThread.join();
    }
}
    
void App::run() {
    while (window.isOpen()) {
        processEvents();

        switch (currentGameState) {
            case GameState::MENU:
                window.clear();
                window.draw(menuSprite);
                window.display();
                if (false) { //Or a key is pressed
                    currentGameState = GameState::PLAYING;
                }
                break;

            case GameState::PLAYING:
                try {
                    game.startGame(window);
                    render();
                    update();
                } catch (const std::exception& e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }
                break;

            case GameState::PAUSED:
                break;

            case GameState::EXITING:
                window.close(); //Forced close = close
                break;

            default:
                break;
        }
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                exitGame(); //Forced close = close
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Enter) {
                    currentGameState = GameState::PLAYING;
                } else
                if (event.key.code == sf::Keyboard::Escape) {
                    exitGame(); 
                }
                
                break;

            default:
                break;
        }
    }
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

void App::gameLoop() {
    while (currentGameState != GameState::EXITING) {
        switch (currentGameState) {
            case GameState::MENU:
                break;

            case GameState::PLAYING:
                break;

            case GameState::PAUSED:
                break;

            default:
                break;
        }
    }
}

void App::startGame() {
    currentGameState = GameState::PLAYING;
}

void App::pauseGame() {
    currentGameState = GameState::PAUSED;
}

void App::resumeGame() {
    currentGameState = GameState::PLAYING;
}

void App::exitGame() {
    //clean up maybe
    window.close();
    currentGameState = GameState::EXITING;
}