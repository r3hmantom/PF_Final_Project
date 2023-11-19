#include <iostream>
using namespace std;

// Board Dimensions
const int ROWS = 5;
const int COLS = 5;

// Player States
const int EMPTY = 0;
const int PLAYER1 = 1;
const int PLAYER2 = 2;

void initBoard(int board[ROWS][COLS]) {

	// INITIALIZING PLAYER 1

	// Initializing first two rows
	for (int i = 0; i < COLS; i++) { // looping over all columns
		for (int j = 0; j <= 1; j++) // looping over only first two rows
			board[j][i] = PLAYER1;
	}
	// Initializing two columns on third row left
	for (int i = 0; i < 2; i++) { // looping over two columns
		for (int j = 2; j < 3; j++)
			board[j][i] = PLAYER1;
	}

	board[2][2] = EMPTY;

	// INITIALIZING PLAYER 2

	// Initializing two columns on third row right
	for (int i = 3; i < COLS; i++) {
		for (int j = 2; j < 3; j++)
			board[j][i] = PLAYER2;
	}

	// Initializing last two rows
	for (int i = 0; i < COLS; i++)
		for (int j = 3; j < ROWS; j++)
			board[j][i] = PLAYER2;
}



int main() {
	int board[ROWS][COLS];


	 

	cout << "Hello world" << endl;

	return 0;
}