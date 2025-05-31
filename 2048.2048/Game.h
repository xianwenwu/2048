#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib> // For exit()
#include "Produce.h"

// 跨平台輸入和清屏宏定義
#ifdef _WIN32
#include <conio.h>
#define GETCH _getch
#define CLRSCR system("cls")
#else
#include <termios.h> // For termios functions
#include <unistd.h>  // For STDIN_FILENO
#include <cstdio>    // For getchar
int custom_getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#define GETCH custom_getch
#define CLRSCR system("clear")
#endif

class Game {
private:
    Produce A; // Game 類內部持有 Produce 對象
    void shiftLeft();
    void mergeLeft();
    void moveLeft();
    void shiftRight();
    void mergeRight();
    void moveRight();
    void shiftUp();
    void mergeUp();
    void moveUp();
    void shiftDown();
    void mergeDown();
    void moveDown();

public:
    Game(); // 無參數建構函數
    void run(); // 替代原來的 play() 函數，作為遊戲主循環
    bool isGameOver();
};

#endif
