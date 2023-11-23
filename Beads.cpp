#include <iostream>
using namespace std;

// Default Variables
const int defaultColsF = 5;

// --------------------------------------------------------------------------------------

// BOARD FUNCTIONS

// Initializing Board
void initBoard(int board[][defaultColsF], int ROWS, int COLS, int PLAYER1, int PLAYER2, int EMPTY) {

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
void moveRight(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position right is opposite player and two position right is empty
	// then current position is moved to/with two position right and make one position to right empty and current position empty
	if (curPosition[curR][curC + 1] == (curPosition[curR][curC] * -1) && curPosition[curR][curC + 2] == EMPTY) {
		// moving current bead to 2 position left
		curPosition[curR][curC + 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR][curC + 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}

	if (curPosition[curR][curC + 1] == EMPTY) {
		// If right  position is empty, then make current position empty and move current position to +1 on right side
		curPosition[curR][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}



}

// Left
void moveLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position left is opposite player and two position left is empty
	// then current position is moved to/with two position left and make one position to left empty and current position empty
	if (curPosition[curR][curC - 1] == (curPosition[curR][curC] * -1) && curPosition[curR][curC - 2] == EMPTY) {
		// moving current bead to 2 position left
		curPosition[curR][curC - 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR][curC - 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}


	if (curPosition[curR][curC - 1] == EMPTY) {
		// If left  position is empty, then make current position empty and move current position to 1 on left side
		curPosition[curR][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Top
void moveTop(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position top is opposite player and two position top is empty
	// then current position is moved to/with two position top and make one position to top empty and current position empty
	if (curPosition[curR - 1][curC] == (curPosition[curR][curC] * -1) && curPosition[curR - 2][curC] == EMPTY) {
		// moving current bead to 2 position top
		curPosition[curR - 2][curC] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR - 1][curC] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}


	if (curPosition[curR - 1][curC] == EMPTY) {
		// If top position is empty, then make current position empty and move current position to 1 on top side
		curPosition[curR - 1][curC] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Bottom
void moveBottom(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position bottom is opposite player and two position bottom is empty
	// then current position is moved to/with two position bottom and make one position to bottom empty and current position empty
	if (curPosition[curR + 1][curC] == (curPosition[curR][curC] * -1) && curPosition[curR + 2][curC] == EMPTY) {
		// moving current bead to 2 position top
		curPosition[curR + 2][curC] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR + 1][curC] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}




	if (curPosition[curR + 1][curC] == EMPTY) {
		// If bottom position is empty, then make current position empty and move current position to 1 on bottom side
		curPosition[curR][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// --------------------------------------------------------------------------------------

// MOVING BEADS DIAGONALLY

// Upper Right
void upperRight(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position top right is opposite player and two position top right is empty
	// then current position is moved to/with two position top and make one position to top empty and current position empty
	if (curPosition[curR - 1][curC + 1] == (curPosition[curR][curC] * -1) && curPosition[curR - 2][curC + 2] == EMPTY) {
		// moving current bead to 2 position top right
		curPosition[curR - 2][curC + 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR - 1][curC + 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}

	if (curPosition[curR - 1][curC + 1] == EMPTY) {
		// If top right position is empty, then make current position empty and move current position to +1 on top right side
		curPosition[curR - 1][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Upper Left
void upperLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {
	// If one position top left is opposite player and two position top left is empty
	// then current position is moved to/with two position top left and make one position to top left empty and current position empty
	if (curPosition[curR - 1][curC - 1] == (curPosition[curR][curC] * -1) && curPosition[curR - 2][curC - 2] == EMPTY) {
		// moving current bead to 2 position top
		curPosition[curR - 2][curC - 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR - 1][curC - 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}

	if (curPosition[curR - 1][curC - 1] == EMPTY) {
		// If top left  position is empty, then make current position empty and move current position to +1 on top left side
		curPosition[curR - 1][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Lower Right
void lowerRight(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position bottom right is opposite player and two bottom right is empty
	// then current position is moved to/with two position bottom right and make one position to bottom right empty and current position empty
	if (curPosition[curR + 1][curC + 1] == (curPosition[curR][curC] * -1) && curPosition[curR + 2][curC + 2] == EMPTY) {
		// moving current bead to 2 bottom right
		curPosition[curR + 2][curC + 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR + 1][curC + 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}

	if (curPosition[curR + 1][curC + 1] == EMPTY) {
		// If lower right  position is empty, then make current position empty and move current position to +1 on lower right side
		curPosition[curR + 1][curC + 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}

// Lower Left
void lowerLeft(int curPosition[][defaultColsF], int curR, int curC, int EMPTY) {

	// If one position lower left is opposite player and two position lower left is empty
	// then current position is moved to/with two position lower left and make one position to lower left empty and current position empty
	if (curPosition[curR + 1][curC - 1] == (curPosition[curR][curC] * -1) && curPosition[curR + 2][curC - 2] == EMPTY) {
		// moving current bead to 2 position lower left
		curPosition[curR + 2][curC - 2] = curPosition[curR][curC];
		// killing opposite person bead
		curPosition[curR + 1][curC - 1] = EMPTY;
		// setting previous position to empty
		curPosition[curR][curC] = EMPTY;
	}

	if (curPosition[curR + 1][curC - 1] == EMPTY) {
		// If lower left  position is empty, then make current position empty and move current position to 1 on lower left on right side
		curPosition[curR][curC - 1] = curPosition[curR][curC];
		curPosition[curR][curC] = EMPTY;
	}

}



// --------------------------------------------------------------------------------------

// KILLING BEADS

