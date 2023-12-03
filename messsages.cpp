#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std;

void displayWinningMessage(sf::RenderWindow& window, bool player1Won) {
	sf::Font font;
	if (!font.loadFromFile("assets/font.ttf")) {
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
void displayPlayerTurn(sf::RenderWindow& window, bool IS_PLAYER1_TURN) {
	sf::Font font;
	if (!font.loadFromFile("assets/font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(IS_PLAYER1_TURN ? PLAYER_1_TURN_TEXT : PLAYER_2_TURN_TEXT);
	text.setCharacterSize(60);
	if (IS_PLAYER1_TURN) {
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

