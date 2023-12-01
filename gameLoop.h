#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utilities.h"
#include "inputs.h"
#include "beads.h"
#include "board.h"

bool initializeWindow(sf::RenderWindow& window);
void runGameLoop(sf::RenderWindow& window, GameState& gameState, sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Sprite& boardSprite);
