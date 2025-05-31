#include "Game.h"
#include <vector> // For potential future use, though Produce handles it now

Game::Game() : A() {
    // Produce A; 將由初始化列表 A() 自動調用 Produce 的預設建構函數
    // 遊戲開始的初始化邏輯可以放在 Produce 的建構函數中
}

void Game::run() {
    char ch;
    for (;;) {
        CLRSCR; // 清屏
        cout << "-----------------------------\n";
        for (int i = 0; i < 7; i++) {
            if (i == 2)
                cout << "|         game start         |\n";
            else if (i == 3)
                cout << "|       （space start）        |\n";
            else if (i == 4)
                cout << "|    q：quit    r：Reset Game     |\n";
            else
                cout << "|                           |\n";
        }
        cout << "-----------------------------\n";

        ch = GETCH(); // 使用跨平台的 GETCH
        if (ch == ' ')
            break;
        else if (ch == 'q') {
            exit(0);
        }
    }

    while (true) {
        CLRSCR; // 清屏
        A.print_board();
        cout << "操作：方向鍵移動，r = 重來，q = 離開\n";

        int key = GETCH(); // 使用跨平台的 GETCH
        if (key == 'q') {
            cout << "你已離開遊戲。\n";
            break;
        }
        else if (key == 'r') {
            cout << "重新開始遊戲...\n";
            A = Produce(); // 重置遊戲板
            continue;
        }
        else if (key == 224 || key == -32) { // 方向鍵的第二個字節
            key = GETCH(); // 讀取方向鍵的實際值
            switch (key) {
            case 72: moveUp(); break;    // 上
            case 80: moveDown(); break;   // 下
            case 75: moveLeft(); break;  // 左
            case 77: moveRight(); break; // 右
            }
            A.generate_random_tile_one_or_two(); // 生成一個或兩個隨機方塊
        }

        if (isGameOver()) {
            CLRSCR; // 清屏
            A.print_board(); // 顯示最終遊戲板
            cout << "遊戲結束！按 r 重新開始或 q 離開。\n";
            while (true) {
                int endKey = GETCH(); // 使用跨平台的 GETCH
                if (endKey == 'r') {
                    A = Produce(); // 重置遊戲板
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
        for (int j = 0; j < 3; j++) { // 修正邊界，避免 j+1 越界
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j + 1]) {
                A.board[i][j] *= 2;
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
                A.board[k++][j] = A.board[i][j];
            }
        }
        while (k < 4) {
            A.board[k++][j] = 0;
        }
    }
}

void Game::mergeUp() {
    for (int i = 0; i < 3; i++) { // 修正邊界，避免 i+1 越界
        for (int j = 0; j < 4; j++) {
            if (A.board[i][j] != 0 && A.board[i][j] == A.board[i + 1][j]) {
                A.board[i][j] *= 2;
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
                return false; // 還有空位，未結束
            }
            // 檢查水平方向是否有可合併的
            if (j < 3 && A.board[i][j] == A.board[i][j + 1]) {
                return false;
            }
            // 檢查垂直方向是否有可合併的
            if (i < 3 && A.board[i][j] == A.board[i + 1][j]) {
                return false;
            }
        }
    }
    return true; // 沒有空位，也沒有可合併的，遊戲結束
}
