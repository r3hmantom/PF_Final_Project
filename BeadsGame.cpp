#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
#include "board.h"
#include "beads.h"
#include "inputs.h"
#include "gameLoop.h"
#include "menu.h"
#include "messages.h"

using namespace std;







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
		initBoard(gameState.board);
		gameState.IS_PLAYER1_TURN = true;
	}

	// Resume Game Logic
	else if (resumeGameSelected) {
		if (!loadGameState(gameState, "savegame.dat")) {
			// No saved game found or error reading file, start a new game
			initBoard(gameState.board);
			gameState.IS_PLAYER1_TURN = true;
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
