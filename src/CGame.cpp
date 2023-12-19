#include "CGAME.h"
CGAME::CGAME() : window(nullptr) {
}

CGAME::CGAME(sf::RenderWindow& window) : window(&window)
    {
        stopGame = false;
        numLanes = window.getSize().y / laneHeight;
        lanes_visited.assign(numLanes, false);
        speed_lane.assign(numLanes, 0.0f);
        time_obj2.assign(numLanes, 0.0f);
        ObjInLane.assign(numLanes, 1);
        secondObjCreated.assign(numLanes, false);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis1(0,1); //obj1 appears at x=0 or 955
        std::uniform_real_distribution<> dis_obj2(400, 700); //obj2 will appear if obj2 across it
        std::uniform_real_distribution<> speedDis(0.08f, 0.2); 
        std::uniform_int_distribution<> numBirdsDis(1, 2); 
        std::uniform_int_distribution<> randObj(0, 2); 

        // random obj
        for (int j = 0; j < numLanes; ++j) {
            if (!lanes_visited[j]) {
                ObjInLane[j] = numBirdsDis(gen);        
                speed_lane[j] = speedDis(gen);
                lanes_visited[j] = true; 
                std::string type_obj = object_rand[randObj(gen)]; 
                int randomX = (dis1(gen) == 0 ? 0 : 995);
                direction.push_back(randomX == 0 ? 1 : -1);
                time_obj2[j] = dis_obj2(gen) + direction[j]*200; 

                int randomY = j * laneHeight; 
                if (type_obj == "birds")
                    objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY, speed_lane[j],direction[j]));
                else
                if (type_obj == "dinosaurs")
                    objects.emplace_back(std::make_shared<CDINOSAUR>(window.getSize().x, randomX, randomY, speed_lane[j],direction[j]));       
                else
                if (type_obj == "birds2")
                    objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY, speed_lane[j],direction[j]));                
            }
        }
}
CGAME::~CGAME() {
    delete window;

}

void CGAME::drawGame() 
{
        if (window) {
            if (cn.getState())
                cn.draw(*window);
            for (auto& obj : objects) 
                obj->draw(*window);
        }
}
CPEOPLE CGAME::getPeople() {
        return cn;
    }

std::vector<CVEHICLE*> CGAME::getVehicles() {
        // std::vector<CVEHICLE*> vehicles;
        // for (auto& truck : trucks) {
        //     vehicles.push_back(&truck);
        // }
        // for (auto& car : cars) {
        //     vehicles.push_back(&car);
        // }
        // return vehicles;
    }
std::vector<CANIMAL*> CGAME::getAnimals() {
        // std::vector<CANIMAL*> animals;
        // for (auto& dino : dinos) {
        //     animals.push_back(&dino);
        // }
        // return animals;
    }
void CGAME::resetGame() {
    }
void CGAME::exitGame(std::thread& thread) {
            // Exit thread
    }

void CGAME::startGame() {
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
    if(cn.getState())
    {

        cn.UpdateFrame(deltaTime);
    }
    for (auto& obj : objects) {
                obj->UpdateFrame(deltaTime);
            moveCooldown_animal = 0.1f;
    }
}
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
        for (auto& obj : objects) {
            if(cn.getState())
            {
                if (CollisionManager::checkCollision(cn, *obj))
                {
                    cn.Died();
                }
            }
            obj->Move();
        }
        for (int i = 0; i < numLanes; ++i) {
            if ((direction[i] == 1 && objects[i]->getX() >= time_obj2[i]) || (direction[i] == -1 && objects[i]->getX() <= time_obj2[i]))
                if (!secondObjCreated[i] &&ObjInLane[i] == 2) {
                    int randomY = i * laneHeight;
                    int x2 = direction[i] == 1 ? 0: 995;
                    objects.emplace_back(std::make_shared<CBIRD2>(1000, x2 , randomY, speed_lane[i],direction[i]));
                    secondObjCreated[i] = true; 
                }
        }
    }