#ifndef GAME_H
#define GAME_H
#include<iostream>
#include"Produce.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

#ifndef _WIN32
int getch_linux() {
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
#define GETCH getch_linux
#define CLRSCR system("clear")
#else
#define GETCH _getch
#define CLRSCR system("cls")
#endif

class Game{
private:
	Produce A;
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
	Game();
	void run();
	bool isGameOver();
};
#endif
