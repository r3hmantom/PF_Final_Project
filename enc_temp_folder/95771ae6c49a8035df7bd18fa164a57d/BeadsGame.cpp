#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Beads.h"

using namespace std;

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
const sf::Color TERMINAL_COLOR(209, 190, 160);  
const sf::Color TEXT_COLOR_PLAYER_2(25 ,31, 202);
const sf::Color TEXT_COLOR_PLAYER_1(216, 38, 55);
const sf::Color TEXT_COLOR(0, 0, 0);






struct GameState {
	int board[ROWS][COLS];
	bool isPlayer1Turn;
};


// Global Variables
bool isPlayer1Turn = true;

// Function Declarations
// -----------------
bool loadTexture(sf::Texture& texture, const string& filename);
void centerSpriteOrigins(sf::Sprite& sprite1, sf::Sprite& sprite2);
bool loadAndSetupSprites(sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Texture& beadTexture1, sf::Texture& beadTexture2);
bool loadAndSetupBoard(sf::Sprite& boardSprite, sf::Texture& boardTexture, sf::RenderWindow& window);
// -----------------
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol, bool& isPlayer1Turn, GameState& gameState, int horizontalOffset);
void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol, bool& isPlayer1Turn);

// -----------------
void drawBeads(sf::RenderWindow& window, const sf::Sprite& beadSprite1, const sf::Sprite& beadSprite2, int board[ROWS][COLS], int selectedRow, int selectedCol);

// -----------------
bool isMoveRight(int gridX, int gridY, int selectedCol, int selectedRow) {
	return gridY == selectedRow && (gridX == selectedCol + 1 || gridX == selectedCol + 2);
}
bool isMoveLeft(int gridX, int gridY, int selectedCol, int selectedRow) {
	return gridY == selectedRow && (gridX == selectedCol - 1 || gridX == selectedCol - 2);
}
bool isMoveDown(int gridX, int gridY, int selectedCol, int selectedRow) {
	return gridX == selectedCol && (gridY == selectedRow + 1 || gridY == selectedRow + 2);
}
bool isMoveUp(int gridX, int gridY, int selectedCol, int selectedRow) {
	return gridX == selectedCol && (gridY == selectedRow - 1 || gridY == selectedRow - 2);
}
bool isMoveUpperRight(int gridX, int gridY, int selectedCol, int selectedRow) {
	return((gridX == selectedCol + 1 && gridY == selectedRow - 1) ||
		(gridX == selectedCol + 2 && gridY == selectedRow - 2)) && ((selectedRow + selectedCol) % 2 == 0);
}
bool isMoveUpperLeft(int gridX, int gridY, int selectedCol, int selectedRow) {
	return ((gridX == selectedCol - 1 && gridY == selectedRow - 1) ||
		(gridX == selectedCol - 2 && gridY == selectedRow - 2)) && ((selectedRow + selectedCol) % 2 == 0);
}
bool isMoveLowerRight(int gridX, int gridY, int selectedCol, int selectedRow) {
	return ((gridX == selectedCol + 1 && gridY == selectedRow + 1) ||
		(gridX == selectedCol + 2 && gridY == selectedRow + 2)) && ((selectedRow + selectedCol) % 2 == 0);
}
bool isMoveLowerLeft(int gridX, int gridY, int selectedCol, int selectedRow) {
	return ((gridX == selectedCol - 1 && gridY == selectedRow + 1) ||
		(gridX == selectedCol - 2 && gridY == selectedRow + 2)) && ((selectedRow + selectedCol) % 2 == 0);
}
// -----------------
void runGameLoop(sf::RenderWindow& window, GameState& gameState, sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Sprite& boardSprite);
bool initializeWindow(sf::RenderWindow& window);

// -----------------
void displayWinningMessage(sf::RenderWindow& window, bool player1Won) {
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	// Create a semi-transparent overlay
	sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Black color with 150 alpha (semi-transparent)

	sf::Text text;
	text.setFont(font);
	text.setString(player1Won ? "Player 1 Wins!" : "Player 2 Wins!");
	text.setCharacterSize(140); // Increased size

	if (player1Won) {
		text.setFillColor(TEXT_COLOR_PLAYER_1);
	}
	else {
		text.setFillColor(TEXT_COLOR_PLAYER_2);
	}
	text.setStyle(sf::Text::Bold); // Making the text bold

	// Get the bounding box of the text
	sf::FloatRect textRect = text.getLocalBounds();
	// Center the text origin
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	// Set the position of the text to be in the center of the window
	text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50));

	// Draw overlay first, then the text
	window.draw(overlay);
	window.draw(text);
}

bool checkForWin(const int board[ROWS][COLS], bool& player1Won) {
	bool player1Exists = false;
	bool player2Exists = false;

	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (board[row][col] == PLAYER1) {
				player1Exists = true;
			}
			else if (board[row][col] == PLAYER2) {
				player2Exists = true;
			}
		}
	}

	if (!player1Exists) {
		player1Won = false; // PLAYER2 wins
		return true;
	}
	if (!player2Exists) {
		player1Won = true; // PLAYER1 wins
		return true;
	}

	return false; // No winner yet
}
void displayPlayerTurn(sf::RenderWindow& window, bool isPlayer1Turn) {
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(isPlayer1Turn ? "Player 1's Turn" : "Player 2's Turn");
	text.setCharacterSize(60);
	if (isPlayer1Turn) {
		text.setFillColor(TEXT_COLOR_PLAYER_1);
	}
	else {
		text.setFillColor(TEXT_COLOR_PLAYER_2);
	}

	// Get the bounding box of the text
	sf::FloatRect textRect = text.getLocalBounds();
	// Center the text origin horizontally
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);

	// Set the position of the text to be centered horizontally
	float centerX = window.getSize().x / 2.0f;
	text.setPosition(centerX, TURN_TOP_OFFSET);

	window.draw(text);
}


// -----------------
// MENU FUNCTIONS
// Function Declarations

void showMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected) {
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	// Start Game Text
	sf::Text startGameText("Start Game", font, 50);
	startGameText.setPosition(100, 200);
	startGameText.setFillColor(sf::Color::White);

	// Resume Game Text
	sf::Text resumeGameText("Resume Game", font, 50);
	resumeGameText.setPosition(100, 300);
	resumeGameText.setFillColor(sf::Color::White);

	// Exit Game Text
	sf::Text exitGameText("Exit Game", font, 50);
	exitGameText.setPosition(100, 400);
	exitGameText.setFillColor(sf::Color::White);

	window.draw(startGameText);
	window.draw(resumeGameText);
	window.draw(exitGameText);
}
void handleMenuInput(sf::RenderWindow& window, const sf::Event& event, bool& startGame, bool& exitGame, bool& resumeGameSelected) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// Assuming text bounds are 200x50 for each option
		sf::FloatRect startGameBounds(100, 200, 200, 50);
		sf::FloatRect resumeGameBounds(100, 300, 200, 50);
		sf::FloatRect exitGameBounds(100, 400, 200, 50);

		if (startGameBounds.contains(mousePos)) {
			startGame = true;
		}
		else if (resumeGameBounds.contains(mousePos)) {
			resumeGameSelected = true;
		}
		else if (exitGameBounds.contains(mousePos)) {
			exitGame = true;
		}
	}
}
void showAndHandleMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		handleMenuInput(window, event, startGame, exitGame, resumeGameSelected);
	}

	window.clear();
	showMenu(window, startGame, exitGame, resumeGameSelected);
	window.display();
}
void saveGameState(const GameState& state, const string& filename) {
	ofstream file(filename, ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<const char*>(&state), sizeof(GameState));
	}
	file.close();
}
bool loadGameState(GameState& state, const string& filename) {
	ifstream file(filename, ios::binary);
	if (file.is_open() && file.read(reinterpret_cast<char*>(&state), sizeof(GameState))) {
		file.close();
		return true;
	}
	return false;
}




int main() {
	// Initializing Window
	sf::RenderWindow window;
	if (!initializeWindow(window)) {
		return EXIT_FAILURE;
	}

	// Setting up Game Assets
	sf::Sprite beadSprite1, beadSprite2;
	sf::Texture beadTexture1, beadTexture2;
	if (!loadAndSetupSprites(beadSprite1, beadSprite2, beadTexture1, beadTexture2)) {
		cerr << "Failed to load and setup sprites." << endl;
		return EXIT_FAILURE;
	}

	sf::Sprite boardSprite;
	sf::Texture boardTexture;
	if (!loadAndSetupBoard(boardSprite, boardTexture, window)) {
		cerr << "Failed to setup board sprite." << endl;
		return EXIT_FAILURE;
	}

	// Menu Variables
	bool startGame = false;
	bool exitGame = false;
	bool resumeGameSelected = false;

	// Game State Variable
	GameState gameState;

	// Show and Handle Menu
	while (window.isOpen() && !startGame && !exitGame && !resumeGameSelected) {
		showAndHandleMenu(window, startGame, exitGame, resumeGameSelected);
	}

	// Initialize a New Game if Required
	if (startGame) {
		initBoard(gameState.board, ROWS, COLS, PLAYER1, PLAYER2, EMPTY);
		gameState.isPlayer1Turn = true;
	}

	// Resume Game Logic
	else if (resumeGameSelected) {
		if (!loadGameState(gameState, "savegame.dat")) {
			// No saved game found or error reading file, start a new game
			initBoard(gameState.board, ROWS, COLS, PLAYER1, PLAYER2, EMPTY);
			gameState.isPlayer1Turn = true;
		}
	}

	// Exit Game Logic
	if (exitGame) {
		return EXIT_SUCCESS;
	}

	// Run Game Loop if Start Game or Resume Game is Selected
	if (startGame || resumeGameSelected) {
		while (window.isOpen()) {
			runGameLoop(window, gameState, beadSprite1, beadSprite2, boardSprite);
		}
	}

	return EXIT_SUCCESS;
}



// Main Functions
bool initializeWindow(sf::RenderWindow& window) {
	// Get the desktop mode to determine the screen resolution
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window with the desktop resolution
	// sf::Style::Default allows the window to be resized and keeps the taskbar visible
	window.create(sf::VideoMode(desktop.width, desktop.height), "12 Beads Game", sf::Style::Default);

	// Maximize the window
	window.setPosition(sf::Vector2i(0, 0));
	window.setSize(sf::Vector2u(desktop.width, desktop.height));

	return window.isOpen();
}
void runGameLoop(sf::RenderWindow& window, GameState& gameState, sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Sprite& boardSprite) {
	int selectedRow = -1, selectedCol = -1;
	bool gameEnded = false;
	bool player1Won = false;
	// Calculate the total width of the bead layout
	int totalBeadsWidth = COLS * BEAD_SIZE;
	// Calculate the horizontal offset to center the beads
	int horizontalOffset = (window.getSize().x - totalBeadsWidth) / 2;


	while (window.isOpen()) {
		// Handle input and update game state
		processInput(window, gameState.board, selectedRow, selectedCol, gameState.isPlayer1Turn, gameState, horizontalOffset);

		// Clear the window
		window.clear(TERMINAL_COLOR);

		// Draw the board
		window.draw(boardSprite);

		// Check for win condition
		if (!gameEnded && checkForWin(gameState.board, player1Won)) {
			gameEnded = true;
		}

		// Draw beads
		drawBeads(window, beadSprite1, beadSprite2, gameState.board, selectedRow, selectedCol);

		// Display player turn or winning message
		if (!gameEnded) {
			displayPlayerTurn(window, gameState.isPlayer1Turn);
		}
		else {
			displayWinningMessage(window, player1Won);
		}

		// Display the window contents
		window.display();
	}
}



// Handling sprite images
bool loadTexture(sf::Texture& texture, const string& filename) {
	if (!texture.loadFromFile(filename)) {
		cerr << "Error loading " << filename << endl;
		return false;
	}
	return true;
}
void centerSpriteOrigins(sf::Sprite& sprite1, sf::Sprite& sprite2) {
	sprite1.setOrigin(sprite1.getTexture()->getSize().x / 2, sprite1.getTexture()->getSize().y / 2);
	sprite2.setOrigin(sprite2.getTexture()->getSize().x / 2, sprite2.getTexture()->getSize().y / 2);
}
bool loadAndSetupSprites(sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Texture& beadTexture1, sf::Texture& beadTexture2) {
	
	if (!loadTexture(beadTexture1, "bead1.png") || !loadTexture(beadTexture2, "bead2.png")) {
		return false;
	}

	beadSprite1.setTexture(beadTexture1);
	beadSprite2.setTexture(beadTexture2);
	centerSpriteOrigins(beadSprite1, beadSprite2);
	return true;
}
bool loadAndSetupBoard(sf::Sprite& boardSprite, sf::Texture& boardTexture, sf::RenderWindow& window) {
    if (!loadTexture(boardTexture, "board.png")) {
        cerr << "Error loading board texture" << endl;
        return false;
    }

    boardSprite.setTexture(boardTexture);

    // Get the size of the sprite
    sf::FloatRect spriteSize = boardSprite.getGlobalBounds();

    // Calculate the horizontal center position
    float centerX = (window.getSize().x - spriteSize.width) / 2.0f;

    // Set the position of the sprite to be centered horizontally
    boardSprite.setPosition(centerX, BOARD_TOP_OFFSET + BOARD_IMG_OFFSET);
    
    return true;
}


// Handling selection an inputs
bool isValidGridPosition(int x, int y) {
	return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol, bool& isPlayer1Turn, GameState& gameState, int horizontalOffset) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			saveGameState(gameState, "savegame.dat");  // Save game before closing
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			// Adjust gridX calculation to account for the horizontal offset
			int gridX = ((event.mouseButton.x - horizontalOffset) / BEAD_SIZE);
			int gridY = ((event.mouseButton.y - BOARD_TOP_OFFSET) / BEAD_SIZE);

			if (isValidGridPosition(gridX, gridY)) {
				handleSelectionAndMovement(board, gridX, gridY, selectedRow, selectedCol, isPlayer1Turn);
			}
		}
	}
}

void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol, bool& isPlayer1Turn) {
	static bool moveMade = false; // Track if a valid move has been made

	// If a bead is already selected and the new click is on another bead
	if ((selectedRow != -1 && selectedCol != -1) && (gridX != selectedCol || gridY != selectedRow)) {
		if ((isPlayer1Turn && board[gridY][gridX] == PLAYER1) || (!isPlayer1Turn && board[gridY][gridX] == PLAYER2)) {
			// Select the new bead
			selectedRow = gridY;
			selectedCol = gridX;
			moveMade = false; // Reset moveMade for the new selection
			return; // Exit the function here to avoid further processing in this turn
		}
	}

	// If no bead is currently selected or the same bead is clicked again
	if (selectedRow == -1 || (selectedRow == gridY && selectedCol == gridX)) {
		// Selecting a bead if it belongs to the current player
		if ((isPlayer1Turn && board[gridY][gridX] == PLAYER1) || (!isPlayer1Turn && board[gridY][gridX] == PLAYER2)) {
			selectedRow = gridY;
			selectedCol = gridX;
			moveMade = false; // Reset moveMade for a new selection
		}
	}
	else {
		// Check for valid moves based on the selected bead
		if (isMoveRight(gridX, gridY, selectedCol, selectedRow)) {
			moveRight(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveLeft(gridX, gridY, selectedCol, selectedRow)) {
			moveLeft(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveDown(gridX, gridY, selectedCol, selectedRow)) {
			moveBottom(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveUp(gridX, gridY, selectedCol, selectedRow)) {
			moveTop(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveUpperRight(gridX, gridY, selectedCol, selectedRow)) {
			upperRight(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveUpperLeft(gridX, gridY, selectedCol, selectedRow)) {
			upperLeft(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveLowerRight(gridX, gridY, selectedCol, selectedRow)) {
			lowerRight(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveLowerLeft(gridX, gridY, selectedCol, selectedRow)) {
			lowerLeft(board, selectedRow, selectedCol, EMPTY, moveMade);
		}

		// Reset selection
		selectedRow = -1;
		selectedCol = -1;

		// Switch turns if a valid move was made
		if (moveMade) {
			isPlayer1Turn = !isPlayer1Turn;
			moveMade = false;
		}

	}
}


// Drawing Beads
void drawBead(sf::RenderWindow& window, const sf::Sprite& sprite, int row, int col, int selectedRow, int selectedCol, float& rotationAngle, int horizontalOffset) {
	sf::Sprite tempSprite = sprite; // Copy to modify position and rotation
	tempSprite.setPosition(col * BEAD_SIZE + BEAD_SIZE / 2 + horizontalOffset, row * BEAD_SIZE + BEAD_SIZE / 2 + BOARD_TOP_OFFSET);
	tempSprite.setRotation((row == selectedRow && col == selectedCol) ? (rotationAngle += 0.6f) : 0.0f);
	window.draw(tempSprite);
}

void drawBeads(sf::RenderWindow& window, const sf::Sprite& beadSprite1, const sf::Sprite& beadSprite2, int board[ROWS][COLS], int selectedRow, int selectedCol) {
	static float rotationAngle = 0.0f;
	// Calculate the total width of the bead layout
	int totalBeadsWidth = COLS * BEAD_SIZE;
	// Calculate the horizontal offset to center the beads
	int horizontalOffset = (window.getSize().x - totalBeadsWidth) / 2;


	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == EMPTY) continue;

			const sf::Sprite& currentSprite = (board[i][j] == PLAYER1) ? beadSprite1 : beadSprite2;
			drawBead(window, currentSprite, i, j, selectedRow, selectedCol, rotationAngle, horizontalOffset);
		}
	}
}