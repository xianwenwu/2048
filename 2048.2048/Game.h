#ifndef GAME_H
#define GAME_H
#include<iostream>
#include <conio.h>
#include"Produce.h"
using namespace std;

class Game{
private:
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
	Produce A;
	Game(Produce);
	void play();
	bool isGameOver();
};
#endif
