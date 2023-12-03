#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
	
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
			if (board[i][j] == 0) continue;

			const sf::Sprite& currentSprite = (board[i][j] == PLAYER1) ? beadSprite1 : beadSprite2;
			drawBead(window, currentSprite, i, j, selectedRow, selectedCol, rotationAngle, horizontalOffset);
		}
	}
}
bool loadAndSetupSprites(sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Texture& beadTexture1, sf::Texture& beadTexture2) {

	if (!loadTexture(beadTexture1, "assets/bead1.png") || !loadTexture(beadTexture2, "assets/bead2.png")) {
		return false;
	}

	beadSprite1.setTexture(beadTexture1);
	beadSprite2.setTexture(beadTexture2);
	centerSpriteOrigins(beadSprite1, beadSprite2);
	return true;
}