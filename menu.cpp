#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std;

void showMenu(sf::RenderWindow& window, bool& startGame, bool& exitGame, bool& resumeGameSelected) {
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	// Start Game Text
	sf::Text startGameText(START_GAME_TEXT, font, 50);
	startGameText.setPosition(100, 200);
	startGameText.setFillColor(sf::Color::White);

	// Resume Game Text
	sf::Text resumeGameText(RESUME_GAME_TEXT, font, 50);
	resumeGameText.setPosition(100, 300);
	resumeGameText.setFillColor(sf::Color::White);

	// Exit Game Text
	sf::Text exitGameText(EXIT_GAME_TEXT, font, 50);
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

