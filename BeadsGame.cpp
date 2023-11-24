#include <iostream>
#include <SFML/Graphics.hpp>
#include "Beads.h"

using namespace std;

// Constants and Global Variables
const int ROWS = 5;
const int COLS = 5;
const int EMPTY = 0;
const int PLAYER1 = 1;
const int PLAYER2 = -1;
const int BEAD_SIZE = 160;
bool isPlayer1Turn = true;

// Function Declarations
bool loadTexture(sf::Texture& texture, const string& filename);
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol);
void drawBeads(sf::RenderWindow& window, sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, int board[][COLS] , int selectedRow, int selectedCol);

int main() {
    int board[ROWS][COLS];
    initBoard(board, ROWS, COLS, PLAYER1, PLAYER2, EMPTY);

    sf::RenderWindow window(sf::VideoMode(800, 800), "12 Beads Game");

    sf::Texture beadTexture1, beadTexture2;
    if (!loadTexture(beadTexture1, "bead1.png") || !loadTexture(beadTexture2, "bead2.png")) {
        return -1;
    }

    sf::Sprite beadSprite1(beadTexture1), beadSprite2(beadTexture2);

    // Set the origins of the sprites to their centers
    sf::Vector2u textureSize1 = beadTexture1.getSize();
    sf::Vector2u textureSize2 = beadTexture2.getSize();
    beadSprite1.setOrigin(textureSize1.x / 2, textureSize1.y / 2);
    beadSprite2.setOrigin(textureSize2.x / 2, textureSize2.y / 2);

    int selectedRow = -1, selectedCol = -1;

    while (window.isOpen()) {
        processInput(window, board, selectedRow, selectedCol);
        window.clear();
        drawBeads(window, beadSprite1, beadSprite2, board, selectedRow, selectedCol);
        window.display();
    }

    return 0;
}


void handleSelectionAndMovement(int board[ROWS][COLS], int gridX, int gridY, int& selectedRow, int& selectedCol) {
    static int originalRow = -1, originalCol = -1;
    static bool moveMade = false; // Track if a valid move has been made

    if (selectedRow == -1) {
        // Check if the clicked bead belongs to the current player
        if ((isPlayer1Turn && board[gridY][gridX] == PLAYER1) || (!isPlayer1Turn && board[gridY][gridX] == PLAYER2)) {
            selectedRow = gridY;
            selectedCol = gridX;
            originalRow = gridY;
            originalCol = gridX;
            moveMade = false; // Reset moveMade as this is a new selection
        }
    }
    else {
        // Perform movement based on the position clicked
        if (gridY == selectedRow && gridX == selectedCol + 1) {
            moveRight(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridY == selectedRow && gridX == selectedCol - 1) {
            moveLeft(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridX == selectedCol && gridY == selectedRow + 1) {
            moveBottom(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridX == selectedCol && gridY == selectedRow - 1) {
            moveTop(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        // Diagonal movement checks
        else if (gridX == selectedCol + 1 && gridY == selectedRow - 1) {
            upperRight(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridX == selectedCol - 1 && gridY == selectedRow - 1) {
            upperLeft(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridX == selectedCol + 1 && gridY == selectedRow + 1) {
            lowerRight(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }
        else if (gridX == selectedCol - 1 && gridY == selectedRow + 1) {
            lowerLeft(board, selectedRow, selectedCol, EMPTY);
            moveMade = true;
        }

        // Reset selection
        selectedRow = -1;
        selectedCol = -1;

        // Only switch turns if a valid move was made
        if (moveMade) {
            isPlayer1Turn = !isPlayer1Turn;
            moveMade = false; // Reset for the next player's turn
        }

        // Reset original position for the next selection
        originalRow = -1;
        originalCol = -1;
    }
}
bool loadTexture(sf::Texture& texture, const string& filename) {
    if (!texture.loadFromFile(filename)) {
        cerr << "Error loading " << filename << endl;
        return false;
    }
    return true;
}
void processInput(sf::RenderWindow& window, int board[ROWS][COLS], int& selectedRow, int& selectedCol) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int gridX = event.mouseButton.x / BEAD_SIZE;
            int gridY = event.mouseButton.y / BEAD_SIZE;

            if (gridX >= 0 && gridX < COLS && gridY >= 0 && gridY < ROWS) {
                handleSelectionAndMovement(board, gridX, gridY, selectedRow, selectedCol);
            }
        }
    }
}
void drawBeads(sf::RenderWindow& window, sf::Sprite& beadSprite1, sf::Sprite& beadSprite2, int board[][COLS], int selectedRow, int selectedCol) {
    static float rotationAngle = 0.0f; // Static variable outside the loops

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == EMPTY) {
                continue; // Skip empty positions
            }

            sf::Sprite& currentSprite = (board[i][j] == PLAYER1) ? beadSprite1 : beadSprite2;
            currentSprite.setPosition(j * BEAD_SIZE + BEAD_SIZE / 2, i * BEAD_SIZE + BEAD_SIZE / 2); // Center position

            // Reset rotation for all beads
            currentSprite.setRotation(0);

            // Apply rotation if this is the selected bead
            if (i == selectedRow && j == selectedCol) {
                rotationAngle += 0.6f; // Increment the rotation angle
                currentSprite.setRotation(rotationAngle);
            }

            window.draw(currentSprite);
        }
    }
}
