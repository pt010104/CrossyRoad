#include "Menu.h"

bool mainMenuDrawn = false;
bool pausedMenuDrawn = false;

Menu::Menu(const sf::Font& font, sf::RenderWindow& window) : window(window), m_font(font) {
    mainMenuCameraView = window.getDefaultView();
    Button playButton;
    playButton.sprite.setTexture(menuTexture);
    playButton.sprite.setPosition(100, 100);
    playButton.onClick = []() {
        std::cout << "Play button clicked!\n";
    };
    mainMenuButtons.push_back(playButton);

    // Initialize buttons for other menus similarly...
}

void Menu::setFont(const std::string& fontPath) {
    if (!m_font.loadFromFile(fontPath)) {
        // Handle font loading error
    }
}

void Menu::renderMainMenu() {
    // if (!mainMenuDrawn) {
        window.setView(mainMenuCameraView);

        if (!menuTexture.loadFromFile("Assets/Menu/TmpMainMenu.png")) {
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

        // for (auto& button : mainMenuButtons) {
        //     // Adjust button positions relative to the menu position if needed
        //     sf::Sprite& buttonSprite = button.sprite;
        //     buttonSprite.setPosition(xPos + button.offset.x, yPos + button.offset.y);
        //     window.draw(buttonSprite);
        // }
    // }
}

void Menu::renderPausedMenu() {
    // if (!pausedMenuDrawn) {

    //     if (!menuTexture.loadFromFile("Assets/Menu/TmpPausedMenu.png")) {
    //         std::cerr << "Failed to load paused menu image." << std::endl;
    //     }

    //     menuSprite.setTexture(menuTexture);
    //     sf::Vector2u windowSize = window.getSize();
    //     sf::Vector2u menuSize = menuTexture.getSize();

    //     float xPos = (windowSize.x - menuSize.x) / 2.0f;
    //     float yPos = (windowSize.y - menuSize.y) / 2.0f;

    //     menuSprite.setPosition(xPos, yPos);
    //     window.draw(menuSprite);

    //     pausedMenuDrawn = true;

    //     // for (auto& button : mainMenuButtons) {
    //     //     // Adjust button positions relative to the menu position if needed
    //     //     sf::Sprite& buttonSprite = button.sprite;
    //     //     buttonSprite.setPosition(xPos + button.offset.x, yPos + button.offset.y);
    //     //     window.draw(buttonSprite);
    //     // }

    //     window.display();
    // }
}

void Menu::handleInputMainMenu() {
    int clickedButtonIndex = checkButtonClick(mainMenuButtons, sf::Vector2f(sf::Mouse::getPosition(window)));
    if (clickedButtonIndex != -1) {
        mainMenuButtons[clickedButtonIndex].onClick();
    }
}

void Menu::handleInputPausedMenu() {

}

int Menu::checkButtonClick(const std::vector<Button>& buttons, const sf::Vector2f& mousePosition) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].sprite.getGlobalBounds().contains(mousePosition)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Menu::resetMainMenu() {
    mainMenuDrawn = false;
}