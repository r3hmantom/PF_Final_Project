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
void moveRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Left
void moveLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Top
void moveTop(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Bottom
void moveBottom(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// MOVING BEADS DIAGONALLY

// Upper Right
void upperRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Upper Left
void upperLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Lower Right
void lowerRight(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// Lower Left
void lowerLeft(int curPosition[][defaultColsH], int curR, int curC, int EMPTY, bool& moveMade);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------



