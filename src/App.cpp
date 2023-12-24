#include "App.h"
#include <stdlib.h>
App::App() : window(sf::VideoMode(1000, 800), "Crossy Road"), game(window), menu(sf::Font(), window) {
    gameRunning = true;
    exitGameFlag = false; 
    gameThread = std::thread(&App::gameLoop, this);

}
App::~App() {
    {
        std::lock_guard<std::mutex> lock(gameMutex);
            exitGameFlag = true;
            gameCondition.notify_one();
    }
    if (gameThread.joinable()) {
        gameThread.join();
    }
}

void App::run() {
    while (window.isOpen() && !exitGameFlag) {
        processEvents();
        render();
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                exitGame();
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseClick(event);
                break;

            case sf::Event::KeyPressed:
                handleKeyPress(event);
                break;

            default:
                break;
        }
    }
}

void App::handleMouseClick(const sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (currentGameState == GameState::MENU) {
            if (false) {
            }
        }
        else if (currentGameState == GameState::PAUSED) {

        }
    }
}

void App::handleKeyPress(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        switch (currentGameState) {
            case GameState::MENU:
                exitGame();
                break;
            case GameState::PLAYING:
                currentGameState = GameState::PAUSED;
                break;
            case GameState::PAUSED:
                menu.resetMainMenu();
                currentGameState = GameState::MENU;
                break;
            //others
            default:
                break;
        }
        
    }
    else if (event.key.code == sf::Keyboard::Enter) {
        if (currentGameState == GameState::PAUSED) {
            currentGameState = GameState::PLAYING;
        }
        else if (currentGameState == GameState::MENU) {
            if (game.checkwindow()) {
                game.resetGame();
            }
            currentGameState = GameState::PLAYING;
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
    switch (currentGameState) {
        case GameState::MENU:
            menu.renderMainMenu();
            break;

        case GameState::PLAYING:
            game.drawGame();
            break;

        case GameState::PAUSED:
            menu.renderPausedMenu();
            break;

        case GameState::EXITING:
            window.close();
            break;

        default:
            break;
    } 
    window.display();
}

void App::gameLoop() {
    std::unique_lock<std::mutex> lock(gameMutex);
    while (!exitGameFlag) {
        gameCondition.wait(lock, [this]{ return gameRunning || exitGameFlag; });
        
        if (exitGameFlag) {
            break; 
        }

        switch (currentGameState) {
            case GameState::MENU:
                
                menu.handleInputMainMenu();
                break;

            case GameState::PLAYING:
                try {
                    game.startGame(window);
                    update();
                } catch (const std::exception& e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }
                break;

            case GameState::PAUSED:
                
                menu.handleInputPausedMenu();
                break;

            case GameState::EXITING:
                break;
            default:
                break;
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
        lock.lock();
    }
}

void App::startGame() {
    currentGameState = GameState::PLAYING;
}

void App::pauseGame() {
    std::lock_guard<std::mutex> lock(gameMutex);
    gameRunning = false; 
}

void App::resumeGame() {
    {
        std::lock_guard<std::mutex> lock(gameMutex);
        gameRunning = true;
    }
    gameCondition.notify_one(); 
}
void App::exitGame() {
    {
        std::lock_guard<std::mutex> lock(gameMutex);
        exitGameFlag = true; // Set the flag to exit the game
    }
    gameCondition.notify_one(); // Signal the game loop to wake up and exit
    window.close();
}