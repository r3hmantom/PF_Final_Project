#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std;

void showMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected);
void handleMenuInput(sf::RenderWindow& window, const sf::Event& event, bool& startGame, bool& exitGame, bool& resumeGameSelected);
void showAndHandleMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected);