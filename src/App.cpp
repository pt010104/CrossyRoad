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
        if (!game.getPeople().getState() && game.getDie()){
            bool finish = false;
            auto current_time = std::chrono::steady_clock::now();
            if ( (current_time - start) < die_duration) {
                finish = true;
                if (currentGameState == GameState::PLAYING){
                    game.startGame(window);
                    update();
                }
                render();
            }
            if (!finish){
                game.setDie(false);
                currentGameState = GameState::PAUSED;
            }
        }
        else 
        if (!game.getSpecial())
        {
            processEvents();
            if (currentGameState == GameState::PLAYING){
                game.startGame(window);  
                update();
            }
            render();
            start = std::chrono::steady_clock::now();
        }
        else if (!game.getFinish() && game.getSpecial()){
            int steps = 0;
            bool inAnim = false;
            auto current_time = std::chrono::steady_clock::now();
            if ( (current_time - start) < work_duration) {
                inAnim = true;
                game.updatePosPeople('W'); // Update character position
                if (currentGameState == GameState::PLAYING){
                    game.startGame(window);
                    update();
                }
                render();
                std::this_thread::sleep_for(10ms);
            }
            if (!inAnim) {
                std::cout << "End animation\n";
                game.setSpecial(false);
                game.setFinish(true);
            }
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
            game.setLevel(1);
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
            else if (buttonName == "highScoreButton"){
                menu.isHighScore = true;
            }
            else if (buttonName == "creditsButton"){
                menu.isCredits = true;
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
            std::string buttonName = menu.handleInputPausedMenu(true);
            if (buttonName == "resume"){
                currentGameState = GameState::PLAYING;
            }
            else if (buttonName == "retry"){
                if (game.checkwindow()) {
                    realTimeClock.restart();
                    game.resetGame();
                }
                currentGameState = GameState::PLAYING;
            }
            else if (buttonName == "returnMenu"){
                menu.resetMainMenu();
                currentGameState = GameState::MENU;
            }
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

        case GameState::WIN:{
            if(menu.soundOn)
                globalSound.stop();
            sf::SoundBuffer buffer;
            sf::Sound soundWin;
            if (!buffer.loadFromFile("Assets/Sounds/gameWin.wav")) {
                std::cerr << "Error loading mainSound" << std::endl;
            }
            else
            {
                soundWin.setBuffer(buffer);
                soundWin.setLoop(true);
                soundWin.play();
            }
            sf::Clock clockWin;
            while (clockWin.getElapsedTime() < sf::seconds(6)) {
                window.clear();
                menu.winGame();
                window.display();
            }
            currentGameState = GameState::MENU;
            if(menu.soundOn)
                globalSound.play();
            break;
        }
            

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
                case GameState::PLAYING:{
                    if (game.getLevel()==6)
                    {
                        menu.resetMainMenu();
                        currentGameState = GameState::WIN;
                    }
                    break;
                }

                case GameState::PAUSED:
                {
                    if(game.getEndless())
                    {
                        std::fstream fileScore("Score.txt");
                        if(!fileScore)
                        {
                            std::cerr<<"Could not open score file";
                        }
                        else{
                            if(Score!=0)
                                fileScore <<Score<<std::endl;
                        }

                    }
                    std::string tmp = menu.handleInputPausedMenu(false);
                    break;
                }

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