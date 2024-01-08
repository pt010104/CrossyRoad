#include "CGAME.h"
CGAME::CGAME() : window(nullptr) {
}
int CGAME::getNumBirds() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<double> prob;
    //Set probability for number of birds
    switch (level) {
        case 1:
            prob = {0.7, 0.3}; // 70% ra 1, 30% ra 2
            break;
        case 2:
            prob = {0.5, 0.5}; 
            break;
        case 3:
            prob = {0.3, 0.7}; 
            break;
        case 4:
            prob = {0.2, 0.8}; 
        case 5:
            prob = {0.0, 1}; 
            break;
    }

    std::discrete_distribution<> numBirdsDis(prob.begin(), prob.end());

    return numBirdsDis(gen) + 1; 
}
void CGAME::GenObj(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0,1); //obj1 appears at x=0 or 955
    std::uniform_real_distribution<> dis_obj2(400, 700); //obj2 will appear if obj1 across it
    std::uniform_real_distribution<> speedDis(4.0f, 6.5f); 
    std::uniform_int_distribution<> numBirdsDis(1, 2); 
    std::uniform_int_distribution<> randObj(0, 9); 
    std::uniform_int_distribution<> numAnimal(1,2); 

    int indexObj=0;
    int levelIndexLane = 52 - 3 - static_cast<int>(std::floor(level * 1.5));
    float multiplierSpeed = 1;
    if(!endless)
        multiplierSpeed = 1 + static_cast<float>(level)/9.5;
    std::vector<std::string> nameTile = {"people_map"+std::to_string(level),"mons_map"+std::to_string(level)};
    // random obj
    for (int j = -100; j < numLanes; j++) {
        if (abs(j)%2==0) { //mons case
            if(endless)
                ObjInLane[indexObj] = numBirdsDis(gen);  

            else ObjInLane[indexObj] = getNumBirds();
            speed_lane[indexObj] = speedDis(gen)*multiplierSpeed;
            int numAnimalInLane = numAnimal(gen) + 1;
            float randomX = (dis1(gen) == 0 ? 0 : 1005);
            direction[indexObj] = randomX == 0 ? 1 : -1;
            time_obj2[indexObj] = dis_obj2(gen) + direction[direction.size()-1]*200; 
            float randomY = j * laneHeight-50; 

            //create traffic pos
            int firstAnimal = numAnimalInLane;
            float previousTime = 2;
            if ((lanePos.size()-1 >= levelIndexLane && !endless) || endless)
            {
                TrafficLight_pos.push_back(j*laneHeight-25);    
                //lane pos
                while (numAnimalInLane > 0)
                {
                    std::string type_obj = object_rand[randObj(gen)]; 
                    if (type_obj == "birds")
                    {
                       
                        objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;
                            
                        if (ObjInLane[indexObj]==2 && numAnimalInLane==firstAnimal)
                            objects.emplace_back(std::make_shared<CBIRD4>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));

                    }
                    else
                    if (type_obj == "birds5")
                    {
                        objects.emplace_back(std::make_shared<CBIRD5>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;      
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR4>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));

                    }
                    else
                    if (type_obj == "birds2")
                    {
                        objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;                
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CBIRD5>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "birds3")
                    {
                        objects.emplace_back(std::make_shared<CBIRD3>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;               
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR2>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "birds4")
                    {
                        objects.emplace_back(std::make_shared<CBIRD4>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;              
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars")
                    {
                        objects.emplace_back(std::make_shared<CCAR>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;               
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CBIRD>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars2")
                    {
                        objects.emplace_back(std::make_shared<CCAR2>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;               
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR5>(window.getSize().x, randomX, randomY+80, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars3")
                    {
                        objects.emplace_back(std::make_shared<CCAR3>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;              
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR6>(window.getSize().x, randomX, randomY+80, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars4")
                    {
                        objects.emplace_back(std::make_shared<CCAR4>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;         
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR7>(window.getSize().x, randomX, randomY+80, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }  
                    if (type_obj == "cars5")
                    {
                        objects.emplace_back(std::make_shared<CCAR5>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;                  
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CBIRD3>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars6")
                    {
                        objects.emplace_back(std::make_shared<CCAR6>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;                  
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CBIRD2>(window.getSize().x, randomX, randomY+50, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    if (type_obj == "cars7")
                    {
                        objects.emplace_back(std::make_shared<CCAR7>(window.getSize().x, randomX, randomY, speed_lane[indexObj],direction[indexObj]));
                        if (numAnimalInLane!=firstAnimal)
                            objects[objects.size()-1]->timeAppear += previousTime;                  
                        if (ObjInLane[indexObj]==2)
                            objects.emplace_back(std::make_shared<CCAR4>(window.getSize().x, randomX, randomY+80, speedDis(gen)*multiplierSpeed,-direction[indexObj]));
                    }
                    numAnimalInLane--;
                    previousTime+=2;      
                }

                indexObj++;  
            }  
        }
        if(abs(j)%2==0) //mons tile 
        {
            if (lanePos.size()-1 < levelIndexLane && !endless)
            {
                maps.emplace_back(window.getSize().x,j*laneHeight,"people_map"+std::to_string(level+1)); //set wall at next level position
            }
            else
                maps.emplace_back(window.getSize().x,j*laneHeight,nameTile[1]); //0 is people, 1 is mons      
        }
        if (abs(j)%2 == 1) //map tile 
        {
            int posMidLane = j*laneHeight;
            lanePos.push_back (posMidLane);
            if (lanePos.size()-1 < levelIndexLane&& !endless)
            {
                maps.emplace_back(window.getSize().x,j*laneHeight,"people_map"+std::to_string(level+1)); //set wall at next level position
            }
            else
            {
                maps.emplace_back(window.getSize().x,j*laneHeight,nameTile[0]);      
                if (globalObstacles && j!=numLanes-1)
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
        int totalLanes = numLanes+100;
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
    if (window && !isFinished) 
    {

        for (auto tile:maps)
        {
            tile.draw(*window);
        }
        for (auto obstacle:currentObs)
        {
            obstacle.draw(*window);
        }
        if (cn.getState())
            cn.draw(*window);
        for (int i = 0;i<currentObjects.size();i++)
        {
            if (realTimeClock.getElapsedTime().asSeconds() >= currentObjects[i]->timeAppear)
            {
                if (drag.state != "fire")
                    currentObjects[i]->draw(*window);
                else if (currentObjects[i]->get_Position().y != drag.mY-25 && currentObjects[i]->get_Position().y != drag.mY+25)
                    currentObjects[i]->draw(*window);
            }
        }     
        if (realTimeClock.getElapsedTime().asSeconds() >= timeAppear && drag.state == "disap")
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
        if (realTime <= 3 && !endless)
        {
            sf::Font font;
            if (!font.loadFromFile("Assets\\Font\\PressStart2P-Regular.ttf")) 
            {
                std::cerr << "Error to load font\n";
            }
            else
            {
                sf::Text textOutline;
                textOutline.setFont(font); 
                textOutline.setString("Level " + std::to_string(level)); 
                textOutline.setCharacterSize(100); 
                textOutline.setFillColor(sf::Color::Black);  
                textOutline.setStyle(sf::Text::Bold);

                sf::Text text;
                text.setFont(font); 
                text.setString("Level " + std::to_string(level)); 
                text.setCharacterSize(100); 
                text.setFillColor(sf::Color::White);  
                text.setStyle(sf::Text::Bold);

                sf::Vector2f position(200, 400);
                text.setPosition(position);

                float outlineThickness = 2.0f;

                for (int x = -outlineThickness; x <= outlineThickness; x++) {
                    for (int y = -outlineThickness; y <= outlineThickness; y++) {
                        if (x != 0 || y != 0) {
                            textOutline.setPosition(position.x + x, position.y + y);
                            window->draw(textOutline);
                        }
                    }
                }

                window->draw(text); 
            }
        }
        if (endless)
        {
            sf::Font font;
            if (!font.loadFromFile("Assets\\Font\\PressStart2P-Regular.ttf")) 
            {
                std::cerr << "Error to load font\n";
            }
            
            sf::Text text;
            text.setFont(font); 
            text.setString("Score:" + std::to_string(Score)); 
            text.setCharacterSize(30); 
            text.setFillColor(sf::Color::White);  
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::White);
            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(1);

            sf::Vector2f position(400, view.getCenter().y-350);
            text.setPosition(position);

            window->draw(text); 
        }
        countDown = false;
        if (typePlay == "loadGame" && realTime < 3) //countdown loadgame
        {
            countDown = true;
            sf::Font font;
            if (!font.loadFromFile("Assets\\Font\\PressStart2P-Regular.ttf")) 
            {
                std::cerr << "Error to load font\n";
            }

            sf::RectangleShape rectangle(sf::Vector2f(1000,800)); 
            rectangle.setFillColor(sf::Color(0, 0, 0, 150)); // 50/255
            rectangle.setPosition(0, view.getCenter().y-400); 
            window->draw(rectangle);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(static_cast<int>(3-realTime+1)));
            text.setCharacterSize(50); 
            text.setFillColor(sf::Color::White);
            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(1);
            text.setPosition(400, view.getCenter().y); 
            window->draw(text);
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
    viewX = 500;
    viewY = 400;
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
    obstacles.clear();
    currentObs.clear();
    objects.clear();
    currentObjects.clear();
    TrafficLight_pos.clear();    
    lanePos.clear();

    numLanes = window->getSize().y / laneHeight;
    int totalLanes = numLanes + 100;
    secondObjCreated.assign(totalLanes*2, false);
    direction.assign(totalLanes*2, 1);
    speed_lane.assign(totalLanes*2, 0.0f);
    time_obj2.assign(totalLanes*2, 0.0f);
    ObjInLane.assign(totalLanes*2, 1);
    isSecond.assign(totalLanes*2, false);
    isDraw.assign(totalLanes*2, true);
    
    timeAppear = 10;
    realTimeClock.restart();
    cn.reset();
    drag.reset();
    dead = false;
    Score = 0;
    // Re-generate game objects
    if (typePlay == "loadGame" && !endless)
        typePlay = "newGame";
    if(typePlay == "newGame")
    {
        
        currentObs.clear();
        if(level!=6)
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
        countDown = true;
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
    stopGame = false;
}
void CGAME::exitGame(std::thread& thread) {
    stopGame = true;
    if (thread.joinable()) {
        thread.join();
    }
}

void CGAME::startGame(sf::RenderWindow& window) {   
    if (!stopGame && !specialAnim && !isFinished && !countDown) {
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
    if (playerPosition.y < view.getCenter().y - threshold && !specialAnim && !isFinished) {
        viewX = view.getCenter().x;
        viewY = playerPosition.y - 200;
        view.setCenter(viewX, viewY);
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
    if (!endless && !specialAnim && !isFinished){
        finishLine = 3;
        if (playerPosition.y <= lanePos[lanePos.size()-1-finishLine-static_cast<int>(std::floor(level * 1.5))]){
            setSpecial(true);
            isPress = true;
            std::cout << "special animation triggered\n";
        }
    }
    if (!endless && isFinished)
    {     
        std::cout << "advance level\n";
            if (level < 5) {
                std::cout << "level " << level++ << " completed\n";   
                resetGame();
                window.setView(view);
                isPress = false;
                setFinish(false);
            }
            else if (level == 5) {
                level++;
                isPress = true;
                std::cout << "gg\n";
                resetGame();
                _sleep(500);
                isPress = false;
                setFinish(false);
            }
    }
    if (!specialAnim && !isFinished) 
        window.setView(view);
    //Score
    if (endless && playerPosition.y <= lanePos[lanePos.size()-2-Score]+40)
        Score++;
}

void CGAME::loadGame(const std::string& filename,sf::RenderWindow& window) {
    
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error when open file for loading game state" << std::endl;
    }

    float centerX, centerY, sizeX, sizeY;
    file >> centerX >> centerY;
    file >> sizeX >> sizeY;
    viewX = centerX;
    viewY = centerY;
   
//  lane 
    file >> endless >> level;

    int levelIndexLane = 52 - 3 - static_cast<int>(std::floor(level * 1.5));
    std::vector<std::string> nameTile = {"people_map"+std::to_string(level),"mons_map"+std::to_string(level)};

    for (int i = -100; i < numLanes; ++i) {
        if(abs(i)%2==0) //mons tile 
        {
            if (lanePos.size()-1 < levelIndexLane && !endless)
            {
                maps.emplace_back(window.getSize().x,i*laneHeight,"people_map"+std::to_string(level+1)); //set wall at next level position
            }
            else
                maps.emplace_back(window.getSize().x,i*laneHeight,nameTile[1]); //0 is people, 1 is mons      
        }
        if (abs(i)%2 == 1) //people tile 
        {
            int posMidLane = i*laneHeight;
            lanePos.push_back (posMidLane);
            if (lanePos.size()-1 < levelIndexLane && !endless)
            {
                maps.emplace_back(window.getSize().x,i*laneHeight,"people_map"+std::to_string(level+1)); //set wall at next level position
            }
            else
            {
                maps.emplace_back(window.getSize().x,i*laneHeight,nameTile[0]);      
            }
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
        float time_appear;
        file >> x >> y >> speed >> direction >> time_appear;
        if (objectType == "birds") {
            objects.push_back(std::make_shared<CBIRD>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "birds2")
        {
            objects.push_back(std::make_shared<CBIRD2>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "birds3")
        {
            objects.push_back(std::make_shared<CBIRD3>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "birds4")
        {
            objects.push_back(std::make_shared<CBIRD4>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "birds5")
        {
            objects.push_back(std::make_shared<CBIRD5>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars")
        {
            objects.push_back(std::make_shared<CCAR>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars2")
        {
            objects.push_back(std::make_shared<CCAR2>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars3")
        {
            objects.push_back(std::make_shared<CCAR3>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars4")
        {
            objects.push_back(std::make_shared<CCAR4>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars5")
        {
            objects.push_back(std::make_shared<CCAR5>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars6")
        {
            objects.push_back(std::make_shared<CCAR6>(window.getSize().x, 0, y,speed,direction));
        }
        else
        if (objectType == "cars7")
        {
            objects.push_back(std::make_shared<CCAR7>(window.getSize().x, 0, y,speed,direction));
        }
        objects[i]->timeAppear = time_appear;
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

    file << endless << " " << level <<std::endl;

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
    if(cn.getState() && !isFinished)
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
    if (!isFinished)
    {
        deltaTime = dt;
        moveCooldown_animal -= deltaTime;
        if(cn.getState())
        {
            cn.UpdateFrame(deltaTime);
        }
        for (int i =0;i<objects.size();i++) {
            if(abs(objects[i]->direction) == 1 && !isFinished)
            {
                objects[i]->UpdateFrame(deltaTime);
                moveCooldown_animal = 0.1f;
            }
            
        }
        drag.UpdateFrame(deltaTime);
    }

}
    void CGAME::updatePosVehicle() {
            // Move CTRUCK and CCAR
}

void CGAME::updatePosAnimal() {
    if(!isFinished && !countDown)
    {
        for (int i =0;i<objects.size();i++) {
            if(abs(objects[i]->direction) == 1)
            {
                if(cn.getState())
                {
                    if (drag.state != "fire" || (objects[i]->get_Position().y != drag.mY-25 && objects[i]->get_Position().y != drag.mY+25))
                        if (CollisionManager::checkCollisionAnimal(cn, *objects[i]))
                        {
                            stopGame=true;
                            cn.Died();
                            deathAnim = true;
                            dead = true;
                        }
                }
                if (drag.state != "fire")
                    objects[i]->Move();
                else if (objects[i]->get_Position().y != drag.mY-25 && objects[i]->get_Position().y != drag.mY+25)
                    objects[i]->Move();
            }
        
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

void CGAME::finishAnimation(){
    
}