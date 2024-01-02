#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

// Define the structure for a button
class Button {
public:
    sf::Sprite sprite;
    std::function<void()> onClick;
    std::string name;
    Button() = default;
    void onHover();
    void onUnhover();
};

extern bool mainMenuDrawn;
extern bool pausedMenuDrawn;

class Menu {
private:
    sf::RenderWindow& window;
    sf::View mainMenuCameraView;
    sf::Texture menuTexture;
    sf::Texture playTextture;
    sf::Texture saveTextture;
    sf::Texture settingTextture;
    sf::Texture soundTexture;
    sf::Texture obstaclesTexture;
    sf::Texture settingPannelTexture;
    bool soundOn;
    bool obstaclesOn;

    sf::Sprite menuSprite;
    std::vector<Button> mainMenuButtons;
    std::vector<Button> pausedMenuButtons;
    sf::Font m_font;


    int checkButtonClick(const std::vector<Button>& buttons, const sf::Vector2f& mousePosition);

public:
    bool isSettingPannel;
    Menu(const sf::Font& font, sf::RenderWindow& window);

    void setFont(const std::string& fontPath);

    void renderMainMenu();
    void renderPausedMenu();
    // Add functions for other menus (scoreMenu, settingsMenu, etc.)

    std::string handleInputMainMenu();
    void displaySettings(std::vector<Button>& buttons,const sf::Vector2f& mousePosition);
    void handleInputPausedMenu();
    // Add functions for handling input in other menus

    void resetMainMenu();
};
