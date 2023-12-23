#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

// Define the structure for a button
struct Button {
    sf::Sprite sprite;
    std::function<void()> onClick; // Function to execute when clicked
};

extern bool mainMenuDrawn;
extern bool pausedMenuDrawn;

class Menu {
private:
    sf::RenderWindow& window;
    sf::View mainMenuCameraView;
    sf::Texture menuTexture;
    sf::Sprite menuSprite;
    std::vector<Button> mainMenuButtons;
    std::vector<Button> pausedMenuButtons;
    sf::Font m_font;

    int checkButtonClick(const std::vector<Button>& buttons, const sf::Vector2f& mousePosition);
public:
    Menu(const sf::Font& font, sf::RenderWindow& window);

    void setFont(const std::string& fontPath);

    void renderMainMenu();
    void renderPausedMenu();
    // Add functions for other menus (scoreMenu, settingsMenu, etc.)

    void handleInputMainMenu();
    void handleInputPausedMenu();
    // Add functions for handling input in other menus

    void resetMainMenu();
};
