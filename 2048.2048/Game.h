#ifndef GAME_H
#define GAME_H
#include<iostream>
#include <conio.h>// 提供_getch()，偵測鍵盤輸入
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
	void play();// 開始進行遊戲主迴圈
	bool isGameOver();// 檢查遊戲是否結束（無可移動與合併的方塊）
};
#endif
