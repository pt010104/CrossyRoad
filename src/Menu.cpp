#include "Menu.h"

bool mainMenuDrawn = false;
bool pausedMenuDrawn = false;

Menu::Menu(const sf::Font& font, sf::RenderWindow& window) : window(window), m_font(font)
{
    obstaclesOn = true;
    soundOn = true;
    endlessOn = true;
    isSettingPannel = false;
    if (!playTextture.loadFromFile("Assets/Menu/PlayButton.png")) {
        std::cerr << "Failed to load play button image." << std::endl;
    }
    if (!saveTextture.loadFromFile("Assets/Menu/loadSave.png")) {
        std::cerr << "Failed to load load save image." << std::endl;
    }
    if (!endlessTexture.loadFromFile("Assets/Menu/modeEndless.png")) {
        std::cerr << "Failed to load mode endless image." << std::endl;
    }
    if (!classicTexture.loadFromFile("Assets/Menu/modeClassic.png")) {
        std::cerr << "Failed to load mode classic image." << std::endl;
    }
    if (!settingTextture.loadFromFile("Assets/Menu/settingsButton.png")) {
        std::cerr << "Failed to load settings button image." << std::endl;
    }
    if (!soundTexture.loadFromFile("Assets/Menu/soundButton.png")) {
        std::cerr << "Failed to load sound button image." << std::endl;
    }
    if (!obstaclesTexture.loadFromFile("Assets/Menu/obstaclesButton.png")) {
        std::cerr << "Failed to load obstacles button image." << std::endl;
    }
    if (!settingPannelTexture.loadFromFile("Assets/Menu/Settings.png")) {
        std::cerr << "Failed to load settings image." << std::endl;
    }

    mainMenuCameraView = window.getDefaultView();
    Button playButton;
    playButton.sprite.setTexture(playTextture);
    playButton.sprite.setPosition(382, 658);
    playButton.name = "play";
    playButton.onClick = []() {
        std::cout << "Play button clicked!\n";
    };

    Button loadSave;
    loadSave.sprite.setTexture(saveTextture);
    loadSave.sprite.setPosition(397, 333);
    loadSave.name = "loadSave";
    loadSave.onClick = []() {
        std::cout << "Loadsave button clicked!\n";
    };   

    Button modeEndless;
    modeEndless.sprite.setTexture(endlessTexture);
    modeEndless.sprite.setPosition(406, 385);
    modeEndless.name = "modeEndless";
    modeEndless.onClick = []() {
        std::cout << "Endless mode button clicked!\n";
    }; 

    Button modeClassic;
    modeClassic.isDraw = false;
    modeClassic.sprite.setTexture(classicTexture);
    modeClassic.sprite.setPosition(406, 385);
    modeClassic.name = "modeClassic";
    modeClassic.onClick = []() {
        std::cout << "Classic mode button clicked!\n";
    };

    Button settingsButton;
    settingsButton.sprite.setTexture(settingTextture);
    settingsButton.sprite.setPosition(400, 430);
    settingsButton.name = "settingsButton";
    settingsButton.onClick = []() {
        std::cout << "settings button clicked!\n";
    };   

    Button settingPannel;
    settingPannel.sprite.setTexture(settingPannelTexture);
    settingPannel.sprite.setPosition(294,327);
    settingPannel.name = "settingPannel";
    settingPannel.onClick = []() {
        std::cout << "Sound button clicked!\n";
    };   
    settingPannel.isDraw = false;

    Button sound;
    Button obstacles;

    sound.sprite.setTexture(soundTexture);
    sound.sprite.setPosition(294+33,327+256);
    sound.name = "soundButton";
    sound.onClick = []() {
        std::cout << "Sound button clicked!\n";
    };   
    sound.isDraw = false;

    obstacles.sprite.setTexture(obstaclesTexture);
    obstacles.sprite.setPosition(294+213,327+256);
    obstacles.name = "obstaclesButton";
    obstacles.onClick = []() {
        std::cout << "Obstacles button clicked!\n";
    };  
    obstacles.isDraw = false;

    mainMenuButtons.push_back(playButton);
    mainMenuButtons.push_back(loadSave);
    mainMenuButtons.push_back(modeEndless);
    mainMenuButtons.push_back(modeClassic);
    mainMenuButtons.push_back(settingsButton);
    mainMenuButtons.push_back(settingPannel);
    mainMenuButtons.push_back(sound);
    mainMenuButtons.push_back(obstacles);
}

void Menu::setFont(const std::string& fontPath) {
    if (!m_font.loadFromFile(fontPath)) {
        // Handle font loading error
    }
}

void Menu::renderMainMenu() {
    // if (!mainMenuDrawn) {
        window.setView(mainMenuCameraView);

        if (!menuTexture.loadFromFile("Assets/Menu/MenuGame.png")) {
            std::cerr << "Failed to load main menu image." << std::endl;
        }

        menuSprite.setTexture(menuTexture);
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u menuSize = menuTexture.getSize();

        float xPos = (windowSize.x - menuSize.x) / 2.0f;
        float yPos = (windowSize.y - menuSize.y) / 2.0f;

        menuSprite.setPosition(xPos, yPos);
        window.draw(menuSprite);
        mainMenuDrawn = true;
    for (auto& button : mainMenuButtons) {
        if(button.isDraw)
            window.draw(button.sprite);
    }
    if (isSettingPannel && soundOn == false)
    {
        sf::RectangleShape rectangle(sf::Vector2f(164.0f, 164.0f)); 
        rectangle.setFillColor(sf::Color(0, 0, 0, 150)); // 50/255
        rectangle.setPosition(294+30, 327+78); 
        window.draw(rectangle);
    }
    if (isSettingPannel && obstaclesOn == false)
    {
        sf::RectangleShape rectangle(sf::Vector2f(168.0f, 164.0f)); 
        rectangle.setFillColor(sf::Color(0, 0, 0, 150)); // 50/255
        rectangle.setPosition(294+215, 327+78); 
        window.draw(rectangle);
    }
}

void Menu::renderPausedMenu() {
    // currentView.setCenter(viewX, viewY);
    // window.setView(currentView);
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 155));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    window.draw(backgroundShape);
}
std::string Menu::handleInputMainMenu(bool isClicked) {

    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    int clickedButtonIndex = -1;
    if (!isSettingPannel)
    {
        clickedButtonIndex = checkButtonClick(mainMenuButtons,mousePos);
        if (clickedButtonIndex != -1) {
            mainMenuButtons[clickedButtonIndex].onHover(); 
        }
        if (clickedButtonIndex == -1) {
            for (auto& button : mainMenuButtons) {
                button.onUnhover(); 
            }
        }
        if(mainMenuButtons[clickedButtonIndex].name == "loadSave")
            typePlay = "loadGame";
        else if(mainMenuButtons[clickedButtonIndex].name == "play")
            typePlay = "newGame";
    }
    else 
        displaySettings(mainMenuButtons,mousePos,isClicked);
    return clickedButtonIndex != -1 ? mainMenuButtons[clickedButtonIndex].name : "";

}
void Menu::displaySettings(std::vector<Button>& buttons,const sf::Vector2f& mousePosition,bool isClicked) {
    int indexEndless;
    int indexClassic;
    int indexPannel;
    int indexSound;
    int indexObs;
    isSettingPannel = true;
    bool isClose = true;

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].onUnhover();
        if (buttons[i].name == "settingPannel")
        {
            buttons[i].isDraw = true;
            indexPannel = i;
        }
        else
        if (buttons[i].name == "soundButton")
        {
            indexSound = i;
            buttons[i].isDraw = true;
        }
        else
        if (buttons[i].name == "obstaclesButton")
        {
            indexObs = i;
            buttons[i].isDraw = true;
        }
        else if (buttons[i].name == "modeEndless")
        {
            if (buttons[i].isDraw){
                endlessOn = true;
            }
            indexEndless = i;
            buttons[i].isDraw = false;
        }
        else if (buttons[i].name == "modeClassic")
        {
            if (buttons[i].isDraw){
                endlessOn = false;
            }
            indexClassic = i;
            buttons[i].isDraw = false;
        }
        else
            buttons[i].isDraw = false;
    }
    //check hover
    if (buttons[indexSound].sprite.getGlobalBounds().contains(mousePosition))
        buttons[indexSound].onHover(); 
    if (buttons[indexObs].sprite.getGlobalBounds().contains(mousePosition))
        buttons[indexObs].onHover(); 
    //check click
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (isClicked) {
            if (buttons[i].sprite.getGlobalBounds().contains(mousePosition) && buttons[i].isDraw) 
            {
                if (buttons[i].name == "soundButton")
                {
                    if (soundOn == true) //turn off sound
                    {
                        globalSound.stop();
                        soundOn = false;
                    }
                    else 
                    {
                        globalSound.play();
                        soundOn = true;
                    }
                }
                if (buttons[i].name == "obstaclesButton")
                    {
                        if (obstaclesOn == true) //turn off obs
                        {
                            obstaclesOn = false;
                            globalObstacles = false;
                        }
                        else 
                        {
                            globalObstacles = true;
                            obstaclesOn = true;
                        }
                    }
                else
                if (buttons[i].name == "settingPannel" || buttons[i].name == "settingsButton")
                    isClose =false;
            }
        }
        else isClose = false;
    }
    if (isClose) 
    {
        buttons[indexPannel].isDraw = false;
        buttons[indexObs].isDraw = false;
        buttons[indexSound].isDraw = false;
        isSettingPannel = false;
        for (size_t i = 0; i < buttons.size(); ++i) {
            if (i!=indexPannel && i!=indexObs && i!=indexSound)
                buttons[i].isDraw = true;
        }
        if (endlessOn){
            buttons[indexClassic].isDraw = false;
        }
        else {
            buttons[indexEndless].isDraw = false;
        }
    }
}

void Menu::handleInputPausedMenu() {

}

int Menu::checkButtonClick(const std::vector<Button>& buttons, const sf::Vector2f& mousePosition) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].sprite.getGlobalBounds().contains(mousePosition) && buttons[i].isDraw) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Menu::resetMainMenu() {
    mainMenuDrawn = false;
}

void Button::onHover(){
    sprite.setColor(sf::Color(198, 236, 0, 250)); 
}
void Button::onUnhover(){
    sprite.setColor(sf::Color(255, 255, 255, 255)); 
}

void Menu::pressEndless(){
    for (auto& button : mainMenuButtons){
        if (button.name == "modeEndless"){
            button.isDraw = false;
        }
        else if (button.name == "modeClassic"){
            button.isDraw = true;
        }
    }
}

void Menu::pressClassic(){
    for (auto& button : mainMenuButtons){
        if (button.name == "modeClassic"){
            button.isDraw = false;
        }
        else if (button.name == "modeEndless"){
            button.isDraw = true;
        }
    }
}