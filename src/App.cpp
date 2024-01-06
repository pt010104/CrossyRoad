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
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Assets/Sounds/mainSound.wav")) {
        std::cerr << "Error loading mainSound" << std::endl;
    }
    else
    {
        globalSound.setBuffer(buffer);
        globalSound.setLoop(true);
        globalSound.play();
    }
    while (window.isOpen() && !exitGameFlag) {
        if (!game.getFinish())
        {
            processEvents();
            game.startGame(window);
            update();  
            render();
        }
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if(!game.getFinish())
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
            std::string buttonName = menu.handleInputMainMenu(true);
            if(buttonName == "play"){
                if (game.checkwindow()) {
                    realTimeClock.restart();
                    game.resetGame();
                }
                currentGameState = GameState::PLAYING;        
            }
            else if (buttonName == "settingsButton"){
                menu.isSettingPannel = true;
            }
            else if (buttonName == "modeEndless"){
                menu.pressEndless();
                game.setEndless(false);
            }
            else if (buttonName == "modeClassic"){
                menu.pressClassic();
                game.setEndless(true);
            }
            else if (buttonName == "loadSave"){
                if (game.checkwindow()) {
                    realTimeClock.restart();
                    game.resetGame();
                }
                currentGameState = GameState::PLAYING;   
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
                realTimeClock.restart();
                game.resetGame();
            }
            currentGameState = GameState::PLAYING;
        }
    }
}

void App::update() {
    realTime = realTimeClock.getElapsedTime().asSeconds();
    deltaTime = clock.restart().asSeconds();
    game.updatePosAnimal();
    game.updatePosVehicle();
    game.updateAnimation(deltaTime);

}

void App::render() {
    window.clear();
    switch (currentGameState) {
        case GameState::MENU:
            menu.renderMainMenu();
            break;

        case GameState::PLAYING:
            game.drawGame(realTime);
            break;

        case GameState::PAUSED:
            game.drawGame(realTime);
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
        if(game.getFinish() == false)
            switch (currentGameState) {
                case GameState::MENU:{
                    std::string tmp = menu.handleInputMainMenu(false);
                    break;
                }
                case GameState::PLAYING:

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
        exitGameFlag = true; 
    }
    gameCondition.notify_one(); 
    window.close();
}