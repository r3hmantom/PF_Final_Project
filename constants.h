#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants
const int ROWS = 5;
const int COLS = 5;
const int EMPTY = 0;
const int PLAYER1 = 1;
const int PLAYER2 = -1;
const int BEAD_PIC_SIZE = 150;
const int BEAD_SIZE = BEAD_PIC_SIZE + 10;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int BOARD_TOP_OFFSET = 100;
const int BOARD_LEFT_OFFSET = 100;
const int BOARD_IMG_OFFSET = 25;
const int TURN_TOP_OFFSET = 50;
const int TURN_LEFT_OFFSET = 400;

// Player

struct GameState {
	int board[ROWS][COLS];
	bool IS_PLAYER1_TURN;
};


// STRING CONSTANTS
 
const string  PLAYER_1_NAME_TEXT = "Player 1";
const string  PLAYER_1_TURN_TEXT = "Player 1's Turn";
const string  PLAYER_2_NAME_TEXT = "Player 2";
const string  PLAYER_2_TURN_TEXT = "Player 2's Turn";


const string START_GAME_TEXT = "Start Game";
const string RESUME_GAME_TEXT = "Resume Game";
const string EXIT_GAME_TEXT = "Exit Game";
const string GAME_TITLE = "12 Beads Game";


// Colors
const sf::Color TERMINAL_COLOR(209, 190, 160);
const sf::Color TEXT_COLOR_PLAYER_1(25, 31, 202);
const sf::Color TEXT_COLOR_PLAYER_2(216, 38, 55);
const sf::Color TEXT_COLOR(0, 0, 0);
const sf::Color TEXT_COLOR_BROWN(59, 55, 43);

#endif // CONSTANTS_H
