// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


// BOARD FUNCTIONS

// Initializing Board
void initBoard(int board[ROWS][COLS]);

// Displaying Board on console
void displayBoard(int board[ROWS][COLS]);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// MOVING BEADS IN AXIS

// Right
void moveRight(int curPosition[][COLS], int curR, int curC,  bool& moveMade);

// Left
void moveLeft(int curPosition[][COLS], int curR, int curC,  bool& moveMade);

// Top
void moveTop(int curPosition[][COLS], int curR, int curC,  bool& moveMade);

// Bottom
void moveBottom(int curPosition[][COLS], int curR, int curC, bool& moveMade);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// MOVING BEADS DIAGONALLY

// Upper Right
void upperRight(int curPosition[][COLS], int curR, int curC, bool& moveMade);

// Upper Left
void upperLeft(int curPosition[][COLS], int curR, int curC,  bool& moveMade);

// Lower Right
void lowerRight(int curPosition[][COLS], int curR, int curC,  bool& moveMade);

// Lower Left
void lowerLeft(int curPosition[][COLS], int curR, int curC,bool& moveMade);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// CHECKS FOR MOVEMENTS

bool isMoveRight(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveLeft(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveDown(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveUp(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveUpperRight(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveUpperLeft(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveLowerRight(int gridX, int gridY, int selectedCol, int selectedRow);
bool isMoveLowerLeft(int gridX, int gridY, int selectedCol, int selectedRow);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


// BOARD GUI
bool loadAndSetupBoard(sf::Sprite& boardSprite, sf::Texture& boardTexture, sf::RenderWindow& window);