const int defaultColsH = 5;

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


// BOARD FUNCTIONS

// Initializing Board
void initBoard(int board[][defaultColsH], int ROWS, int COLS, int PLAYER1, int PLAYER2, int EMPTY);

// Displaying Board on console
void displayBoard(int board[][defaultColsH], int ROWS, int COLS);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// MOVING BEADS IN AXIS

// Right
void moveRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Left
void moveLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Top
void moveTop(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Bottom
void moveBottom(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// MOVING BEADS DIAGONALLY

// Upper Right
void upperRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Upper Left
void upperLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Lower Right
void lowerRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// Lower Left
void lowerLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------



