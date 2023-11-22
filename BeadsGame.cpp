#include <iostream>
#include "Beads.h"

using namespace std;

// Board Dimensions
const int ROWS = 5;
const int COLS = 5;

// Player States
const int EMPTY = 0;
const int PLAYER1 = 1;
const int PLAYER2 = -1;

// Game State
const int WIN_STATE = 0; 



//void moveBeadRight()


int main() {
	int board[ROWS][COLS];
	initBoard(board, ROWS, COLS, PLAYER1, PLAYER2, EMPTY);
	displayBoard(board, ROWS, COLS);



	return 0;
}