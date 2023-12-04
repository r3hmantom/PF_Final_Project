#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "board.h"

using namespace std;


// images
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


// file handling
void saveGameState(const GameState& state, const string& filename, bool saveEmptyState = false) {

	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		cerr << "Error opening file for saving game state." << endl;
		return;
	}

	if (saveEmptyState) {
		// Create an empty or initial game state
		GameState emptyState;
		initBoard(emptyState.board); // Assuming initBoard initializes the board to a default state
		std::srand(std::time(nullptr));
		emptyState.IS_PLAYER1_TURN = std::rand() % 2 == 0;
		file.write(reinterpret_cast<const char*>(&emptyState), sizeof(GameState));
	}
	else {
		// Save the current game state
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


// grid
bool isValidGridPosition(int x, int y) {
	return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}


// player
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
