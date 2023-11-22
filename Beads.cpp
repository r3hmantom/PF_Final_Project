#include <iostream>
using namespace std;

// Default Variables
const int defaultColsF = 5;

// --------------------------------------------------------------------------------------

// BOARD FUNCTIONS

// Initializing Board
void initBoard(int board[][defaultColsF],int ROWS, int COLS,int PLAYER1,int PLAYER2,int EMPTY) {

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
// Displaying Board on console
void displayBoard(int board[][defaultColsF], int ROWS, int COLS) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
}

// --------------------------------------------------------------------------------------

// MOVING BEADS IN AXIS

// Right
void moveRight(int curPosition[][defaultColsF], int curR, int curC , int EMPTY) {

	if (curPosition[curR][curC + 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Left
void moveLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR][curC - 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Top
void moveTop(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR + 1][curC] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR + 1][curC] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Bottom
void moveBottom(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR - 1][curC] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// --------------------------------------------------------------------------------------

// MOVING BEADS DIAGONALLY

// Upper Right
void upperRight(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR - 1][curC + 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR - 1][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Upper Left
void upperLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR - 1][curC - 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR - 1][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Lower Right
void lowerRight(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR + 1][curC + 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR + 1][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Lower Left
void loweLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	if (curPosition[curR + 1][curC - 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}



// --------------------------------------------------------------------------------------

// KILLING BEADS

// Player 1 Bead
