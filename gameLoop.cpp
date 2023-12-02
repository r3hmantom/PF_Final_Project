#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
#include "inputs.h"
#include "beads.h"
#include "board.h"
#include "messages.h"
#include "menu.h"

bool initializeWindow(sf::RenderWindow& window) {
	// Get the desktop mode to determine the screen resolution
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window with the desktop resolution and prevent resizing
	// sf::Style::Titlebar | sf::Style::Close allows the window to have a title bar and close button, but not be resizable
	window.create(sf::VideoMode(desktop.width, desktop.height), "12 Beads Game", sf::Style::Titlebar | sf::Style::Close);

	// Position the window
	window.setPosition(sf::Vector2i(0, 0));

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

	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}
	sf::Text backToMenuText;
	backToMenuText.setFont(font);
	backToMenuText.setString("Back to Main Menu");
	backToMenuText.setCharacterSize(90); // Increased size
	backToMenuText.setFillColor(sf::Color::White);
	backToMenuText.setStyle(sf::Text::Bold); // Making the text bold
	// centering it
	sf::Vector2u windowSize = window.getSize();
	sf::FloatRect textRect = backToMenuText.getLocalBounds();
	backToMenuText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	backToMenuText.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 100));




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
			saveGameState(gameState, "savegame.dat", true);
			window.draw(backToMenuText);
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				// Handle clicks on 'Back to Menu' text
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					if (isMouseOverText(window, backToMenuText)) {
						return; // Return to main menu
					}
				}
			}
		}

		// Display the window contents
		window.display();
	}
}
