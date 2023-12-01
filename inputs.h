#include <SFML/Graphics.hpp>
#include "constants.h"

// Function declarations
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol, bool& IS_PLAYER1_TURN, GameState& gameState, int horizontalOffset);
void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol, bool& IS_PLAYER1_TURN);
