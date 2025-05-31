#include "Game.h"

Game::Game(Produce A) {
    this->A = A;
}

void Game::play() {
    char ch;
    for (;;) {
        cout << "-----------------------------\n";
        for (int i = 0; i < 7; i++) {
            if (i == 2)
                cout << "|         2048 game      |\n";
            else if (i == 3)
                cout << "|      enter start      |\n";
            else if (i == 4)
                cout << "|   q:quit r:reset   |\n";
            else
                cout << "|                           |\n";
        }
        cout << "-----------------------------\n";

        ch = getchar();
        if (ch == ' ')
            break;
        else if (ch == 'q') {
            exit(0);  // Quit the game
        }
    }

    while (true) {
        A.print_board();  // Print the board
        cout << "Move: arrow keys, r = reset, q = quit\n";

        int key = _getch();
        if (key == 'q') {
            cout << "Exiting the game.\n";
            break;
        }
        else if (key == 'r') {
            cout << "Resetting the game...\n";
            A = Produce();  // Reset the board
            continue;
        }
        else if (key == 224 || key == -32) { // Arrow key input
            key = _getch();
            switch (key) {
            case 72: moveUp(); break;     // Up
            case 80: moveDown(); break;   // Down
            case 75: moveLeft(); break;   // Left
            case 77: moveRight(); break;  // Right
            }
            A.generate_random_tile();  // Generate new tiles after a move
        }

        if (isGameOver()) {
            A.print_board();
            cout << "Game Over! r = reset, q = quit.\n";
            while (true) {
                int endKey = _getch();
                if (endKey == 'r') {
                    A = Produce();
                    break;
                }
                else if (endKey == 'q') {
                    exit(0);
                }
            }
        }
    }
}

void Game::shiftLeft() {
    for (int i = 0; i < 4; i++) {
        int k = 0;
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] != 0) {
                A.board[i][k++] = A.board[i][j]; // Shift non-zero tiles to the left
            }
        }
        while (k < 4) {
            A.board[i][k++] = 0; // Fill the rest with 0
        }
    }
}

void Game::mergeLeft() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) { // Changed loop condition to avoid out-of-bounds access
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j + 1]) {
                A.board[i][j] *= 2; // Merge tiles
                A.board[i][j + 1] = 0;
            }
        }
    }
}

void Game::moveLeft() {
    shiftLeft();
    mergeLeft();
    shiftLeft();
}

void Game::shiftRight() {
    for (int i = 0; i < 4; i++) {
        int k = 3;
        for (int j = 3; j >= 0; j--) {
            if (A.board[i][j] != 0) {
                A.board[i][k--] = A.board[i][j]; // Shift non-zero tiles to the right
            }
        }
        while (k >= 0) {
            A.board[i][k--] = 0; // Fill the rest with 0
        }
    }
}

void Game::mergeRight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) { // Changed loop condition
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j - 1]) {
                A.board[i][j] *= 2; // Merge tiles
                A.board[i][j - 1] = 0;
            }
        }
    }
}

void Game::moveRight() {
    shiftRight();
    mergeRight();
    shiftRight();
}

void Game::shiftUp() {
    for (int j = 0; j < 4; j++) {
        int k = 0;
        for (int i = 0; i < 4; i++) {
            if (A.board[i][j] != 0) {
                A.board[k++][j] = A.board[i][j]; // Shift non-zero tiles up
            }
        }
        while (k < 4) {
            A.board[k++][j] = 0; // Fill the rest with 0
        }
    }
}

void Game::mergeUp() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) { // Changed loop condition
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i + 1][j]) {
                A.board[i][j] *= 2; // Merge tiles
                A.board[i + 1][j] = 0;
            }
        }
    }
}

void Game::moveUp() {
    shiftUp();
    mergeUp();
    shiftUp();
}

void Game::shiftDown() {
    for (int j = 0; j < 4; j++) {
        int k = 3;
        for (int i = 3; i >= 0; i--) {
            if (A.board[i][j] != 0) {
                A.board[k--][j] = A.board[i][j]; // Shift non-zero tiles down
            }
        }
        while (k >= 0) {
            A.board[k--][j] = 0; // Fill the rest with 0
        }
    }
}

void Game::mergeDown() {
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i > 0; i--) { // Changed loop condition
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i - 1][j]) {
                A.board[i][j] *= 2;  // Merge tiles
                A.board[i - 1][j] = 0;
            }
        }
    }
}

void Game::moveDown() {
    shiftDown();
    mergeDown();
    shiftDown();
}

bool Game::isGameOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] == 0) {
                return false; // There is an empty cell, game is not over
            }
            if (i > 0 && A.board[i][j] == A.board[i - 1][j]) {
                return false; // There are vertically adjacent tiles that can be merged, game is not over
            }
            if (j > 0 && A.board[i][j] == A.board[i][j - 1]) {
                return false; // There are horizontally adjacent tiles that can be merged, game is not over
            }
        }
    }
    A.print_board();
    return true; // No empty cells and no mergeable tiles, game over
}
