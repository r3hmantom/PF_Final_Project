#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
using namespace std;

// images
bool loadTexture(sf::Texture& texture, const string& filename);
void centerSpriteOrigins(sf::Sprite& sprite1, sf::Sprite& sprite2);


// file handling
void saveGameState(const GameState& state, const string& filename, bool saveEmptyState);
bool loadGameState(GameState& state, const string& filename);

// grid
bool isValidGridPosition(int x, int y);

// player
bool checkForWin(const int board[ROWS][COLS], bool& player1Won);