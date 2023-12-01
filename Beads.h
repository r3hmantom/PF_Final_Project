#include <SFML/Graphics.hpp>
#include "constants.h"

void drawBead(sf::RenderWindow& window, const sf::Sprite& sprite, int row, int col, int selectedRow, int selectedCol, float& rotationAngle, int horizontalOffset);
void drawBeads(sf::RenderWindow& window, const sf::Sprite& beadSprite1, const sf::Sprite& beadSprite2, int board[ROWS][COLS], int selectedRow, int selectedCol);
bool loadAndSetupSprites(sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, sf::Texture& beadTexture1, sf::Texture& beadTexture2);