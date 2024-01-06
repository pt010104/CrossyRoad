#include "Menu.h"

bool mainMenuDrawn = false;
bool pausedMenuDrawn = false;

Menu::Menu(const sf::Font& font, sf::RenderWindow& window) : window(window), m_font(font)
{
    obstaclesOn = true;
    soundOn = true;
    endlessOn = true;
    isSettingPannel = false;
    isHighScore = false;
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
    if (!highScoreTexture.loadFromFile("Assets/Menu/highScore.png")) {
        std::cerr << "Failed to load mode highScoreTexture image." << std::endl;
    }

    //paused menu buttons
    if (!resumeTexture.loadFromFile("Assets/Menu/resumeButton.png")) {
        std::cerr << "Failed to load resume button image." << std::endl;
    }
    if (!retryTexture.loadFromFile("Assets/Menu/retryButton.png")) {
        std::cerr << "Failed to load retry button image." << std::endl;
    }
    if (!returnMenuTexture.loadFromFile("Assets/Menu/menuButton.png")) {
        std::cerr << "Failed to load menu button image." << std::endl;
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

    Button highScore;
    highScore.sprite.setTexture(highScoreTexture);
    highScore.sprite.setPosition(400,478);
    highScore.name = "highScoreButton";
    highScore.onClick = []() {
        std::cout << "highScore button clicked!\n";
    };

    //paused menu buttons
    Button resume;
    resume.sprite.setTexture(resumeTexture);
    resume.sprite.setPosition(327, 490);
    resume.name = "resume";
    resume.onClick = []() {
        std::cout << "resume button clicked!\n";
    }; 

    Button retry;
    retry.sprite.setTexture(retryTexture);
    retry.sprite.setPosition(369, 366);
    retry.name = "retry";
    retry.onClick = []() {
        std::cout << "retry button clicked!\n";
    };

    Button returnMenu;
    returnMenu.sprite.setTexture(returnMenuTexture);
    returnMenu.sprite.setPosition(550, 366);
    returnMenu.name = "returnMenu";
    returnMenu.onClick = []() {
        std::cout << "return menu button clicked!\n";
    }; 

    mainMenuButtons.push_back(playButton);
    mainMenuButtons.push_back(highScore);
    mainMenuButtons.push_back(loadSave);
    mainMenuButtons.push_back(modeEndless);
    mainMenuButtons.push_back(modeClassic);
    mainMenuButtons.push_back(settingsButton);
    mainMenuButtons.push_back(settingPannel);
    mainMenuButtons.push_back(sound);
    mainMenuButtons.push_back(obstacles);

    pausedMenuButtons.push_back(resume);
    pausedMenuButtons.push_back(retry);
    pausedMenuButtons.push_back(returnMenu);    
}

void Menu::setFont(const std::string& fontPath) {
    if (!m_font.loadFromFile(fontPath)) {
        // Handle font loading error
    }
}

void Menu::renderMainMenu() {
    // if (!mainMenuDrawn) {
        window.setView(mainMenuCameraView);
        if (!isHighScore)
        {
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
        else 
        {
            sf::Sprite spriteHighScoreBoard;
            sf::Texture texture;
            if (!texture.loadFromFile("Assets\\Menu\\ScoreBoard.png")) {
            }
            spriteHighScoreBoard.setTexture(texture); 
            window.draw(spriteHighScoreBoard);
            
            sf::Font font;
            if (!font.loadFromFile("Assets\\Font\\PressStart2P-Regular.ttf")) {
            }

            std::fstream fileScore("Score.txt");
            std::vector<int> scores;
            int score;
            if (!fileScore) {
                std::cerr << "Could not open score file" << std::endl;
            }
            int length = 0;
            while (fileScore >> score) {
                length++;
                scores.push_back(score);
            }
            fileScore.close();
            std::sort(scores.begin(), scores.end(), std::greater<int>());
            std::vector<sf::Text> scoreTexts;
            length = std::min(5,length);

            for (int i = 0; i < length; ++i) {
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(scores[i]));
                text.setCharacterSize(25); 
                text.setFillColor(sf::Color::White);
                text.setOutlineColor(sf::Color::Black);
                text.setOutlineThickness(1);
                text.setPosition(480, 355 + 44 * i); 
                window.draw(text);
            }
        }
}

void Menu::renderPausedMenu() {
    // currentView.setCenter(viewX, viewY);
    // window.setView(currentView);
    sf::RectangleShape backgroundShape(sf::Vector2f(1000.0f, 800.0f));
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 155));
    backgroundShape.setPosition(viewX - 500, viewY - 400);
    window.draw(backgroundShape);

    if (!pausedTexture.loadFromFile("Assets/Menu/pausedMenu.png")) {
        std::cerr << "Failed to load paused menu image." << std::endl;
    }
    pausedSprite.setTexture(pausedTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u pausedSize = pausedTexture.getSize();

    float xPos = (windowSize.x - pausedSize.x) / 2.0f;
    float yPos = (windowSize.y - pausedSize.y) / 2.0f;

    pausedSprite.setPosition(xPos, yPos + viewY - 400);
    window.draw(pausedSprite);

    for (auto& button : pausedMenuButtons) {
        if (button.name == "resume")
            button.sprite.setPosition(327, 490 + viewY - 400);
        else if (button.name == "retry")
            button.sprite.setPosition(369, 366 + viewY - 400);
        else if (button.name == "returnMenu")
            button.sprite.setPosition(550, 366 + viewY - 400);
    }
    for (auto& button : pausedMenuButtons) {
        if(button.isDraw)
            window.draw(button.sprite);
    }
}

std::string Menu::handleInputMainMenu(bool isClicked) {

    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    int clickedButtonIndex = -1;
    if (!isSettingPannel && !isHighScore)
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
    else if(isSettingPannel)
        displaySettings(mainMenuButtons,mousePos,isClicked);
    else if(isHighScore)
        highScoreDisplay(mainMenuButtons,mousePos,isClicked);
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

void Menu::highScoreDisplay(std::vector<Button>& buttons,const sf::Vector2f& mousePosition,bool isClicked){
    if (isClicked)
        isHighScore = false;
    
}

std::string Menu::handleInputPausedMenu(bool isClicked) {
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    int clickedButtonIndex = -1;
    clickedButtonIndex = checkButtonClick(pausedMenuButtons,mousePos);
        if (clickedButtonIndex != -1) {
            pausedMenuButtons[clickedButtonIndex].onHover(); 
        }
        if (clickedButtonIndex == -1) {
            for (auto& button : pausedMenuButtons) {
                button.onUnhover(); 
            }
        }
    return clickedButtonIndex != -1 ? pausedMenuButtons[clickedButtonIndex].name : "";
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

void Menu::winGame(){
    sf::Texture texture;
    if (!texture.loadFromFile("Assets\\Menu\\winGame.png")) {
    }

    sf::Sprite spriteWin;
    spriteWin.setTexture(texture);

    window.draw(spriteWin); 
}