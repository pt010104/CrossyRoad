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
            float randomX = (dis1(gen) == 0 ? 0 : 995);
            direction[indexObj] = randomX == 0 ? 1 : -1;
            time_obj2[indexObj] = dis_obj2(gen) + direction[direction.size()-1]*200; 
            float randomY = j * laneHeight-50; 
            //create traffic pos
            TrafficLight_pos.push_back(j*laneHeight-25);      

            if (type_obj == "birds")
            {
                objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                if (ObjInLane[indexObj]==2)
                    objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY+50, speedDis(gen),direction[indexObj]));

            }
            else
            if (type_obj == "dinosaurs")
            {
                objects.emplace_back(std::make_shared<CDINOSAUR>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));       
                 if (ObjInLane[indexObj]==2)
                    objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY+50, speedDis(gen),direction[indexObj]));

            }
            else
            if (type_obj == "birds2")
            {
                objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));                
                if (ObjInLane[indexObj]==2)
                    objects.emplace_back(std::make_shared<CDINOSAUR>(window.getSize().x, randomX, randomY+50, speedDis(gen),direction[indexObj]));
            }
            indexObj++;        
        }
        if(abs(j)%2==0) //mons tile 
            maps.emplace_back(window.getSize().x,j*laneHeight,"mons");      
        if (abs(j)%2 == 1) //map tile 
        {
            maps.emplace_back(window.getSize().x,j*laneHeight,"people");      
            if (globalObstacles)
            {        
                int numFrames = 7;
                std::uniform_int_distribution<int> dist(1, numFrames);
                std::uniform_int_distribution<int> dist2(4, 5);
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
}   
CGAME::CGAME(sf::RenderWindow& window) : window(&window)
{
        timeAppear = 10;
        isPress = false;
        view = window.getDefaultView();
        newGameMainView = view;
        threshold = 200; 
        stopGame = false;
        level = 1;
        numLanes = window.getSize().y / laneHeight;
        int totalLanes = numLanes+40;
        secondObjCreated.assign(totalLanes*2,false);
        speed_lane.assign(totalLanes*2, 0.0f);
        time_obj2.assign(totalLanes*2, 0.0f);
        ObjInLane.assign(totalLanes*2, 1);
        isSecond.assign(totalLanes*2,false);
        isDraw.assign(totalLanes*2,true);
        direction.assign(totalLanes, 1);
        GenObj(window);
}
CGAME::~CGAME() {
    delete window;

}

void CGAME::drawGame(float& realTime) 
{
    if (window) {
            for (auto tile:maps)
            {
                tile.draw(*window);
            }
            for (auto obstacle:currentObs)
            {
                if (obstacle.get_Position().x >= 0 && obstacle.get_Position().x<=1000)
                    obstacle.draw(*window);
            }
            if (cn.getState())
                cn.draw(*window);
            for (int i = 0;i<currentObjects.size();i++)
            {
                if (drag.state != "fire" && abs(currentObjects[i]->direction) == 1)
                    currentObjects[i]->draw(*window);
                else if (currentObjects[i]->get_Position().y != drag.mY-25 && currentObjects[i]->get_Position().y != drag.mY+25 && abs(currentObjects[i]->direction) == 1)
                    currentObjects[i]->draw(*window);
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
    setFinish(false);
    // other variables specific to game state
    // Clear vectors and reset their sizes
    direction.clear();
    secondObjCreated.clear();
    speed_lane.clear();
    time_obj2.clear();
    ObjInLane.clear();
    isSecond.clear();
    isDraw.clear();
    maps.clear();
    std::cout<<"clear map done"<<std::endl;
    obstacles.clear();
    currentObs.clear();
    objects.clear();
    currentObjects.clear();
    TrafficLight_pos.clear();    
    numLanes = window->getSize().y / laneHeight;
    int totalLanes = numLanes +40;
    secondObjCreated.assign(totalLanes * 2, false);
    direction.assign(totalLanes, 1);
    speed_lane.assign(totalLanes, 0.0f);
    time_obj2.assign(totalLanes, 0.0f);
    ObjInLane.assign(totalLanes, 1);
    isSecond.assign(totalLanes, false);
    isDraw.assign(totalLanes, true);
    
    timeAppear = 10;
    realTimeClock.restart();
    cn.reset();
    // Re-generate game objects
    if(typePlay == "newGame")
    {
        currentObs.clear();
        GenObj(*window);
        for (auto obstacle : obstacles){
            sf::Vector2f obsPos = obstacle.get_Position();
            if (obsPos.y >= -100 && obsPos.y <= 800)
                currentObs.push_back(obstacle);
        }
        for (auto& object : objects){
            sf::Vector2f objPos = object->get_Position();
            if (objPos.y >= -100 && objPos.y <= 800)
                currentObjects.push_back(object);
        }
        
    }
    else if (typePlay == "loadGame")
    {
        currentObs.clear();
        loadGame("save.txt",*window);
        for (auto obstacle : obstacles){
            sf::Vector2f obsPos = obstacle.get_Position();
            if (obsPos.y >= (cn.get_Position().y - 700) && obsPos.y <= (cn.get_Position().y + 700)){
                currentObs.push_back(obstacle);
            }
        }
        for (auto& object : objects){
            sf::Vector2f objPos = object->get_Position();
            if (objPos.y >= (cn.get_Position().y - 700) && objPos.y <= (cn.get_Position().y + 700))
                currentObjects.push_back(object);
        }   
    }
    std::cout<<"Reset done"<<std::endl;
}
void CGAME::exitGame(std::thread& thread) {
    stopGame = true;
    if (thread.joinable()) {
        thread.join();
    }
}

void CGAME::startGame(sf::RenderWindow& window) {   
    if (!stopGame) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && isPress==false) {
            isPress = true;
            saveGame("save.txt");
        }

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
        for (int i =0;i<currentObs.size();i++)
        {
            if (currentObs[i].get_Position().y > (playerPosition.y +200) &&!currentObs.empty()) {
                currentObs.erase(currentObs.begin()+i);
            } 
        }
        for (auto& object : objects){
            sf::Vector2f objPos = object->get_Position();
            if (objPos.y >= (cn.get_Position().y - 700) && objPos.y <= (cn.get_Position().y + 200))
                currentObjects.push_back(object);
        }
    }
    //level
    if (!endless){
        finishLine = 800 - numLanes*laneHeight;
        if (playerPosition.y < finishLine - level*multiplier){
            if (level < 5) {
                std::cout << "level " << level++ << " completed\n";
                setFinish(true);
            }
            else if (level == 6) {
                stopGame = true;
                cn.Died();
                std::cout << "gg\n";
                level = 1;
                setFinish(true);
            }
        }
    }
    window.setView(view);
}

void CGAME::loadGame(const std::string& filename,sf::RenderWindow& window) {
    
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error when open file for loading game state" << std::endl;
    }

    float centerX, centerY, sizeX, sizeY;
    file >> centerX >> centerY;
    file >> sizeX >> sizeY;
   
//  lane 
    for (int i = -40; i < numLanes; ++i) {
        if(abs(i)%2==0) //mons tile 
            maps.emplace_back(window.getSize().x,i*laneHeight,"mons");      
        if (abs(i)%2 == 1) //map tile 
        {
            maps.emplace_back(window.getSize().x,i*laneHeight,"people");    
        }
    }
    int objInLane_size;
    file >> objInLane_size;
    for(int i = 0 ;i< objInLane_size;i++)
    {
            int tempSecondObjCreated;
            int tempisSecond;
            int tempisDraw;
            int direct;
            file >> ObjInLane[i]
                >> speed_lane[i] 
                >> direct
                >> time_obj2[i]
                >> tempSecondObjCreated  
                >> tempisSecond
                >> tempisDraw;
            direction[i] = direct;
            secondObjCreated[i] = (tempSecondObjCreated != 0);
            isSecond[i] = (tempisSecond!=0);
            isDraw[i] = (tempisDraw!=0);
    }
    //  objects
    int sizeObj;
    file >> sizeObj;
    std::cout<<"load obj begin"<<std::endl;
    for (int i =0;i< sizeObj ;i++) {
        std::string objectType;
        file >> objectType;
        float x,y,speed;
        int direction;
        file >> x >> y >> speed >> direction;
        if (objectType == "birds") {
            objects.push_back(std::make_shared<CBIRD>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "dinosaurs")
        {
            objects.push_back(std::make_shared<CDINOSAUR>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "birds2")
        {
            objects.push_back(std::make_shared<CBIRD2>(window.getSize().x, 0, y,speed,direction));
        }
    }
    std::cout<<"load obj done";
    int obsSize;
    file >> obsSize;
    std::string typeObs;
    for (int i  = 0;i<obsSize;i++) {
        int x,y;
        file >> typeObs >> x >> y;
        obstacles.emplace_back(window.getSize().x,x,y,typeObs);

    }
    float pos;
    int trafficSize;
    file >>trafficSize;
    for(int i =0;i<trafficSize;i++) {
        file >> pos;
        TrafficLight_pos.push_back(pos);
    }
    int X,Y;
    file >> X >> Y;
    cn.set_Position(X,Y);
    view.setCenter(centerX, centerY);
    view.setSize(sizeX, sizeY);
    file.close();
    std::cout << "Game state loaded from " << filename << std::endl;
}

void CGAME::saveGame(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error open file for saving game " << std::endl;
        return;
    }

    file << view.getCenter().x << " " << view.getCenter().y << std::endl; 
    file << view.getSize().x << " " << view.getSize().y << std::endl; 
    file <<ObjInLane.size()<<std::endl;
    // Save lane 
    for (int i = 0; i < ObjInLane.size(); ++i) {
        file << ObjInLane[i] << " "
             << speed_lane[i] << " "
             << direction[i] << " "
             << time_obj2[i] << " "
             << secondObjCreated[i] << " "
             << isSecond[i] << " "
             << isDraw[i] << std::endl;
    }
    //  objects
    file << objects.size()<<std::endl;
    for (const auto& obj : objects) {
        file << obj->serialize() << std::endl;
    }
    //obstacles
    file << obstacles.size()<<std::endl;
    for (const auto& obstacle : obstacles) {
        file << obstacle.typeTile << " " << obstacle.get_Position().x<< " " << obstacle.get_Position().y << std::endl;
    }

    //  TrafficLight 
    file << TrafficLight_pos.size();
    for (const auto& pos : TrafficLight_pos) {
        file << pos << " ";
    }
    file << std::endl;
    //cn pos
    file << cn.get_Position().x << " "<< cn.get_Position().y;

    file.close();
    std::cout << "Game state saved to " << filename << std::endl;
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
    for (int i =0;i<objects.size();i++) {
        if(abs(objects[i]->direction) == 1)
        {
            objects[i]->UpdateFrame(deltaTime);
            moveCooldown_animal = 0.1f;
        }
        
    }
    drag.UpdateFrame(deltaTime);
}
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
    for (int i =0;i<objects.size();i++) {
        if(abs(objects[i]->direction) == 1)
        {
            if(cn.getState())
            {
                // if (drag.state != "fire" || (objects[i]->get_Position().y != drag.mY-25 && objects[i]->get_Position().y != drag.mY+25))
                //     if (CollisionManager::checkCollisionAnimal(cn, *objects[i]))
                //     {
                //         stopGame=true;
                //         cn.Died();
                //     }
            }
            if (drag.state != "fire")
                objects[i]->Move();
            else if (objects[i]->get_Position().y != drag.mY-25 && objects[i]->get_Position().y != drag.mY+25)
                objects[i]->Move();
        }
        
    }
}

bool CGAME::checkwindow(){
    if (window) return true;
    return false;
}

void CGAME::setEndless(bool mode){
    endless = mode;
}

bool CGAME::getEndless(){
    return endless;
}

void CGAME::setLevel(int l){
    level = l;
}

int CGAME::getLevel(){
    return level;
}