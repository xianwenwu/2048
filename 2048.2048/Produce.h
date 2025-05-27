#ifndef R_H
#define R_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;

class Produce
{
public:
	int board[4][4];
	Produce();//初始化遊戲面板
	void generate_random_tile();//隨機產生方塊
	void print_board();//印出初始畫面、更新後畫面
};
#endif
