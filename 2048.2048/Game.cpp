#include "Game.h"
#include <string>

Game::Game(Produce A) {
    this->A = A;
    this->winConditionMet = false;
    this->nickname = "";
    this->score = 0;
    this->highScore = 0;
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->soundEnabled = true;
    this->mode = ENDLESS;
}

void Game::mainMenu() {
    char choice;
    while (true) {
        system("cls");
        cout << "--------------------------------------\n";
        cout << "|                                    |\n";
        cout << "|             2048 Game              |\n";
        cout << "|                                    |\n";
        cout << "|      [S]  Start Game               |\n";
        cout << "|      [O]  Options                  |\n";
        cout << "|      [Q]  Quit Game                |\n";
        cout << "|                                    |\n";
        cout << "--------------------------------------\n";
        cout << "High Score: " << highScore << endl;

        choice = _getch();

        switch (toupper(choice)) {
        case 'S':
            selectGameModeAndPlay();
            break;
        case 'O':
            showOptionsScreen();
            break;
        case 'Q':
            exit(0);
            break;
        }
    }
}

void Game::showOptionsScreen() {
    char input;
    do {
        system("cls");
        cout << "--------------------------------------\n";
        cout << "|                                    |\n";
        cout << "|              Options               |\n";
        cout << "|                                    |\n";
        cout << "|  [1] Sound: " << (soundEnabled ? "On " : "Off") << "                  |\n";
        cout << "|                                    |\n";
        cout << "|  [B] Back to Main Menu             |\n";
        cout << "|                                    |\n";
        cout << "--------------------------------------\n";
        input = _getch();
        if (input == '1') {
            soundEnabled = !soundEnabled;
            if (soundEnabled) {
                Beep(800, 150);
            }
            else {
                Beep(400, 150);
            }
        }
    } while (input != 'b' && input != 'B');
}


void Game::selectGameModeAndPlay() {
    char ch;
    while (true) {
        system("cls");
        cout << "--------------------------------------\n";
        cout << "|                                    |\n";
        cout << "|          Select Game Mode          |\n";
        cout << "|                                    |\n";
        cout << "|   [SPACE]  Start Endless Mode      |\n";
        cout << "|   [I]      Start Challenge Mode    |\n";
        cout << "|   [B]      Back to Main Menu       |\n";
        cout << "|                                    |\n";
        cout << "--------------------------------------\n";
        cout << "High Score: " << highScore << endl;

        ch = _getch();
        if (ch == ' ' || ch == 'i' || ch == 'I') {
            if (ch == ' ') {
                mode = ENDLESS;
            }
            else {
                mode = CHALLENGE;
                system("cls");
                cout << "Challenge Mode Selected!\n";
                cout << "Enter your nickname: ";
                cin >> nickname;
                startTime = chrono::steady_clock::now();
            }
            play();
            break;
        }
        else if (ch == 'b' || ch == 'B') {
            return;
        }
    }
}

void Game::play() {
    A = Produce();
    score = 0;
    winConditionMet = false;

    while (true) {
        system("cls");
        cout << "Score: " << score << " | High Score: " << highScore << "\n";
        if (mode == CHALLENGE) {
            auto now = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(now - startTime);
            cout << "Player: " << nickname << "\n";
            cout << "Time: " << duration.count() << "s\n";
        }
        A.print_board(hConsole);
        cout << "Move: arrow keys, r = reset, q = quit to menu\n";

        if (winConditionMet) {
            auto endTime = chrono::steady_clock::now();
            auto finalDuration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
            cout << "\nCongratulations, " << nickname << "! You reached 2048 in " << finalDuration.count() << " seconds!\n";
            cout << "You Win! r = reset, q = quit to menu.\n";
            while (true) {
                int endKey = _getch();
                if (endKey == 'r' || endKey == 'R') {
                    if (score > highScore) highScore = score;
                    score = 0;
                    A = Produce();
                    winConditionMet = false;
                    if (mode == CHALLENGE) startTime = chrono::steady_clock::now();
                    break;
                }
                else if (endKey == 'q' || endKey == 'Q') {
                    if (score > highScore) highScore = score;
                    return;
                }
            }
            if (!winConditionMet) continue;
        }

        if (isGameOver()) {
            cout << "Game Over! r = reset, q = quit to menu.\n";
            while (true) {
                int endKey = _getch();
                if (endKey == 'r' || endKey == 'R') {
                    if (score > highScore) highScore = score;
                    score = 0;
                    A = Produce();
                    winConditionMet = false;
                    if (mode == CHALLENGE) startTime = chrono::steady_clock::now();
                    break;
                }
                else if (endKey == 'q' || endKey == 'Q') {
                    if (score > highScore) highScore = score;
                    return;
                }
            }
            if (!isGameOver()) continue;
        }

        int key = _getch();
        if (key == 'q' || key == 'Q') {
            if (score > highScore) highScore = score;
            return;
        }
        else if (key == 'r' || key == 'R') {
            if (score > highScore) highScore = score;
            score = 0;
            A = Produce();
            winConditionMet = false;
            if (mode == CHALLENGE) {
                startTime = chrono::steady_clock::now();
            }
            continue;
        }
        else if (key == 224 || key == -32) {
            key = _getch();
            switch (key) {
            case 72: moveUp(); break;
            case 80: moveDown(); break;
            case 75: moveLeft(); break;
            case 77: moveRight(); break;
            }
            A.generate_random_tile();
            if (mode == CHALLENGE && !winConditionMet) {
                winConditionMet = checkWinCondition();
            }
        }
    }
}

bool Game::checkWinCondition() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] == 256) {
                return true;
            }
        }
    }
    return false;
}

void Game::shiftLeft() {
    for (int i = 0; i < 4; i++) {
        int k = 0;
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] != 0) {
                A.board[i][k++] = A.board[i][j];
            }
        }
        while (k < 4) {
            A.board[i][k++] = 0;
        }
    }
}

void Game::mergeLeft() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j + 1]) {
                A.board[i][j] *= 2;
                score += A.board[i][j];
                A.board[i][j + 1] = 0;
                if (soundEnabled) Beep(600, 100);
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
                A.board[i][k--] = A.board[i][j];
            }
        }
        while (k >= 0) {
            A.board[i][k--] = 0;
        }
    }
}

void Game::mergeRight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j - 1]) {
                A.board[i][j] *= 2;
                score += A.board[i][j];
                A.board[i][j - 1] = 0;
                if (soundEnabled) Beep(600, 100);
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
                A.board[k++][j] = A.board[i][j];
            }
        }
        while (k < 4) {
            A.board[k++][j] = 0;
        }
    }
}

void Game::mergeUp() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i + 1][j]) {
                A.board[i][j] *= 2;
                score += A.board[i][j];
                A.board[i + 1][j] = 0;
                if (soundEnabled) Beep(600, 100);
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
                A.board[k--][j] = A.board[i][j];
            }
        }
        while (k >= 0) {
            A.board[k--][j] = 0;
        }
    }
}

void Game::mergeDown() {
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i > 0; i--) {
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i - 1][j]) {
                A.board[i][j] *= 2;
                score += A.board[i][j];
                A.board[i - 1][j] = 0;
                if (soundEnabled) Beep(600, 100);
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
    if (winConditionMet) return false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] == 0) {
                return false;
            }
            if (i < 3 && A.board[i][j] == A.board[i + 1][j]) {
                return false;
            }
            if (j < 3 && A.board[i][j] == A.board[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}
