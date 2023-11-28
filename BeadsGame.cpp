#include <iostream>
#include <SFML/Graphics.hpp>
#include "Beads.h"

using namespace std;

// Constants
const int ROWS = 5;
const int COLS = 5;
const int EMPTY = 0;
const int PLAYER1 = 1;
const int PLAYER2 = -1;
const int BEAD_SIZE = 160;
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1000;
const int BOARD_TOP_OFFSET = 100;
const int BOARD_LEFT_OFFSET = 100;
const int TURN_TOP_OFFSET = 10;
const int TURN_LEFT_OFFSET = 400;



// Global Variables
bool isPlayer1Turn = true;

// Function Declarations
bool loadTexture(sf::Texture& texture, const string& filename);
void centerSpriteOrigins(sf::Sprite& sprite1, sf::Sprite& sprite2);
bool loadAndSetupSprites(sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Texture& beadTexture1, sf::Texture& beadTexture2);
// -----------------
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol);
void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol);
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
	return (gridX == selectedCol + 1 && gridY == selectedRow - 1) ||
		(gridX == selectedCol + 2 && gridY == selectedRow - 2);
}
bool isMoveUpperLeft(int gridX, int gridY, int selectedCol, int selectedRow) {
	return (gridX == selectedCol - 1 && gridY == selectedRow - 1) ||
		(gridX == selectedCol - 2 && gridY == selectedRow - 2);
}
bool isMoveLowerRight(int gridX, int gridY, int selectedCol, int selectedRow) {
	return (gridX == selectedCol + 1 && gridY == selectedRow + 1) ||
		(gridX == selectedCol + 2 && gridY == selectedRow + 2);
}
bool isMoveLowerLeft(int gridX, int gridY, int selectedCol, int selectedRow) {
	return (gridX == selectedCol - 1 && gridY == selectedRow + 1) ||
		(gridX == selectedCol - 2 && gridY == selectedRow + 2);
}
// -----------------
void runGameLoop(sf::RenderWindow& window, int board[ROWS][COLS], sf::Sprite& beadSprite1, sf::Sprite& beadSprite2);
bool initializeWindow(sf::RenderWindow& window);
// -----------------
void displayWinningMessage(sf::RenderWindow& window, bool player1Won) {
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(player1Won ? "Player 1 Wins!" : "Player 2 Wins!");
	text.setCharacterSize(50); // Increased size
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold); // Making the text bold

	// Get the bounding box of the text
	sf::FloatRect textRect = text.getLocalBounds();
	// Center the text origin
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	// Set the position of the text to be in the center of the window
	text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

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
	text.setCharacterSize(30); 
	text.setFillColor(sf::Color::White);

	// Set the position of the text
	text.setPosition(TURN_LEFT_OFFSET, TURN_TOP_OFFSET); 

	window.draw(text);
}





int main() {
	// Initializing Game Board
	int board[ROWS][COLS] = {};
	initBoard(board, ROWS, COLS, PLAYER1, PLAYER2, EMPTY);

	// Creating Window
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

	// Main Game
	runGameLoop(window, board, beadSprite1, beadSprite2);

	return EXIT_SUCCESS;
}



// Main Functions
bool initializeWindow(sf::RenderWindow& window) {
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "12 Beads Game");
	return window.isOpen();
}
void runGameLoop(sf::RenderWindow& window, int board[ROWS][COLS], sf::Sprite& beadSprite1, sf::Sprite& beadSprite2) {
	int selectedRow = -1, selectedCol = -1;
	bool gameEnded = false;
	bool player1Won = false;

	while (window.isOpen()) {
		processInput(window, board, selectedRow, selectedCol);
		window.clear();

		if (!gameEnded && checkForWin(board, player1Won)) {
			gameEnded = true;
		}

		drawBeads(window, beadSprite1, beadSprite2, board, selectedRow, selectedCol);

		if (!gameEnded) {
			displayPlayerTurn(window, isPlayer1Turn); // Display whose turn it is
		}
		else {
			displayWinningMessage(window, player1Won); // Display winning message if game ended
		}

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


// Handling selection an inputs
bool isValidGridPosition(int x, int y) {
	return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int gridX = ((event.mouseButton.x - BOARD_LEFT_OFFSET) / BEAD_SIZE);
			int gridY = ((event.mouseButton.y - BOARD_TOP_OFFSET)  / BEAD_SIZE);

			if (isValidGridPosition(gridX, gridY)) {
				handleSelectionAndMovement(board, gridX, gridY, selectedRow, selectedCol);
			}
		}
	}
}
void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol) {
	static int originalRow = -1, originalCol = -1;
	static bool moveMade = false; // Track if a valid move has been made

	if (selectedRow == -1) {
		// Check if the clicked bead belongs to the current player
		if ((isPlayer1Turn && board[gridY][gridX] == PLAYER1) || (!isPlayer1Turn && board[gridY][gridX] == PLAYER2)) {
			selectedRow = gridY;
			selectedCol = gridX;
			originalRow = gridY;
			originalCol = gridX;
			moveMade = false; // Reset moveMade as this is a new selection
		}
	}
	else {
		// Perform movement based on the position clicked
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
		// Diagonal movement checks
		else if (isMoveUpperRight(gridX, gridY, selectedCol, selectedRow)) {
			if ((selectedRow + selectedCol) % 2 == 0)
				upperRight(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveUpperLeft(gridX, gridY, selectedCol, selectedRow)) {
			if ((selectedRow + selectedCol) % 2 == 0)
				upperLeft(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveLowerRight(gridX, gridY, selectedCol, selectedRow)) {
			if ((selectedRow + selectedCol) % 2 == 0)
			    lowerRight(board, selectedRow, selectedCol, EMPTY, moveMade);
		}
		else if (isMoveLowerLeft(gridX, gridY, selectedCol, selectedRow)) {
			if ((selectedRow + selectedCol) % 2 == 0)
				lowerLeft(board, selectedRow, selectedCol, EMPTY, moveMade);
		}


		// Reset selection
		selectedRow = -1;
		selectedCol = -1;

		// Only switch turns if a valid move was made
		if (moveMade) {
			isPlayer1Turn = !isPlayer1Turn;
			moveMade = false; // Reset for the next player's turn
		}

		// Reset original position for the next selection
		originalRow = -1;
		originalCol = -1;
	}
}


// Drawing Beads
void drawBead(sf::RenderWindow& window, const sf::Sprite& sprite, int row, int col, int selectedRow, int selectedCol, float& rotationAngle) {
	sf::Sprite tempSprite = sprite; // Copy to modify position and rotation
	tempSprite.setPosition(col * BEAD_SIZE + BEAD_SIZE / 2 + BOARD_LEFT_OFFSET ,  row * BEAD_SIZE + BEAD_SIZE / 2 + BOARD_TOP_OFFSET);
	tempSprite.setRotation((row == selectedRow && col == selectedCol) ? (rotationAngle += 0.6f) : 0.0f);
	window.draw(tempSprite);
}
void drawBeads(sf::RenderWindow& window, const sf::Sprite& beadSprite1, const sf::Sprite& beadSprite2, int board[ROWS][COLS], int selectedRow, int selectedCol) {
	static float rotationAngle = 0.0f;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == EMPTY) continue;

			const sf::Sprite& currentSprite = (board[i][j] == PLAYER1) ? beadSprite1 : beadSprite2;
			drawBead(window, currentSprite, i, j, selectedRow, selectedCol, rotationAngle);
		}
	}
}