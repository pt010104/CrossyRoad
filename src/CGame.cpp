#include "CGAME.h"
CGAME::CGAME() : window(nullptr) {
}
void CGAME::GenObj(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0,1); //obj1 appears at x=0 or 955
    std::uniform_real_distribution<> dis_obj2(400, 700); //obj2 will appear if obj1 across it
    std::uniform_real_distribution<> speedDis(7.5f, 8.5f); 
    std::uniform_int_distribution<> numBirdsDis(1, 2); 
    std::uniform_int_distribution<> randObj(0, 2); 
    int indexObj=0;
    // random obj
    for (int j = -40; j < numLanes; j++) {
        if (abs(j)%2==0) {
            ObjInLane[indexObj] = numBirdsDis(gen);        
            speed_lane[indexObj] = speedDis(gen);
            std::string type_obj = object_rand[randObj(gen)]; 
            int randomX = (dis1(gen) == 0 ? 0 : 995);
            direction.push_back(randomX == 0 ? 1 : -1);
            time_obj2[indexObj] = dis_obj2(gen) + direction[direction.size()-1]*200; 
            int randomY = j * laneHeight-50; 
            //create traffic pos
            TrafficLight_pos.push_back(j*laneHeight-25);      

            if (type_obj == "birds")
                objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
            else
            if (type_obj == "dinosaurs")
                objects.emplace_back(std::make_shared<CDINOSAUR>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));       
            else
            if (type_obj == "birds2")
                objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));                
            indexObj++;        
        }
        if(abs(j)%2==0) //mons tile 
            maps.emplace_back(window.getSize().x,j*laneHeight,"mons");      
        if (abs(j)%2 == 1) //map tile 
        {
            maps.emplace_back(window.getSize().x,j*laneHeight,"people");              
            int numFrames = 7;
            std::uniform_int_distribution<int> dist(1, numFrames);
            std::uniform_int_distribution<int> dist2(3, 4);
            int numObsInLane = dist2(gen);
            std::vector <int> orderFrame;
            for (int i =0; i<numObsInLane; ++i) {
                int indexFrame = dist(gen);
                orderFrame.push_back(indexFrame);
            }
            std::vector<int> coordX(8); 
            std::iota(coordX.begin(), coordX.end(), 1); 
            std::shuffle(coordX.begin(), coordX.end(), gen); 
            for (int i = 0; i<orderFrame.size();i++)
            {
                std::string tileName = "right_" + std::to_string(orderFrame[i]); 
                obstacles.emplace_back(window.getSize().x,coordX[i]*133,j*laneHeight+25,tileName);
            }
        }            
    }
}   
CGAME::CGAME(sf::RenderWindow& window) : window(&window)
{
        timeAppear = 10;
        isPress = false;
        view = window.getDefaultView();
        newGameMainView = view;
        threshold = 200; 
        stopGame = false;
        numLanes = window.getSize().y / laneHeight;
        int totalLanes = numLanes+50;
        secondObjCreated.assign(totalLanes*2,false);
        speed_lane.assign(totalLanes*2, 0.0f);
        time_obj2.assign(totalLanes*2, 0.0f);
        ObjInLane.assign(totalLanes*2, 1);
        isSecond.assign(totalLanes*2,false);
        isDraw.assign(totalLanes*2,true);
        GenObj(window);
}
CGAME::~CGAME() {
    delete window;

}

void CGAME::drawGame(float& realTime) 
{
    if (window) {
            for (auto tile:maps)
                tile.draw(*window);
            for (auto obstacle:obstacles)
                obstacle.draw(*window);
            if (cn.getState())
                cn.draw(*window);
            for (auto& obj : objects) 
            {
                if (drag.state != "fire")
                    obj->draw(*window);
                else if (obj->get_Position().y != drag.mY-25 && obj->get_Position().y != drag.mY+25)
                    obj->draw(*window);
            }     
            if (realTime >=timeAppear && drag.state == "disap")
            {
                auto it = std::upper_bound(TrafficLight_pos.begin(), TrafficLight_pos.end(), cn.get_Position().y);
                if (it != TrafficLight_pos.begin())
                {
                    --it;
                    drag.mY = *it;
                    drag.state = "appear";
                }
                timeAppear += 25;
             
            }
            if (drag.state != "disap")
            {
                    drag.appear(realTime-(timeAppear-25));   
                    drag.draw(*window);
            }   

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
    view = newGameMainView;
    isPress = false;
    threshold = 200;
    stopGame = false;
    // ... other variables specific to game state

    // Clear vectors and reset their sizes
    secondObjCreated.clear();
    speed_lane.clear();
    time_obj2.clear();
    ObjInLane.clear();
    isSecond.clear();
    isDraw.clear();
    maps.clear();
    obstacles.clear();
    objects.clear();
    TrafficLight_pos.clear();    
    int totalLanes = window->getSize().y / laneHeight;
    secondObjCreated.assign(totalLanes * 2, false);
    speed_lane.assign(totalLanes * 2, 0.0f);
    time_obj2.assign(totalLanes * 2, 0.0f);
    ObjInLane.assign(totalLanes * 2, 1);
    isSecond.assign(totalLanes * 2, false);
    isDraw.assign(totalLanes * 2, true);

    cn.reset();
    // Re-generate game objects
    GenObj(*window);
    currentObs.clear();
    for (auto obstacle : obstacles){
        sf::Vector2f obsPos = obstacle.get_Position();
        if (obsPos.y >= -100 && obsPos.y <= 800)
            currentObs.push_back(obstacle);
    }
}
void CGAME::exitGame(std::thread& thread) {
    stopGame = true;
    if (thread.joinable()) {
        thread.join();
    }
}

void CGAME::startGame(sf::RenderWindow& window) {   
            if (!stopGame) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isPress==false) {
                    isPress = true;
                    bool canMove = true;
                    for (auto obstacle : currentObs) {
                        if (CollisionManager::checkCollisionInDirection(cn, obstacle, 'W')) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        this->updatePosPeople('W');
                    }

                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& isPress==false) {
                    isPress = true;
                    bool canMove = true;
                    for (auto obstacle : currentObs) {
                        if (CollisionManager::checkCollisionInDirection(cn, obstacle, 'A')) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        this->updatePosPeople('A');
                    }
                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& isPress==false) {
                    isPress = true;
                    bool canMove = true;
                    for (auto obstacle : currentObs) {
                        if (CollisionManager::checkCollisionInDirection(cn, obstacle, 'S')) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        this->updatePosPeople('S');
                    }
                }
                else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& isPress==false) {
                    isPress = true;
                    bool canMove = true;
                    for (auto obstacle : currentObs) {
                        if (CollisionManager::checkCollisionInDirection(cn, obstacle, 'D')) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        this->updatePosPeople('D');
                    }
                }
                isPress = false;
            }
            //move camera && refresh currentObstacles
            sf::Vector2f playerPosition = cn.get_Position();
            if (playerPosition.y < view.getCenter().y - threshold) {
                view.setCenter(view.getCenter().x, playerPosition.y-200);
                currentObs.clear();
                for (auto obstacle : obstacles){
                    sf::Vector2f obsPos = obstacle.get_Position();
                    if (obsPos.y >= (playerPosition.y - 700) && obsPos.y <= (playerPosition.y + 200)){
                        currentObs.push_back(obstacle);
                    }
                }
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
    drag.UpdateFrame(deltaTime);
}
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
        for (auto& obj : objects) {
            if(cn.getState())
            {
                if (drag.state != "fire" || (obj->get_Position().y != drag.mY-25 && obj->get_Position().y != drag.mY+25))
                    if (CollisionManager::checkCollisionAnimal(cn, *obj))
                    {
                        stopGame=true;
                        cn.Died();
                    }
            }
            if (drag.state != "fire")
                obj->Move();
            else if (obj->get_Position().y != drag.mY-25 && obj->get_Position().y != drag.mY+25)
                obj->Move();
        }
        int indexObj = 0;
        for (int i = -40; i < numLanes; i+=2) {
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

bool CGAME::checkwindow(){
    if (window) return true;
    return false;
}