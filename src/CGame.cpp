    #include "CGAME.h"
    CGAME::CGAME() : window(nullptr) {
    }
    CGAME::CGAME(sf::RenderWindow& window) : window(&window)
    {
        numLanes = window.getSize().y / laneHeight;
        lanes_visited.assign(numLanes, false);
        speed_lane.assign(numLanes, 0.0f);
        time_bird2.assign(numLanes, 0.0f);
        BirdsInLane.assign(numLanes, 0);
        secondBirdCreated.assign(numLanes, false);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis_bird1(200, 670);
        std::uniform_real_distribution<> speedDis(0.08f, 0.1); 
        std::uniform_int_distribution<> numBirdsDis(1, 2); 

        // random birds
        for (int i = 0; i < numLanes; ++i) {
            int lane = -1;
            for (int j = 0; j < numLanes; ++j) {
                if (!lanes_visited[j]) {
                    BirdsInLane[i] = numBirdsDis(gen);        
                    time_bird2[i] = dis_bird1(gen);
                    speed_lane[j] = speedDis(gen);
                    lane = j;
                    lanes_visited[j] = true; 
                    break;
                }
            }
            if (lane != -1) {
                int randomX = 5;
                int randomY = lane * laneHeight; 
                birds.emplace_back(window.getSize().x, randomX, randomY, speed_lane[lane]);
            }
        }
    }
    CGAME::~CGAME() {

    }

    void CGAME::drawGame() 
    {
        if (window) {
            cn.draw(*window);
            for (auto& bird : birds) 
                bird.draw(*window);
        }
    }
    CPEOPLE CGAME::getPeople() {
        return cn;
    }

    std::vector<CVEHICLE*> CGAME::getVehicles() {
        std::vector<CVEHICLE*> vehicles;
        for (auto& truck : trucks) {
            vehicles.push_back(&truck);
        }
        for (auto& car : cars) {
            vehicles.push_back(&car);
        }
        return vehicles;
    }
    std::vector<CANIMAL*> CGAME::getAnimals() {
        std::vector<CANIMAL*> animals;
        for (auto& dino : dinos) {
            animals.push_back(&dino);
        }
        for (auto& bird : birds) {
            animals.push_back(&bird);
        }
        return animals;
    }
    void CGAME::resetGame() {
    }
    void CGAME::exitGame(std::thread& thread) {
            // Exit thread
    }

    void CGAME::startGame(sf::Event& event) {
            moveCooldown -= deltaTime;
            if (moveCooldown <= 0.0f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    this->updatePosPeople('W');
                    moveCooldown = 0.005f;

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    this->updatePosPeople('A');
                    moveCooldown = 0.005f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    this->updatePosPeople('S');
                    moveCooldown = 0.005f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    this->updatePosPeople('D');
                    moveCooldown = 0.005f;
                }
            }
            updatePosAnimal();
    }

    void CGAME::loadGame(std::istream& is) {
    }

    void CGAME::saveGame(std::ostream& os) {
    }

    void CGAME::pauseGame(std::thread& thread) {
            // Pause the thread
    }

    void CGAME::resumeGame(std::thread& thread) {
            // Resume the thread
    }

    void CGAME::updatePosPeople(char direction) {
        if(cn.getState())
        {
            switch (direction)
            {
                case 'W':
                    cn.Up();
                    break;
                case 'A':
                    cn.Left();
                    break;
                case 'S':
                    cn.Down();
                    break;
                case 'D':
                    cn.Right();
                    break;
                default:
                    break;
            }
        }
    }
    void CGAME::updateAnimation(float dt) {
        moveCooldown_animal -= deltaTime;
        cn.UpdateFrame(deltaTime);
        if (moveCooldown_animal <= 0.0f) {
            for (auto& bird : birds) {
                bird.UpdateFrame(deltaTime);
            }
            moveCooldown_animal = 0.1f;
        }
        deltaTime = dt;
    }
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
    }

    void CGAME::updatePosAnimal() {
        for (auto& bird : birds) {
            bird.Move();
        }
        for (int i = 0; i < numLanes; ++i) {
            if (birds[i].getX() == time_bird2[i] && !secondBirdCreated[i] &&BirdsInLane[i] == 2) {
                int randomY = i * laneHeight;
                birds.emplace_back(1000, 5, randomY, speed_lane[i]);
                secondBirdCreated[i] = true; 
            }
        }
    }