#include "CGAME.h"
CGAME::CGAME() : window(nullptr) {
}
void CGAME::GenObj(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0,1); //obj1 appears at x=0 or 955
    std::uniform_real_distribution<> dis_obj2(400, 700); //obj2 will appear if obj1 across it
    std::uniform_real_distribution<> speedDis(0.1f, 0.2f); 
    std::uniform_int_distribution<> numBirdsDis(1, 2); 
    std::uniform_int_distribution<> randObj(0, 2); 
    int indexObj=0;
    // random obj
    for (int j = -10; j < numLanes; ++j) {
        if (!lanes_visited[indexObj]) {
            ObjInLane[indexObj] = numBirdsDis(gen);        
            speed_lane[indexObj] = speedDis(gen);
            lanes_visited[indexObj] = true; 
            std::string type_obj = object_rand[randObj(gen)]; 
            int randomX = (dis1(gen) == 0 ? 0 : 995);
            direction.push_back(randomX == 0 ? 1 : -1);
            time_obj2[indexObj] = dis_obj2(gen) + direction[indexObj]*200; 

            int randomY = j * laneHeight; 
            if (type_obj == "birds")
                objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
            else
            if (type_obj == "dinosaurs")
                objects.emplace_back(std::make_shared<CDINOSAUR>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));       
            else
            if (type_obj == "birds2")
                objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));                
        }
        indexObj++;
    }    
}
CGAME::CGAME(sf::RenderWindow& window) : window(&window)
{
        isPress = false;
        view = window.getDefaultView();
        threshold = 180;
        stopGame = false;
        numLanes = window.getSize().y / laneHeight;
        int totalLanes = numLanes+10;
        lanes_visited.assign(totalLanes,0);
        secondObjCreated.assign(totalLanes,0);
        speed_lane.assign(totalLanes, 0.0f);
        time_obj2.assign(totalLanes, 0.0f);
        ObjInLane.assign(totalLanes, 1);
        GenObj(window);
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
            float lineY = view.getCenter().y - threshold;

            // Tạo đường thẳng
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0, lineY), sf::Color::White),
                sf::Vertex(sf::Vector2f(window->getSize().x, lineY), sf::Color::White)
            };

            // Vẽ đường thẳng
            window->draw(line, 2, sf::Lines);       
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

void CGAME::startGame(sf::RenderWindow& window) {   
          
            moveCooldown -= deltaTime;
            if (moveCooldown <= 0.0f && !stopGame) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isPress==false) {
                    isPress = true;
                    this->updatePosPeople('W');
                    moveCooldown = 0.007f;

                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& isPress==false) {
                    isPress = true;
                    this->updatePosPeople('A');
                    moveCooldown = 0.007f;
                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& isPress==false) {
                    isPress = true;
                    this->updatePosPeople('S');
                    moveCooldown = 0.007f;
                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& isPress==false) {
                    isPress = true;
                    this->updatePosPeople('D');
                    moveCooldown = 0.007f;
                }
                isPress = false;
            }
            //move camera
            sf::Vector2f playerPosition = cn.get_Position();
            if (playerPosition.y < view.getCenter().y - threshold) {
                int oldCenter =  view.getCenter().y;
                view.setCenter(view.getCenter().x, playerPosition.y-threshold);
                threshold = threshold + 100;
            }
            else if (playerPosition.y > view.getCenter().y + threshold+250 && view.getCenter().y!= window.getSize().y/2) {
                view.setCenter(view.getCenter().x, playerPosition.y + threshold+250);
                threshold = threshold - 100;
            }
            window.setView(view);
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
                   //  stopGame=true;
                  //  cn.Died();
                }
            }
            obj->Move();
        }
        int indexObj = 0;
        for (int i = -10; i < numLanes; ++i) {
            if ((direction[indexObj] == 1 && objects[indexObj]->getX() >= time_obj2[indexObj]) || (direction[indexObj] == -1 && objects[indexObj]->getX() <= time_obj2[indexObj]))
                if (!secondObjCreated[indexObj] &&ObjInLane[indexObj] == 2) {
                    int randomY = i * laneHeight;
                    int x2 = direction[indexObj] == 1 ? 0: 995;
                    objects.emplace_back(std::make_shared<CBIRD2>(1000, x2 , randomY, speed_lane[indexObj],direction[indexObj]));
                    secondObjCreated[indexObj] = true; 
            }
            indexObj++;
        }
    }