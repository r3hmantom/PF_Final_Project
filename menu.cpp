#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std;

const int MENU_ITEM_COUNT = 3;
const char* MENU_TEXTS[MENU_ITEM_COUNT] = { "Start Game", "Resume Game", "Exit Game" };
const sf::Vector2f MENU_POSITIONS[MENU_ITEM_COUNT] = { sf::Vector2f(100, 200), sf::Vector2f(100, 300), sf::Vector2f(100, 400) };
const int MENU_TEXT_SIZE = 50;

sf::Font font;



sf::Text createMenuItemText(const sf::RenderWindow& window, const string& text, float verticalOffset) {
    if (!font.loadFromFile("assets/font.ttf")) {
        cerr << "Error loading font" << endl;
    }
    sf::Text menuItemText;
    menuItemText.setFont(font);
    menuItemText.setString(text);
    menuItemText.setCharacterSize(MENU_TEXT_SIZE);
    menuItemText.setFillColor(sf::Color::White);

    // Calculate center position
    sf::FloatRect textRect = menuItemText.getLocalBounds();
    menuItemText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    menuItemText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, verticalOffset));

    return menuItemText;
}

void showMenu(sf::RenderWindow& window, sf::Text menuTexts[MENU_ITEM_COUNT]) {

    // Create a rectangle that covers the entire window
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(TERMINAL_COLOR);

    // Draw the background
    window.draw(background);

    for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
        window.draw(menuTexts[i]);
    }
}

bool isMouseOverText(const sf::RenderWindow& window, const sf::Text& text) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return text.getGlobalBounds().contains(mousePos);
}

void updateCursorForMenu(sf::RenderWindow& window, const sf::Text menuTexts[MENU_ITEM_COUNT], bool menuActive) {
    static sf::Cursor handCursor, arrowCursor;
    static bool cursorsLoaded = false;

    if (!cursorsLoaded) {
        if (!handCursor.loadFromSystem(sf::Cursor::Hand) || !arrowCursor.loadFromSystem(sf::Cursor::Arrow)) {
            cerr << "Error loading cursors" << endl;
            return;
        }
        cursorsLoaded = true;
    }

    if (menuActive) {
        bool isMouseOverAnyText = false;
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            if (isMouseOverText(window, menuTexts[i])) {
                isMouseOverAnyText = true;
                break;
            }
        }

        if (isMouseOverAnyText) {
            window.setMouseCursor(handCursor);
        }
        else {
            window.setMouseCursor(arrowCursor);
        }
    }
    else {
        window.setMouseCursor(arrowCursor);
    }
}

void handleMenuInput(sf::RenderWindow& window, const sf::Event& event, sf::Text menuTexts[MENU_ITEM_COUNT], bool& startGame, bool& exitGame, bool& resumeGameSelected) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOverText(window, menuTexts[0])) {
            startGame = true;
        }
        else if (isMouseOverText(window, menuTexts[1])) {
            resumeGameSelected = true;
        }
        else if (isMouseOverText(window, menuTexts[2])) {
            exitGame = true;
        }
    }
}
void showAndHandleMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected) {
    sf::Text menuTexts[MENU_ITEM_COUNT];

    bool menuActive = true; // Flag to indicate if the menu is active

    float verticalSpacing = 100.0f;  // Vertical spacing between menu items
    float startY = window.getSize().y / 2.0f - verticalSpacing * (MENU_ITEM_COUNT / 2.0f);

    for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
        menuTexts[i] = createMenuItemText(window, MENU_TEXTS[i], startY + i * verticalSpacing);
    }

    // Cursor objects for different cursor types
    sf::Cursor handCursor, arrowCursor;
    if (!handCursor.loadFromSystem(sf::Cursor::Hand) || !arrowCursor.loadFromSystem(sf::Cursor::Arrow)) {
        cerr << "Error loading cursors" << endl;
        return;
    }

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        handleMenuInput(window, event, menuTexts, startGame, exitGame, resumeGameSelected);

        if (startGame || resumeGameSelected || exitGame) {
            menuActive = false; // Menu is no longer active
            break; // Break out of the event loop
        }

        // Check if mouse is over any text
        bool isMouseOverAnyText = false;
        for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
            if (isMouseOverText(window, menuTexts[i])) {
                isMouseOverAnyText = true;
                break;
            }
        }

        // Change cursor based on mouse position
        if (isMouseOverAnyText) {
            window.setMouseCursor(handCursor);
        } else {
            window.setMouseCursor(arrowCursor);
        }
    }
    updateCursorForMenu(window, menuTexts, menuActive);
    if (menuActive) {
        window.clear();
        showMenu(window, menuTexts);
        window.display();
    }
\
}
