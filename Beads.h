const int defaultColsH = 5;

// BOARD

// Initializing Board
void initBoard(int board[][defaultColsH], int ROWS, int COLS, int PLAYER1, int PLAYER2, int EMPTY);

// Displaying Board
void displayBoard(int board[][defaultColsH], int ROWS, int COLS);

// --------------------------------------------------------------------------------------

void moveRight(int curPosition[][defaultColsH], int curR, int curC, int nextPosition[][defaultColsH], int nextR, int nextC);


