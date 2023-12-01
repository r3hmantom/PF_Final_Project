#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
#include "inputs.h"
#include "beads.h"
#include "board.h"
#include "messages.h"

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
		processInput(window, gameState.board, selectedRow, selectedCol, gameState.IS_PLAYER1_TURN, gameState, horizontalOffset);

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
			displayPlayerTurn(window, gameState.IS_PLAYER1_TURN);
		}
		else {
			displayWinningMessage(window, player1Won);
		}

		// Display the window contents
		window.display();
	}
}
