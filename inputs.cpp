#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
#include "board.h"


void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol, bool& IS_PLAYER1_TURN) {
	static bool moveMade = false; // Track if a valid move has been made

	// If a bead is already selected and the new click is on another bead
	if ((selectedRow != -1 && selectedCol != -1) && (gridX != selectedCol || gridY != selectedRow)) {
		if ((IS_PLAYER1_TURN && board[gridY][gridX] == PLAYER1) || (!IS_PLAYER1_TURN && board[gridY][gridX] == PLAYER2)) {
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
		if ((IS_PLAYER1_TURN && board[gridY][gridX] == PLAYER1) || (!IS_PLAYER1_TURN && board[gridY][gridX] == PLAYER2)) {
			selectedRow = gridY;
			selectedCol = gridX;
			moveMade = false; // Reset moveMade for a new selection
		}
	}
	else {
		// Check for valid moves based on the selected bead
		if (isMoveRight(gridX, gridY, selectedCol, selectedRow)) {
			moveRight(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveLeft(gridX, gridY, selectedCol, selectedRow)) {
			moveLeft(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveDown(gridX, gridY, selectedCol, selectedRow)) {
			moveBottom(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveUp(gridX, gridY, selectedCol, selectedRow)) {
			moveTop(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveUpperRight(gridX, gridY, selectedCol, selectedRow)) {
			upperRight(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveUpperLeft(gridX, gridY, selectedCol, selectedRow)) {
			upperLeft(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveLowerRight(gridX, gridY, selectedCol, selectedRow)) {
			lowerRight(board, selectedRow, selectedCol, moveMade);
		}
		else if (isMoveLowerLeft(gridX, gridY, selectedCol, selectedRow)) {
			lowerLeft(board, selectedRow, selectedCol, moveMade);
		}

		// Reset selection
		selectedRow = -1;
		selectedCol = -1;

		// Switch turns if a valid move was made
		if (moveMade) {
			IS_PLAYER1_TURN = !IS_PLAYER1_TURN;
			moveMade = false;
		}

	}
}
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol, bool& IS_PLAYER1_TURN, GameState& gameState, int horizontalOffset) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			saveGameState(gameState, "savegame.dat" , false);  // Save game before closing
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			// Adjust gridX calculation to account for the horizontal offset
			int gridX = ((event.mouseButton.x - horizontalOffset) / BEAD_SIZE);
			int gridY = ((event.mouseButton.y - BOARD_TOP_OFFSET) / BEAD_SIZE);

			if (isValidGridPosition(gridX, gridY)) {
				handleSelectionAndMovement(board, gridX, gridY, selectedRow, selectedCol, IS_PLAYER1_TURN);
			}
		}
	}
}
