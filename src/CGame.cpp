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
        std::uniform_int_distribution<> dis1(0,1);
        std::uniform_real_distribution<> dis_bird1(400, 900); //bird2 will appear if bird1 across it
        std::uniform_real_distribution<> speedDis(0.05f, 0.08); 
        std::uniform_int_distribution<> numBirdsDis(1, 2); 

        // random birds
        for (int j = 0; j < numLanes; ++j) {
            if (!lanes_visited[j]) {
                BirdsInLane[j] = numBirdsDis(gen);        
                time_bird2[j] = dis_bird1(gen); 
                speed_lane[j] = speedDis(gen);
                lanes_visited[j] = true; 
                int randomX = (dis1(gen) == 0 ? 0 : 995);
                direction.push_back(randomX == 0 ? 1 : -1);
                int randomY = j * laneHeight; 
                birds.emplace_back(window.getSize().x, randomX, randomY, speed_lane[j],direction[j]);
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
                    moveCooldown = 0.007f;

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    this->updatePosPeople('A');
                    moveCooldown = 0.007f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    this->updatePosPeople('S');
                    moveCooldown = 0.007f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    this->updatePosPeople('D');
                    moveCooldown = 0.007f;
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
        deltaTime = dt;
        moveCooldown_animal -= deltaTime;
        cn.UpdateFrame(deltaTime);
            for (auto& bird : birds) {
                bird.UpdateFrame(deltaTime);
            moveCooldown_animal = 0.1f;
        }
    }
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
    }

    void CGAME::updatePosAnimal() {
        for (auto& bird : birds) {
            bird.Move();
        }
        for (int i = 0; i < numLanes; ++i) {
            if (birds[i].getX() >= time_bird2[i] && !secondBirdCreated[i] &&BirdsInLane[i] == 2) {
                int randomY = i * laneHeight;
                int x2 = direction[i] == 1 ? 0: 995;
                birds.emplace_back(1000, x2, randomY, speed_lane[i],direction[i]);
                secondBirdCreated[i] = true; 
            }
        }
    }